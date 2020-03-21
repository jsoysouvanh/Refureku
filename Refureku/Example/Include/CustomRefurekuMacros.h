#pragma once

/**
*	These macros are the tags to use in your headers to make Refureku take it into consideration.
*
*	You can redefine these macro names as you like,
*	but never change their expansion.
*/

#ifdef KODGEN_PARSING
	#define Class(...)		__attribute__((annotate("KGC:"#__VA_ARGS__)))
	#define Struct(...)		__attribute__((annotate("KGS:"#__VA_ARGS__)))
	#define Enum(...)		__attribute__((annotate("KGE:"#__VA_ARGS__)))
	#define EnumVal(...)	__attribute__((annotate("KGEV:"#__VA_ARGS__)))
	#define Field(...)		__attribute__((annotate("KGF:"#__VA_ARGS__)))
	#define Method(...)		__attribute__((annotate("KGM:"#__VA_ARGS__)))
#else
	#define Class(...)
	#define Struct(...)
	#define Enum(...)
	#define EnumVal(...)
	#define Field(...)
	#define Method(...)
#endif