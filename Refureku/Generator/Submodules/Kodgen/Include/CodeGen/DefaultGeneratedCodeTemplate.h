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
			virtual void generateCode(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& entityInfo) const noexcept override {}
	};
}