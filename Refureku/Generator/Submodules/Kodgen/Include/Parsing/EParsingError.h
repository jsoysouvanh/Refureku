#pragma once

#include <string>

#include "Misc/FundamentalTypes.h"

namespace kodgen
{
	enum class EParsingError : uint16
	{
		/**
		*	The wrong macro has been used to mark an entity,
		*
		*	i.e. RfrkEnum(Prop1, Prop2) class MyClass {};
		*	Should use RfrkClass instead of RfrkEnum
		*/
		WrongPropertyMacroUsed = 0,

		/**
		*	A subproperty end encloser is missing
		*
		*	i.e. RfrkEnum(Prop1, Prop2[SubProp1, SubProp2, Prop3)
		*	The end encloser mark is missing after SubProp2
		*/
		SubPropertyEndEncloserMissing,

		/**
		*	A property separator is missing
		*
		*	i.e. RfrkEnum(Prop1, Prop2[SubProp1, SubProp2] Prop3)
		*	The property separator is missing after SubProp2]
		*/
		PropertySeparatorMissing,

		/**
		*	An unregistered simple property has been detected in a Property declaration
		*	There might be a type miss, or you should register this simple property in the property rules
		*	of the marked entity type
		*/
		InvalidSimpleProperty,

		/**
		*	An unregistered complex main property has been detected in a Property declaration
		*	There might be a type miss, or you should register this complex property in the property rules
		*	of the marked entity type
		*
		*	i.e. RfrkEnum(Prop1, Prop2[SubProp1, SubProp2], Prop3)
		*	Prop2 is invalid
		*/
		InvalidComplexMainProperty,

		/**
		*	An unregistered complex sub property has been detected in a Property declaration
		*	There might be a type miss, or you should register this complex property in the property rules
		*	of the marked entity type
		*
		*	i.e. RfrkEnum(Prop1, Prop2[SubProp1, SubProp2], Prop3)
		*	SubProp1 or SubProp2 is invalid
		*/
		InvalidComplexSubProperty,

		/**
		*	The file the parser attempted to parse doesn't exist or is not a file (might be a directory)
		*/
		InexistantFile,

		/**
		*	Clang internally failed to init a translation unit
		*/
		TranslationUnitInitFailed,
		
		/**
		*	Might be used in the future.
		*	Is is also used as a no-error value
		*/
		Count
	};

	std::string toString(EParsingError error) noexcept;
}