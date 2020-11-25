/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <Kodgen/Parsing/FileParserFactory.h>

#include "RefurekuGenerator/Properties/CustomInstantiatorPropertyRule.h"
#include "RefurekuGenerator/Properties/PropertySettingsPropertyRule.h"
//#include "RefurekuGenerator/Properties/TestPropertyRule.h"

namespace rfk
{
	template <typename FileParserType>
	class FileParserFactory : public kodgen::FileParserFactory<FileParserType>
	{
		private:
			/** Native properties. */
			CustomInstantiatorPropertyRule	_customInstantiatorPropertyRule;
			PropertySettingsPropertyRule	_propertySettingsPropertyRule;
			//TestPropertyRule				_testPropertyRule;

		public:
			FileParserFactory()							noexcept;
			FileParserFactory(FileParserFactory const&)	= default;
			FileParserFactory(FileParserFactory&&)		= default;
			~FileParserFactory()						= default;
	};

	#include "RefurekuGenerator/Parsing/FileParserFactory.inl"
}