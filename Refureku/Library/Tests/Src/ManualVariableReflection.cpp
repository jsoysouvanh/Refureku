#include "ManualVariableReflection.h"

#include <string_view>

#include <Refureku/TypeInfo/Variables/Variable.h>
#include <Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h>

int const manuallyReflectedVariable = 24;

static rfk::Variable const& getVariable_manuallyReflectedVariable() noexcept
{
	static rfk::Variable var("manuallyReflectedVariable",
							 std::hash<std::string_view>()("manuallyReflectedVariable"),
							 rfk::getType<decltype(manuallyReflectedVariable)>(),
							 &manuallyReflectedVariable,
							 rfk::EVarFlags::Default);

	return var;
}

rfk::DefaultEntityRegisterer registerer_manuallyReflectedVariable = getVariable_manuallyReflectedVariable();