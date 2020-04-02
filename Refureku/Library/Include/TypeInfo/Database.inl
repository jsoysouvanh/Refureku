
template <typename T>
constexpr Archetype const* Database::getArchetype() noexcept
{
	if constexpr (std::is_fundamental_v<T>)
	{
		//TODO
		//Handle every fundamental type case
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

	//Restrict
	//if constexpr (std::restr<T>)
	//{
	//	currPart = currPart | rfk::ETypePart::Const;
	//}

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
Type Database::getType() noexcept
{
	rfk::Type result;

	fillType<T>(result);

	return result;
}