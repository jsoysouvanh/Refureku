#include "RefurekuGenerator/Properties/CodeGenData/PropertyCodeGenPropertyAddData.h"

#include <cassert>
#include <utility>	//std::move

using namespace rfk;

PropertyCodeGenPropertyAddData::PropertyCodeGenPropertyAddData(bool isPreAdd, std::string entityVariable, std::string propertyVariable)	noexcept:
	PropertyCodeGenData(isPreAdd ? ECodeGenLocation::PrePropertyAdd : ECodeGenLocation::PostPropertyAdd),
	_entityVariable{std::move(entityVariable)},
	_propertyVariable{std::move(propertyVariable)}
{
}

std::string const& PropertyCodeGenPropertyAddData::accessEntityVariable() const noexcept
{
	return _entityVariable;
}

std::string const& PropertyCodeGenPropertyAddData::accessPropertyVariable() const noexcept
{
	return _propertyVariable;
}

std::string PropertyCodeGenPropertyAddData::getEntityVariableName() const noexcept
{
	return removeTrailingAccessor(_entityVariable);
}

std::string PropertyCodeGenPropertyAddData::getPropertyVariableName() const noexcept
{
	return removeTrailingAccessor(_propertyVariable);
}

std::string PropertyCodeGenPropertyAddData::removeTrailingAccessor(std::string const& variable) const noexcept
{
	switch (variable.back())
	{
		case '.':
			return std::string(variable.data(), variable.size() - 1);	//remove .

		case '>':
			return std::string(variable.data(), variable.size() - 2);	//remove ->

		default:
			//Should never be something else than . and >
			assert(false);
	}

	return "";
}