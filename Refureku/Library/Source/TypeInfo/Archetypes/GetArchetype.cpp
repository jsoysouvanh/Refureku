#include "Refureku/TypeInfo/Archetypes/GetArchetype.h"

#include <cstddef>
#include <functional>	//std::hash

#include "Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h"
#include "Refureku/TypeInfo/Archetypes/FundamentalArchetype.h"

template <>
rfk::Archetype const* rfk::getArchetype<void>() noexcept
{
	static FundamentalArchetype archetype("void", std::hash<std::string>()("void"), 0u);

	return &archetype;
}

rfk::ArchetypeRegisterer voidRegisterer2 = *rfk::getArchetype<void>();

template <>
rfk::Archetype const* rfk::getArchetype<std::nullptr_t>() noexcept
{
	static FundamentalArchetype	archetype("nullptr_t", std::hash<std::string>()("nullptr_t"), sizeof(std::nullptr_t));

	return &archetype;
}

rfk::ArchetypeRegisterer nullptrRegisterer2	= *rfk::getArchetype<std::nullptr_t>();

template <>
rfk::Archetype const* rfk::getArchetype<bool>() noexcept
{
	static FundamentalArchetype	archetype("bool", std::hash<std::string>()("bool"), sizeof(bool));

	return &archetype;
}

rfk::ArchetypeRegisterer boolRegisterer2 = *rfk::getArchetype<bool>();

template <>
rfk::Archetype const* rfk::getArchetype<char>() noexcept
{
	static FundamentalArchetype	archetype("char", std::hash<std::string>()("char"), sizeof(char));

	return &archetype;
}

rfk::ArchetypeRegisterer charRegisterer2 = *rfk::getArchetype<char>();

template <>
rfk::Archetype const* rfk::getArchetype<signed char>() noexcept
{
	static FundamentalArchetype	archetype("signed char", std::hash<std::string>()("signed char"), sizeof(signed char));

	return &archetype;
}

rfk::ArchetypeRegisterer signedCharRegisterer2 = *rfk::getArchetype<signed char>();

template <>
rfk::Archetype const* rfk::getArchetype<unsigned char>() noexcept
{
	static FundamentalArchetype	archetype("unsigned char", std::hash<std::string>()("unsigned char"), sizeof(unsigned char));

	return &archetype;
}

rfk::ArchetypeRegisterer ucharRegisterer2 = *rfk::getArchetype<unsigned char>();

template <>
rfk::Archetype const* rfk::getArchetype<wchar_t>() noexcept
{
	static FundamentalArchetype	archetype("wchar", std::hash<std::string>()("wchar"), sizeof(wchar_t));

	return &archetype;
}

rfk::ArchetypeRegisterer wcharRegisterer2 = *rfk::getArchetype<wchar_t>();

template <>
rfk::Archetype const* rfk::getArchetype<char16_t>() noexcept
{
	static FundamentalArchetype	archetype("char16", std::hash<std::string>()("char16"), sizeof(char16_t));

	return &archetype;
}

rfk::ArchetypeRegisterer char16Registerer2 = *rfk::getArchetype<char16_t>();

template <>
rfk::Archetype const* rfk::getArchetype<char32_t>() noexcept
{
	static FundamentalArchetype	archetype("char32", std::hash<std::string>()("char32"), sizeof(char32_t));

	return &archetype;
}

rfk::ArchetypeRegisterer char32Registerer2 = *rfk::getArchetype<char32_t>();

template <>
rfk::Archetype const* rfk::getArchetype<short>() noexcept
{
	static FundamentalArchetype	archetype("short", std::hash<std::string>()("short"), sizeof(short));

	return &archetype;
}

rfk::ArchetypeRegisterer shortRegisterer2 = *rfk::getArchetype<short>();

template <>
rfk::Archetype const* rfk::getArchetype<unsigned short>() noexcept
{
	static FundamentalArchetype	archetype("unsigned short", std::hash<std::string>()("unsigned short"), sizeof(unsigned short));

	return &archetype;
}

rfk::ArchetypeRegisterer ushortRegisterer2 = *rfk::getArchetype<unsigned short>();

template <>
rfk::Archetype const* rfk::getArchetype<int>() noexcept
{
	static FundamentalArchetype	archetype("int", std::hash<std::string>()("int"), sizeof(int));

	return &archetype;
}

rfk::ArchetypeRegisterer intRegisterer2 = *rfk::getArchetype<int>();

template <>
rfk::Archetype const* rfk::getArchetype<unsigned int>() noexcept
{
	static FundamentalArchetype	archetype("unsigned int", std::hash<std::string>()("unsigned int"), sizeof(unsigned int));

	return &archetype;
}

rfk::ArchetypeRegisterer uintRegisterer2 = *rfk::getArchetype<unsigned int>();

template <>
rfk::Archetype const* rfk::getArchetype<long>() noexcept
{
	static FundamentalArchetype	archetype("long", std::hash<std::string>()("long"), sizeof(long));

	return &archetype;
}

rfk::ArchetypeRegisterer longRegisterer2 = *rfk::getArchetype<long>();

template <>
rfk::Archetype const* rfk::getArchetype<unsigned long>() noexcept
{
	static FundamentalArchetype	archetype("unsigned long", std::hash<std::string>()("unsigned long"), sizeof(unsigned long));

	return &archetype;
}

rfk::ArchetypeRegisterer ulongRegisterer2 = *rfk::getArchetype<unsigned long>();

template <>
rfk::Archetype const* rfk::getArchetype<long long>() noexcept
{
	static FundamentalArchetype	archetype("long long", std::hash<std::string>()("long long"), sizeof(long long));

	return &archetype;
}

rfk::ArchetypeRegisterer longLongRegisterer2 = *rfk::getArchetype<long long>();

template <>
rfk::Archetype const* rfk::getArchetype<unsigned long long>() noexcept
{
	static FundamentalArchetype	archetype("unsigned long long", std::hash<std::string>()("unsigned long long"), sizeof(unsigned long long));

	return &archetype;
}

rfk::ArchetypeRegisterer ulongLongRegisterer2 = *rfk::getArchetype<unsigned long long>();

template <>
rfk::Archetype const* rfk::getArchetype<float>() noexcept
{
	static FundamentalArchetype	archetype("float", std::hash<std::string>()("float"), sizeof(float));

	return &archetype;
}

rfk::ArchetypeRegisterer floatRegisterer2 = *rfk::getArchetype<float>();

template <>
rfk::Archetype const* rfk::getArchetype<double>() noexcept
{
	static FundamentalArchetype	archetype("double", std::hash<std::string>()("double"), sizeof(double));

	return &archetype;
}

rfk::ArchetypeRegisterer doubleRegisterer2 = *rfk::getArchetype<double>();

template <>
rfk::Archetype const* rfk::getArchetype<long double>() noexcept
{
	static FundamentalArchetype	archetype("long double", std::hash<std::string>()("long double"), sizeof(long double));

	return &archetype;
}

rfk::ArchetypeRegisterer longDoubleRegisterer2 = *rfk::getArchetype<long double>();