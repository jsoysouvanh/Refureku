#include "Refureku/TypeInfo/Variables/VariableRegisterer.h"

#include "Refureku/TypeInfo/Database.h"

using namespace rfk;

VariableRegisterer::VariableRegisterer(Variable const* variable) noexcept:
	_registeredVariable{variable}
{
	//Register to database
	Database::registerFileLevelEntity(*variable, false);
}

VariableRegisterer::~VariableRegisterer()noexcept
{
	//Unregister from database
	Database::unregisterEntity(*_registeredVariable, false);
}