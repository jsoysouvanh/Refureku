
template <typename T>
Archetype const* Type::getArchetype() noexcept
{
	if constexpr (std::is_fundamental_v<T>)
	{
		if constexpr (std::is_same_v<T, void>)
		{
			return &FundamentalArchetypes::getVoidArchetype();
		}
		else if constexpr (std::is_same_v<T, std::nullptr_t>)
		{
			return &FundamentalArchetypes::getNullptrArchetype();
		}
		else if constexpr (std::is_same_v<T, bool>)
		{
			return &FundamentalArchetypes::getBoolArchetype();
		}
		else if constexpr (std::is_same_v<T, char>)
		{
			return &FundamentalArchetypes::getCharArchetype();
		}
		else if constexpr (std::is_same_v<T, signed char>)
		{
			return &FundamentalArchetypes::getSignedCharArchetype();
		}
		else if constexpr (std::is_same_v<T, unsigned char>)
		{
			return &FundamentalArchetypes::getUnsignedCharArchetype();
		}
		else if constexpr (std::is_same_v<T, wchar_t>)
		{
			return &FundamentalArchetypes::getWideCharArchetype();
		}
		else if constexpr (std::is_same_v<T, char16_t>)
		{
			return &FundamentalArchetypes::getChar16Archetype();
		}
		else if constexpr (std::is_same_v<T, char32_t>)
		{
			return &FundamentalArchetypes::getChar32Archetype();
		}
		else if constexpr (std::is_same_v<T, short>)
		{
			return &FundamentalArchetypes::getShortArchetype();
		}
		else if constexpr (std::is_same_v<T, unsigned short>)
		{
			return &FundamentalArchetypes::getUnsignedShortArchetype();
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			return &FundamentalArchetypes::getIntArchetype();
		}
		else if constexpr (std::is_same_v<T, unsigned int>)
		{
			return &FundamentalArchetypes::getUnsignedIntArchetype();
		}
		else if constexpr (std::is_same_v<T, long>)
		{
			return &FundamentalArchetypes::getLongArchetype();
		}
		else if constexpr (std::is_same_v<T, unsigned long>)
		{
			return &FundamentalArchetypes::getUnsignedLongArchetype();
		}
		else if constexpr (std::is_same_v<T, long long>)
		{
			return &FundamentalArchetypes::getLongLongArchetype();
		}
		else if constexpr (std::is_same_v<T, unsigned long long>)
		{
			return &FundamentalArchetypes::getUnsignedLongLongArchetype();
		}
		else if constexpr (std::is_same_v<T, float>)
		{
			return &FundamentalArchetypes::getFloatArchetype();
		}
		else if constexpr (std::is_same_v<T, double>)
		{
			return &FundamentalArchetypes::getDoubleArchetype();
		}
		else if constexpr (std::is_same_v<T, long double>)
		{
			return &FundamentalArchetypes::getLongDoubleArchetype();
		}

		return nullptr;
	}
	else if constexpr (std::is_class_v<T>)
	{
		if constexpr (isReflectedClass<T>)
		{
			return &T::staticGetArchetype();
		}

		return nullptr;
	}
	else if constexpr (std::is_enum_v<T>)
	{
		return getEnum<T>();
	}
	else
	{
		return nullptr;
	}
}

template <typename T>
void Type::fillType(Type& out_type) noexcept
{
	TypePart& currPart = out_type.parts.emplace_back(TypePart{ 0u, ETypePartDescriptor::Undefined, 0u });

	//Const
	if constexpr (std::is_const_v<T>)
	{
		currPart.descriptor = currPart.descriptor | ETypePartDescriptor::Const;
	}

	//Volatile
	if constexpr (std::is_volatile_v<T>)
	{
		currPart.descriptor = currPart.descriptor | ETypePartDescriptor::Volatile;
	}

	if constexpr (std::is_array_v<T>)
	{
		currPart.descriptor = currPart.descriptor | ETypePartDescriptor::CArray;
		currPart.additionalData = static_cast<decltype(currPart.additionalData)>(std::extent_v<T>);

		fillType<std::remove_extent_t<T>>(out_type);
	}
	else if constexpr (std::is_pointer_v<T>)
	{
		currPart.descriptor = currPart.descriptor | ETypePartDescriptor::Ptr;
		fillType<std::remove_pointer_t<T>>(out_type);
	}
	else if constexpr (std::is_lvalue_reference_v<T>)
	{
		currPart.descriptor = currPart.descriptor | ETypePartDescriptor::LRef;
		fillType<std::remove_reference_t<T>>(out_type);
	}
	else if constexpr (std::is_rvalue_reference_v<T>)
	{
		currPart.descriptor = currPart.descriptor | ETypePartDescriptor::RRef;
		fillType<std::remove_reference_t<T>>(out_type);
	}
	else
	{
		currPart.descriptor = currPart.descriptor | ETypePartDescriptor::Value;

		out_type.archetype = Type::getArchetype<std::decay_t<T>>();
	}
}

template <typename T>
Type const& Type::getType() noexcept
{
	static Type	result;
	static bool	initialized = false;
	
	if (!initialized)
	{
		initialized = true;
		fillType<T>(result);
	}

	return result;
}

template <typename... ArgTypes>
inline Type& Type::addPart(ArgTypes&&... args) noexcept
{
	parts.emplace_back(std::forward<ArgTypes>(args)...);

	return *this;
}

inline Type& Type::addPart(TypePart const& newPart) noexcept
{
	parts.push_back(newPart);

	return *this;
}

inline Type& Type::removePart() noexcept
{
	if (!parts.empty())
	{
		parts.erase(parts.cbegin());
	}

	return *this;
}

inline bool Type::isPointer() const noexcept
{
	return !parts.empty() && parts.front().isPointer();
}

inline bool Type::isLValueReference() const	noexcept
{
	return !parts.empty() && parts.front().isLValueReference();
}

inline bool Type::isRValueReference() const	noexcept
{
	return !parts.empty() && parts.front().isRValueReference();
}

inline bool Type::isCArray() const noexcept
{
	return !parts.empty() && parts.front().isCArray();
}

inline bool Type::isValue() const noexcept
{
	return !parts.empty() && parts.front().isValue();
}

inline bool Type::isConst() const noexcept
{
	return !parts.empty() && parts.front().isConst();
}

inline bool Type::isVolatile() const noexcept
{
	return !parts.empty() && parts.front().isVolatile();
}

inline uint32 Type::getArraySize() const noexcept
{
	return (!parts.empty()) ? parts.front().getArraySize() : 0u;
}