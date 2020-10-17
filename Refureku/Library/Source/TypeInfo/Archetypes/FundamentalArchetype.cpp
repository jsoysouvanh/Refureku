#include "Refureku/TypeInfo/Archetypes/FundamentalArchetype.h"

using namespace rfk;

FundamentalArchetype::FundamentalArchetype(std::string&& name, uint64 id, uint64 memorySize) noexcept:
	Archetype(std::forward<std::string>(name), id, EKind::FundamentalArchetype, memorySize)
{
}

template <>
rfk::Archetype const* rfk::getArchetype<void>() noexcept
{
	static FundamentalArchetype archetype("void", std::hash<std::string>()("void"), 0u);

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<nullptr_t>() noexcept
{
	static FundamentalArchetype	archetype("nullptr_t", std::hash<std::string>()("nullptr_t"), sizeof(std::nullptr_t));

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<bool>() noexcept
{
	static FundamentalArchetype	archetype("bool", std::hash<std::string>()("bool"), sizeof(bool));

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<char>() noexcept
{
	static FundamentalArchetype	archetype("char", std::hash<std::string>()("char"), sizeof(char));

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<signed char>() noexcept
{
	static FundamentalArchetype	archetype("signed char", std::hash<std::string>()("signed char"), sizeof(signed char));

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<unsigned char>() noexcept
{
	static FundamentalArchetype	archetype("unsigned char", std::hash<std::string>()("unsigned char"), sizeof(unsigned char));

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<wchar_t>() noexcept
{
	static FundamentalArchetype	archetype("wchar", std::hash<std::string>()("wchar"), sizeof(wchar_t));

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<char16_t>() noexcept
{
	static FundamentalArchetype	archetype("char16", std::hash<std::string>()("char16"), sizeof(char16_t));

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<char32_t>() noexcept
{
	static FundamentalArchetype	archetype("char32", std::hash<std::string>()("char32"), sizeof(char32_t));

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<short>() noexcept
{
	static FundamentalArchetype	archetype("short", std::hash<std::string>()("short"), sizeof(short));

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<unsigned short>() noexcept
{
	static FundamentalArchetype	archetype("unsigned short", std::hash<std::string>()("unsigned short"), sizeof(unsigned short));

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<int>() noexcept
{
	static FundamentalArchetype	archetype("int", std::hash<std::string>()("int"), sizeof(int));

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<unsigned int>() noexcept
{
	static FundamentalArchetype	archetype("unsigned int", std::hash<std::string>()("unsigned int"), sizeof(unsigned int));

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<long>() noexcept
{
	static FundamentalArchetype	archetype("long", std::hash<std::string>()("long"), sizeof(long));

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<unsigned long>() noexcept
{
	static FundamentalArchetype	archetype("unsigned long", std::hash<std::string>()("unsigned long"), sizeof(unsigned long));

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<long long>() noexcept
{
	static FundamentalArchetype	archetype("long long", std::hash<std::string>()("long long"), sizeof(long long));

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<unsigned long long>() noexcept
{
	static FundamentalArchetype	archetype("unsigned long long", std::hash<std::string>()("unsigned long long"), sizeof(unsigned long long));

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<float>() noexcept
{
	static FundamentalArchetype	archetype("float", std::hash<std::string>()("float"), sizeof(float));

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<double>() noexcept
{
	static FundamentalArchetype	archetype("double", std::hash<std::string>()("double"), sizeof(double));

	return &archetype;
}

template <>
rfk::Archetype const* rfk::getArchetype<long double>() noexcept
{
	static FundamentalArchetype	archetype("long double", std::hash<std::string>()("long double"), sizeof(long double));

	return &archetype;
}