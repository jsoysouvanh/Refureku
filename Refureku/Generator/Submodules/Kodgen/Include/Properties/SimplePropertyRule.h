#pragma once

#include <string>
#include <iostream>

namespace kodgen
{
	class SimplePropertyRule
	{
		public:
			std::string name = "";

			SimplePropertyRule()							= default;
			SimplePropertyRule(std::string&& name)			noexcept;
			SimplePropertyRule(SimplePropertyRule const&)	= default;
			SimplePropertyRule(SimplePropertyRule&&)		= default;
			~SimplePropertyRule()							= default;

			bool hasSameName(SimplePropertyRule const& other)	const noexcept;

			bool operator<(SimplePropertyRule const& other)		const;
	};

	std::ostream& operator<<(std::ostream& out_stream, SimplePropertyRule const&) noexcept;
}