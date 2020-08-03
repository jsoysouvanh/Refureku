/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <Parsing/FileParser.h>

#include "Properties/DynamicGetArchetypePropertyRule.h"
#include "Properties/CustomInstantiatorPropertyRule.h"
#include "Properties/RangePropertyRule.h"

namespace rfk
{
	class FileParser : public kodgen::FileParser
	{
		private:
			/** Native properties. */
			DynamicGetArchetypePropertyRule	_dynamicGetArchetypePropertyRule;
			CustomInstantiatorPropertyRule	_customInstantiatorPropertyRule;

		protected:
			virtual void preParse(fs::path const& parseFile)											noexcept override;
			virtual void postParse(fs::path const& parseFile, kodgen::FileParsingResult const& result)	noexcept override;

		public:
			FileParser()					noexcept;
			FileParser(FileParser const&)	= default;
			FileParser(FileParser&&)		= default;
			virtual ~FileParser()			= default;
	};
}