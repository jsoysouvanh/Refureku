/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <iostream>

#include <clang-c/Index.h>

#include "Parsing/EParsingError.h"

namespace kodgen
{
	class ParsingError
	{
		private:
			/** Line the error occured at. */
			unsigned		_line					= 0;

			/** Column the error occured at. */
			unsigned		_column					= 0;

			/** Filename in which the error occured. */
			std::string		_filename				= "";

			/** Parsing error kind. */
			EParsingError	_propertyParsingError	= EParsingError::Count;

		public:
			ParsingError()																	= delete;
			ParsingError(EParsingError		parsingError,
						 CXSourceLocation	errorSourceLocation = clang_getNullLocation())	noexcept;
			ParsingError(ParsingError const&)												= default;
			ParsingError(ParsingError&&)													= default;
			~ParsingError()																	= default;

			/**
			*	@brief Getter for _filename field.
			*
			*	@return _filename.
			*/
			std::string const&		getFilename()	const noexcept;

			/**
			*	@brief Getter for _line field.
			*
			*	@return _line.
			*/
			unsigned				getLine()		const noexcept;

			/**
			*	@brief Getter for _column field.
			*
			*	@return _column.
			*/
			unsigned				getColumn()		const noexcept;

			/**
			*	@brief Getter for _propertyParsingError field.
			*
			*	@return _propertyParsingError.
			*/
			EParsingError			getErrorValue()	const noexcept;

			/**
			*	@brief Retrieve the string representation of one of this class instances.
			*
			*	@return The string representation of this instance.
			*/
			std::string				toString()		const noexcept;

			ParsingError& operator=(ParsingError const&)	= default;
			ParsingError& operator=(ParsingError&&)			= default;
	};

	std::ostream& operator<<(std::ostream& out_stream, ParsingError const& parsingError) noexcept;
}