#include "Kodgen/Properties/ComplexPropertySubProperty.h"

#include <cassert>
#include <stdexcept>

using namespace kodgen;

ComplexPropertySubProperty::ComplexPropertySubProperty(EType type, std::string name, std::string description) noexcept:
	_type{type},
	_name{std::move(name)},
	_description{std::move(description)}
{
}

bool ComplexPropertySubProperty::isValid(std::string const& subpropertyAsString, std::string& out_errorDescription) const noexcept
{
	try
	{
		switch (_type)
		{
			case EType::Integer:
				std::stoi(subpropertyAsString);
				break;

			case EType::UnsignedInteger:
				std::stoul(subpropertyAsString);
				break;

			case EType::Float:
				std::stof(subpropertyAsString);
				break;

			case EType::String:
				if (subpropertyAsString.size() < 2u || subpropertyAsString.front() != '"' || subpropertyAsString.back() != '"')
				{
					out_errorDescription = subpropertyAsString + " is not enclosed with \"\" so it is not a string.";

					return false;
				}
				break;

			default:
				assert(false);	//Should never pass here
				break;
		}
	}
	catch (std::invalid_argument const& /* exception */)
	{
		out_errorDescription = subpropertyAsString + " could not be cast to " + toString(_type) + ".";

		return false;
	}
	catch (std::out_of_range const& /* exception */)
	{
		out_errorDescription = subpropertyAsString + " falls out of the range of a " + toString(_type) + ".";

		return false;
	}

	return true;
}

ComplexPropertySubProperty::EType ComplexPropertySubProperty::getType() const noexcept
{
	return _type;
}

std::string const& ComplexPropertySubProperty::getName() const noexcept
{
	return _name;
}

std::string const& ComplexPropertySubProperty::getDescription() const noexcept
{
	return _description;
}

std::string kodgen::toString(ComplexPropertySubProperty::EType type) noexcept
{
	switch (type)
	{
		case ComplexPropertySubProperty::EType::Integer:
			return "int32";

		case ComplexPropertySubProperty::EType::UnsignedInteger:
			return "uint32";

		case ComplexPropertySubProperty::EType::Float:
			return "float";

		case ComplexPropertySubProperty::EType::String:
			return "string";
	}

	assert(false);	//Should never pass here
	return "";
}