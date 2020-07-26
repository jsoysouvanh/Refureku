/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <CodeGen/GeneratedCodeTemplate.h>

namespace kodgen
{
	class DefaultGeneratedCodeTemplate : public GeneratedCodeTemplate
	{
		public:
			DefaultGeneratedCodeTemplate()										= default;
			DefaultGeneratedCodeTemplate(DefaultGeneratedCodeTemplate const&)	= delete;
			DefaultGeneratedCodeTemplate(DefaultGeneratedCodeTemplate&&)		= delete;
			virtual ~DefaultGeneratedCodeTemplate()								= default;

			/**
			*	Basic override which generates no code.
			*/
			virtual void generateCode(kodgen::GeneratedFile&	generatedFile,
									  kodgen::EntityInfo const&	entityInfo)		noexcept override {}
	};
}