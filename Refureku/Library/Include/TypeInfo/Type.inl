
inline Type& Type::addPart(TypePart&& newPart) noexcept
{
	parts.emplace_back(std::forward<TypePart>(newPart));

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