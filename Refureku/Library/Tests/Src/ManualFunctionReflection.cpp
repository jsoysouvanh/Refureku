#include "ManualFunctionReflection.h"

#include <string_view>

#include <Refureku/TypeInfo/Functions/Function.h>
#include <Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h>

rfk::Function const& getFunction_manuallyReflectedFunction() noexcept
{
	static bool initialized = false;
	static rfk::Function func("manuallyReflectedFunction",
							  std::hash<std::string_view>()("manuallyReflectedFunction"),
							  rfk::getType<int>(),
							  new rfk::NonMemberFunction<int(int, float)>(&manuallyReflectedFunction),
							  rfk::EFunctionFlags::Inline);

	if (!initialized)
	{
		initialized = true;

		func.setParametersCapacity(2);
		func.addParameter("i", std::hash<std::string_view>()("manuallyReflectedFunction i"), rfk::getType<int>());
		func.addParameter("j", std::hash<std::string_view>()("manuallyReflectedFunction j"), rfk::getType<float>());
	}

	return func;
}

rfk::DefaultEntityRegisterer registerer_manuallyReflectedFunction = getFunction_manuallyReflectedFunction();