#pragma once

#define GENERATE_ENUM_OPERATORS(EnumName)																		\
inline EnumName operator|(EnumName flags1, EnumName flags2)														\
{																												\
	using UnderlyingType = std::underlying_type_t<EnumName>;													\
																												\
	return static_cast<EnumName>(static_cast<UnderlyingType>(flags1) | static_cast<UnderlyingType>(flags2));	\
}																												\
																												\
inline EnumName operator&(EnumName flags1, EnumName flags2)														\
{																												\
	using UnderlyingType = std::underlying_type_t<EnumName>;													\
																												\
	return static_cast<EnumName>(static_cast<UnderlyingType>(flags1) & static_cast<UnderlyingType>(flags2));	\
}