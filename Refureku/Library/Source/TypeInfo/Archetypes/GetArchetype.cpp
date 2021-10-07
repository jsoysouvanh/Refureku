#include "Refureku/TypeInfo/Archetypes/GetArchetype.h"

#include <cstddef>
#include <string_view>	//std::hash<std::string_view>

#include "Refureku/TypeInfo/Archetypes/ArchetypeRegisterer.h"
#include "Refureku/TypeInfo/Archetypes/FundamentalArchetype.h"

using namespace rfk;

template <>
Archetype const* rfk::getArchetype<void>() noexcept
{
	static FundamentalArchetype archetype("void", std::hash<std::string_view>()("void"), 0u);

	return &archetype;
}

ArchetypeRegisterer voidRegisterer = *rfk::getArchetype<void>();

template <>
Archetype const* rfk::getArchetype<std::nullptr_t>() noexcept
{
	static FundamentalArchetype archetype("nullptr_t", std::hash<std::string_view>()("nullptr_t"), sizeof(std::nullptr_t));

	return &archetype;
}

ArchetypeRegisterer nullptrRegisterer = *rfk::getArchetype<std::nullptr_t>();

template <>
Archetype const* rfk::getArchetype<bool>() noexcept
{
	static FundamentalArchetype archetype("bool", std::hash<std::string_view>()("bool"), sizeof(bool));

	return &archetype;
}

ArchetypeRegisterer boolRegisterer = *rfk::getArchetype<bool>();

template <>
Archetype const* rfk::getArchetype<char>() noexcept
{
	static FundamentalArchetype archetype("char", std::hash<std::string_view>()("char"), sizeof(char));

	return &archetype;
}

ArchetypeRegisterer charRegisterer = *rfk::getArchetype<char>();

template <>
Archetype const* rfk::getArchetype<signed char>() noexcept
{
	static FundamentalArchetype archetype("signed char", std::hash<std::string_view>()("signed char"), sizeof(signed char));

	return &archetype;
}

ArchetypeRegisterer signedCharRegisterer = *rfk::getArchetype<signed char>();

template <>
Archetype const* rfk::getArchetype<unsigned char>() noexcept
{
	static FundamentalArchetype archetype("unsigned char", std::hash<std::string_view>()("unsigned char"), sizeof(unsigned char));

	return &archetype;
}

ArchetypeRegisterer ucharRegisterer = *rfk::getArchetype<unsigned char>();

template <>
Archetype const* rfk::getArchetype<wchar_t>() noexcept
{
	static FundamentalArchetype archetype("wchar", std::hash<std::string_view>()("wchar"), sizeof(wchar_t));

	return &archetype;
}

ArchetypeRegisterer wcharRegisterer = *rfk::getArchetype<wchar_t>();

template <>
Archetype const* rfk::getArchetype<char16_t>() noexcept
{
	static FundamentalArchetype archetype("char16", std::hash<std::string_view>()("char16"), sizeof(char16_t));

	return &archetype;
}

ArchetypeRegisterer char16Registerer = *rfk::getArchetype<char16_t>();

template <>
Archetype const* rfk::getArchetype<char32_t>() noexcept
{
	static FundamentalArchetype archetype("char32", std::hash<std::string_view>()("char32"), sizeof(char32_t));

	return &archetype;
}

ArchetypeRegisterer char32Registerer = *rfk::getArchetype<char32_t>();

template <>
Archetype const* rfk::getArchetype<short>() noexcept
{
	static FundamentalArchetype archetype("short", std::hash<std::string_view>()("short"), sizeof(short));

	return &archetype;
}

ArchetypeRegisterer shortRegisterer = *rfk::getArchetype<short>();

template <>
Archetype const* rfk::getArchetype<unsigned short>() noexcept
{
	static FundamentalArchetype archetype("unsigned short", std::hash<std::string_view>()("unsigned short"), sizeof(unsigned short));

	return &archetype;
}

ArchetypeRegisterer ushortRegisterer = *rfk::getArchetype<unsigned short>();

template <>
Archetype const* rfk::getArchetype<int>() noexcept
{
	static FundamentalArchetype archetype("int", std::hash<std::string_view>()("int"), sizeof(int));

	return &archetype;
}

ArchetypeRegisterer intRegisterer = *rfk::getArchetype<int>();

template <>
Archetype const* rfk::getArchetype<unsigned int>() noexcept
{
	static FundamentalArchetype archetype("unsigned int", std::hash<std::string_view>()("unsigned int"), sizeof(unsigned int));

	return &archetype;
}

ArchetypeRegisterer uintRegisterer = *rfk::getArchetype<unsigned int>();

template <>
Archetype const* rfk::getArchetype<long>() noexcept
{
	static FundamentalArchetype archetype("long", std::hash<std::string_view>()("long"), sizeof(long));

	return &archetype;
}

ArchetypeRegisterer longRegisterer = *rfk::getArchetype<long>();

template <>
Archetype const* rfk::getArchetype<unsigned long>() noexcept
{
	static FundamentalArchetype archetype("unsigned long", std::hash<std::string_view>()("unsigned long"), sizeof(unsigned long));

	return &archetype;
}

ArchetypeRegisterer ulongRegisterer = *rfk::getArchetype<unsigned long>();

template <>
Archetype const* rfk::getArchetype<long long>() noexcept
{
	static FundamentalArchetype archetype("long long", std::hash<std::string_view>()("long long"), sizeof(long long));

	return &archetype;
}

ArchetypeRegisterer longLongRegisterer = *rfk::getArchetype<long long>();

template <>
Archetype const* rfk::getArchetype<unsigned long long>() noexcept
{
	static FundamentalArchetype archetype("unsigned long long", std::hash<std::string_view>()("unsigned long long"), sizeof(unsigned long long));

	return &archetype;
}

ArchetypeRegisterer ulongLongRegisterer = *rfk::getArchetype<unsigned long long>();

template <>
Archetype const* rfk::getArchetype<float>() noexcept
{
	static FundamentalArchetype archetype("float", std::hash<std::string_view>()("float"), sizeof(float));

	return &archetype;
}

ArchetypeRegisterer floatRegisterer = *rfk::getArchetype<float>();

template <>
Archetype const* rfk::getArchetype<double>() noexcept
{
	static FundamentalArchetype archetype("double", std::hash<std::string_view>()("double"), sizeof(double));

	return &archetype;
}

ArchetypeRegisterer doubleRegisterer = *rfk::getArchetype<double>();

template <>
Archetype const* rfk::getArchetype<long double>() noexcept
{
	static FundamentalArchetype archetype("long double", std::hash<std::string_view>()("long double"), sizeof(long double));

	return &archetype;
}

ArchetypeRegisterer longDoubleRegisterer = *rfk::getArchetype<long double>();