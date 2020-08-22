/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <Kodgen/Parsing/FileParser.h>

namespace rfk
{
	class FileParser : public kodgen::FileParser
	{
		protected:
			virtual void preParse(fs::path const& parseFile)											noexcept override;
			virtual void postParse(fs::path const& parseFile, kodgen::FileParsingResult const& result)	noexcept override;

		public:
			FileParser()					= default;
			FileParser(FileParser const&)	= default;
			FileParser(FileParser&&)		= default;
			virtual ~FileParser()			= default;
	};
}