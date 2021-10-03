#include "Refureku/TypeInfo/Archetypes/GetArchetypeAPI.h"

#include <cstddef>
#include <string_view>	//std::hash<std::string_view>

#include "Refureku/TypeInfo/Archetypes/ArchetypeRegistererAPI.h"
#include "Refureku/TypeInfo/Archetypes/FundamentalArchetypeAPI.h"

using namespace rfk;

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<void>() noexcept
{
	static FundamentalArchetypeAPI archetype("void", std::hash<std::string_view>()("void"), 0u);

	return &archetype;
}

ArchetypeRegistererAPI voidRegisterer = *rfk::getArchetypeAPI<void>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<std::nullptr_t>() noexcept
{
	static FundamentalArchetypeAPI archetype("nullptr_t", std::hash<std::string_view>()("nullptr_t"), sizeof(std::nullptr_t));

	return &archetype;
}

ArchetypeRegistererAPI nullptrRegisterer = *rfk::getArchetypeAPI<std::nullptr_t>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<bool>() noexcept
{
	static FundamentalArchetypeAPI archetype("bool", std::hash<std::string_view>()("bool"), sizeof(bool));

	return &archetype;
}

ArchetypeRegistererAPI boolRegisterer = *rfk::getArchetypeAPI<bool>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<char>() noexcept
{
	static FundamentalArchetypeAPI archetype("char", std::hash<std::string_view>()("char"), sizeof(char));

	return &archetype;
}

ArchetypeRegistererAPI charRegisterer = *rfk::getArchetypeAPI<char>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<signed char>() noexcept
{
	static FundamentalArchetypeAPI archetype("signed char", std::hash<std::string_view>()("signed char"), sizeof(signed char));

	return &archetype;
}

ArchetypeRegistererAPI signedCharRegisterer = *rfk::getArchetypeAPI<signed char>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<unsigned char>() noexcept
{
	static FundamentalArchetypeAPI archetype("unsigned char", std::hash<std::string_view>()("unsigned char"), sizeof(unsigned char));

	return &archetype;
}

ArchetypeRegistererAPI ucharRegisterer = *rfk::getArchetypeAPI<unsigned char>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<wchar_t>() noexcept
{
	static FundamentalArchetypeAPI archetype("wchar", std::hash<std::string_view>()("wchar"), sizeof(wchar_t));

	return &archetype;
}

ArchetypeRegistererAPI wcharRegisterer = *rfk::getArchetypeAPI<wchar_t>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<char16_t>() noexcept
{
	static FundamentalArchetypeAPI archetype("char16", std::hash<std::string_view>()("char16"), sizeof(char16_t));

	return &archetype;
}

ArchetypeRegistererAPI char16Registerer = *rfk::getArchetypeAPI<char16_t>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<char32_t>() noexcept
{
	static FundamentalArchetypeAPI archetype("char32", std::hash<std::string_view>()("char32"), sizeof(char32_t));

	return &archetype;
}

ArchetypeRegistererAPI char32Registerer = *rfk::getArchetypeAPI<char32_t>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<short>() noexcept
{
	static FundamentalArchetypeAPI archetype("short", std::hash<std::string_view>()("short"), sizeof(short));

	return &archetype;
}

ArchetypeRegistererAPI shortRegisterer = *rfk::getArchetypeAPI<short>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<unsigned short>() noexcept
{
	static FundamentalArchetypeAPI archetype("unsigned short", std::hash<std::string_view>()("unsigned short"), sizeof(unsigned short));

	return &archetype;
}

ArchetypeRegistererAPI ushortRegisterer = *rfk::getArchetypeAPI<unsigned short>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<int>() noexcept
{
	static FundamentalArchetypeAPI archetype("int", std::hash<std::string_view>()("int"), sizeof(int));

	return &archetype;
}

ArchetypeRegistererAPI intRegisterer = *rfk::getArchetypeAPI<int>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<unsigned int>() noexcept
{
	static FundamentalArchetypeAPI archetype("unsigned int", std::hash<std::string_view>()("unsigned int"), sizeof(unsigned int));

	return &archetype;
}

ArchetypeRegistererAPI uintRegisterer = *rfk::getArchetypeAPI<unsigned int>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<long>() noexcept
{
	static FundamentalArchetypeAPI archetype("long", std::hash<std::string_view>()("long"), sizeof(long));

	return &archetype;
}

ArchetypeRegistererAPI longRegisterer = *rfk::getArchetypeAPI<long>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<unsigned long>() noexcept
{
	static FundamentalArchetypeAPI archetype("unsigned long", std::hash<std::string_view>()("unsigned long"), sizeof(unsigned long));

	return &archetype;
}

ArchetypeRegistererAPI ulongRegisterer = *rfk::getArchetypeAPI<unsigned long>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<long long>() noexcept
{
	static FundamentalArchetypeAPI archetype("long long", std::hash<std::string_view>()("long long"), sizeof(long long));

	return &archetype;
}

ArchetypeRegistererAPI longLongRegisterer = *rfk::getArchetypeAPI<long long>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<unsigned long long>() noexcept
{
	static FundamentalArchetypeAPI archetype("unsigned long long", std::hash<std::string_view>()("unsigned long long"), sizeof(unsigned long long));

	return &archetype;
}

ArchetypeRegistererAPI ulongLongRegisterer = *rfk::getArchetypeAPI<unsigned long long>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<float>() noexcept
{
	static FundamentalArchetypeAPI archetype("float", std::hash<std::string_view>()("float"), sizeof(float));

	return &archetype;
}

ArchetypeRegistererAPI floatRegisterer = *rfk::getArchetypeAPI<float>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<double>() noexcept
{
	static FundamentalArchetypeAPI archetype("double", std::hash<std::string_view>()("double"), sizeof(double));

	return &archetype;
}

ArchetypeRegistererAPI doubleRegisterer = *rfk::getArchetypeAPI<double>();

template <>
ArchetypeAPI const* rfk::getArchetypeAPI<long double>() noexcept
{
	static FundamentalArchetypeAPI archetype("long double", std::hash<std::string_view>()("long double"), sizeof(long double));

	return &archetype;
}

ArchetypeRegistererAPI longDoubleRegisterer = *rfk::getArchetypeAPI<long double>();