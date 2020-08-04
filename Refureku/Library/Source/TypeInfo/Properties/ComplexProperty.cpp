#include "Refureku/TypeInfo/Properties/ComplexProperty.h"

#include <algorithm>

using namespace rfk;

ComplexProperty::ComplexProperty(std::string mainProperty, std::vector<std::string> subProperties) noexcept:
	SimpleProperty(std::move(mainProperty)),
	subProperties{std::move(subProperties)}
{
}

bool ComplexProperty::containsSubproperty(std::string const& name) const noexcept
{
	return std::find(subProperties.cbegin(), subProperties.cend(), name) != subProperties.cend();
}

int32 ComplexProperty::getInt32(size_t index) const
{
	try
	{
		std::string const& subprop = subProperties.at(index);

		try
		{
			return std::stoi(subprop);
		}
		catch (std::invalid_argument const& /* exception */)
		{
			throw TypeMismatch("The subproperty at the provided index \"" + subprop + "\" could not be converted to int32.");
		}
		catch (std::out_of_range const& /* exception */)
		{
			throw TypeMismatch("The subproperty at the provided index \"" + subprop + "\" could not be converted to int32 because it falls out of the range of an int32.");
		}
	}
	catch (std::out_of_range const& /* exception */)
	{
		throw OutOfRange("The provided index is out of the bounds of the subProperties vector.");
	}
}

uint32 ComplexProperty::getUint32(size_t index) const
{
	try
	{
		std::string const& subprop = subProperties.at(index);

		try
		{
			return std::stoul(subprop);
		}
		catch (std::invalid_argument const& /* exception */)
		{
			throw TypeMismatch("The subproperty at the provided index \"" + subprop + "\" could not be converted to uint32.");
		}
		catch (std::out_of_range const& /* exception */)
		{
			throw TypeMismatch("The subproperty at the provided index \"" + subprop + "\" could not be converted to uint32 because it falls out of the range of an uint32.");
		}
	}
	catch (std::out_of_range const& /* exception */)
	{
		throw OutOfRange("The provided index is out of the bounds of the subProperties vector.");
	}
}

float ComplexProperty::getFloat(size_t index) const
{
	try
	{
		std::string const& subprop = subProperties.at(index);

		try
		{
			return std::stof(subprop);
		}
		catch (std::invalid_argument const& /* exception */)
		{
			throw TypeMismatch("The subproperty at the provided index \"" + subprop + "\" could not be converted to float.");
		}
		catch (std::out_of_range const& /* exception */)
		{
			throw TypeMismatch("The subproperty at the provided index \"" + subprop + "\" could not be converted to float because it falls out of the range of a float.");
		}
	}
	catch (std::out_of_range const& /* exception */)
	{
		throw OutOfRange("The provided index is out of the bounds of the subProperties vector.");
	}
}

std::string ComplexProperty::getString(size_t index) const
{
	try
	{
		std::string const& subprop = subProperties.at(index);

		if (subprop.size() >= 2 && subprop.front() == '"' && subprop.back() == '"')
		{
			return std::string(subprop.cbegin() + 1, subprop.cend() - 1);
		}
		else
		{
			throw TypeMismatch("The subproperty at the provided index \"" + subprop + "\" could not be converted to string because it doesn't start and end with \".");
		}
	}
	catch (std::out_of_range const& /* exception */)
	{
		throw OutOfRange("The provided index is out of the bounds of the subProperties vector.");
	}
}