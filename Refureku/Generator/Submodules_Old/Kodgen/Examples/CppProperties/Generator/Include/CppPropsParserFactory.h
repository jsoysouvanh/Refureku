#pragma once

#include <Kodgen/Parsing/FileParserFactory.h>

#include "CppPropsParser.h"
#include "GetPropertyRule.h"
#include "SetPropertyRule.h"

class CppPropsParserFactory : public kodgen::FileParserFactory<CppPropsParser>
{
	private:
		/** Property rules used by this parser. */
		GetPropertyRule	_getPropertyRule;
		SetPropertyRule	_setPropertyRule;

	public:
		CppPropsParserFactory()								noexcept;
		CppPropsParserFactory(CppPropsParserFactory const&)	= default;
		CppPropsParserFactory(CppPropsParserFactory&&)		= default;
		virtual ~CppPropsParserFactory()					= default;
};