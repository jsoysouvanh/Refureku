
template <typename T>
constexpr void Database::fillType(Type& out_type) noexcept
{
	TypePart& currPart = out_type.parts.emplace_back(TypePart{ 0u, rfk::ETypePartDescriptor::Undefined, 0u });

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

		out_type.archetype = Database::getArchetype<std::decay_t<T>>();
	}
}

template <typename T>
Type const& Database::getType() noexcept
{
	static rfk::Type	result;
	static bool			initialized = false;

	if (!initialized)
	{
		initialized = true;
		Database::fillType<T>(result);
	}

	return result;
}

template <typename T>
constexpr Archetype const* Database::getArchetype() noexcept
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
		if constexpr (rfk::generated::implements_staticGetArchetype<T, rfk::Class const&()>::value || rfk::generated::implements_staticGetArchetype<T, rfk::Struct const&()>::value)
		{
			return &T::staticGetArchetype();
		}

		return nullptr;
	}
	else if constexpr (std::is_enum_v<T>)
	{
		//TODO
		return nullptr;
	}
	else
	{
		return nullptr;
	}
}