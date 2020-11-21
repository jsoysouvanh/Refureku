#pragma once

#include <Kodgen/Properties/DefaultComplexPropertyRule.h>

class TestPropertyRule : public kodgen::DefaultComplexPropertyRule
{
	public:
		TestPropertyRule() noexcept;

		virtual std::string	generateCode(kodgen::EntityInfo const&	entity,
										 kodgen::Property const&	property,
										 void*						userData) const	noexcept override;
};