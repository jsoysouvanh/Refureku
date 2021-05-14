/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <clang-c/Index.h>

#include "Kodgen/Parsing/ParsingResults/ParsingResultBase.h"
#include "Kodgen/Misc/EAccessSpecifier.h"

namespace kodgen
{
	//Forward declarations
	class	PropertyParser;
	class	ParsingSettings;
	class	StructClassTree;

	struct ParsingContext
	{
		public:
			/** Parent context of this context. */
			ParsingContext const*	parentContext			= nullptr;

			/** Root cursor of this parsing context. */
			CXCursor				rootCursor				= clang_getNullCursor();
			
			/** Current access specifier */
			EAccessSpecifier		currentAccessSpecifier	= EAccessSpecifier::Invalid;

			/** Should check for properties (annotate) at the next parsing step? */
			bool					shouldCheckProperties	= true;

			/** Should parse all nested entities whether or not they are annotated? */
			bool					shouldParseAllNested	= false;

			/** Parser used to parse entity properties. */
			PropertyParser*			propertyParser			= nullptr;

			/** ParsingSettings used. */
			ParsingSettings const*	parsingSettings			= nullptr;

			/** Inheritance tree of all structs/classes contained in the translation unit. */
			StructClassTree*		structClassTree			= nullptr;

			/** Result of the parsing. */
			ParsingResultBase*		parsingResult			= nullptr;
	};
}