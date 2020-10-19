/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <Kodgen/Parsing/FileParserFactory.h>

#include "RefurekuGenerator/Parsing/FileParser.h"
#include "RefurekuGenerator/Properties/CustomInstantiatorPropertyRule.h"

namespace rfk
{
	class FileParserFactory : public kodgen::FileParserFactory<FileParser>
	{
		private:
			/** Native properties. */
			CustomInstantiatorPropertyRule	_customInstantiatorPropertyRule;

		public:
			FileParserFactory()							noexcept;
			FileParserFactory(FileParserFactory const&)	= default;
			FileParserFactory(FileParserFactory&&)		= default;
			~FileParserFactory()						= default;
	};
}