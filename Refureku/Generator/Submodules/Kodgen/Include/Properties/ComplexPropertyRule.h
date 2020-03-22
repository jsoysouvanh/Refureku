#pragma once

#include <regex>

#include "Properties/SimplePropertyRule.h"

namespace kodgen
{
	class ComplexPropertyRule final : public SimplePropertyRule
	{
		public:
			std::regex	subPropertyPattern;
			
			ComplexPropertyRule()													= default;
			ComplexPropertyRule(std::string&& name, std::string&& argumentPattern)	noexcept;
			ComplexPropertyRule(ComplexPropertyRule const&)							= default;
			ComplexPropertyRule(ComplexPropertyRule&&)								= default;
			~ComplexPropertyRule()													= default;

			bool isValidSubProperty(std::string const& argument)	const noexcept;
	};
}