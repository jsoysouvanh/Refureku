#include "RefurekuGenerator/Properties/CustomInstantiatorPropertyRule.h"

#include <Kodgen/InfoStructures/MethodInfo.h>

#include "RefurekuGenerator/Properties/NativeProperties.h"

using namespace rfk;

CustomInstantiatorPropertyRule::CustomInstantiatorPropertyRule() noexcept:
	kodgen::DefaultSimplePropertyRule(NativeProperties::customInstantiatorProperty, kodgen::EEntityType::Method, "Method property. Used to make a custom way to instantiate this class through the Struct::makeInstance() method. The method must be static and return void*.")
{
}

bool CustomInstantiatorPropertyRule::isPropertyGroupValid(kodgen::PropertyGroup const& propertyGroup, kodgen::uint8 propertyIndex, std::string& out_errorDescription) const noexcept
{
	return isUsedOnlyOnce(propertyGroup, propertyIndex, out_errorDescription);
}

bool CustomInstantiatorPropertyRule::isEntityValid(kodgen::EntityInfo const& entity, kodgen::uint8 /* propertyIndex */, std::string& out_errorDescription) const noexcept
{
	kodgen::MethodInfo const& methodInfo = static_cast<kodgen::MethodInfo const&>(entity);

	//Check that the method is static
	if (!methodInfo.isStatic)
	{
		out_errorDescription = "A method tagged with " + NativeProperties::customInstantiatorProperty + " must be static.";

		return false;
	}

	//Check that method return type is void*
	if (methodInfo.returnType.getCanonicalName(false, false) != "void *")
	{
		out_errorDescription = "A method tagged with " + NativeProperties::customInstantiatorProperty + " must return void*.";

		return false;
	}

	return true;
}