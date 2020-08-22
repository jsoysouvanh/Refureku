/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <type_traits>	//std::is_base_of

#include "Kodgen/Parsing/FileParserFactoryBase.h"
#include "Kodgen/Parsing/FileParser.h"

namespace kodgen
{
	template <typename FileParserType>
	class FileParserFactory : public FileParserFactoryBase
	{
		static_assert(std::is_base_of_v<FileParser, FileParserType>, "The provided type must be a derived class of FileParser.");
		static_assert(std::is_default_constructible_v<FileParserType>, "The provided FileParser type must be default constructible.");
		static_assert(std::is_move_constructible_v<FileParserType>, "The provided FileParser type must be move constructible.");

		protected:
			/**
			*	@brief	Setup a generated parser for parsing, forwarding any necessary data/settings.
			*			FileParserFactory::setupParser(fileParser) **MUST** be called in any override implementation.
			*/
			virtual void setupFileParser(FileParserType& fileParser)	const	noexcept;

		public:
			FileParserFactory()							= default;
			FileParserFactory(FileParserFactory const&)	= default;
			FileParserFactory(FileParserFactory&&)		= default;
			virtual ~FileParserFactory()				= default;

			/**
			*	@brief	Generate a new ready-to-use FileParser.
			*			In any override implementation, setupParser(returnedFileParser) **MUST** be called on the generated parser before returning.
			*
			*	@return The newly generated FileParser.
			*/
			virtual FileParserType	generateFileParser()	const	noexcept;
	};

	#include "Kodgen/Parsing/FileParserFactory.inl"
}