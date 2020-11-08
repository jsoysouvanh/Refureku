#include "RefurekuGenerator/Properties/CustomInstantiatorPropertyRule.h"

#include <Kodgen/InfoStructures/MethodInfo.h>

#include "RefurekuGenerator/Properties/NativeProperties.h"
#include "RefurekuGenerator/Properties/PropertyCodeGenData.h"

using namespace rfk;

CustomInstantiatorPropertyRule::CustomInstantiatorPropertyRule() noexcept:
	kodgen::DefaultSimplePropertyRule(NativeProperties::customInstantiatorProperty, kodgen::EEntityType::Method)
{
}

std::string	CustomInstantiatorPropertyRule::generateCode(kodgen::EntityInfo const& entity, kodgen::Property const& /* property */, void* userData) const noexcept
{
	PropertyCodeGenData* data = reinterpret_cast<PropertyCodeGenData*>(userData);

	if (data->codeGenLocation == ECodeGenLocation::ClassFooter)
	{
		kodgen::MethodInfo const&	method		= static_cast<kodgen::MethodInfo const&>(entity);
		std::string					className	= entity.outerEntity->getFullName();
		std::string					parameters	= method.getParameterTypes();
		std::string					methodPtr	= "&" + className + "::" + method.name;

		if (parameters.empty())
		{
			//CustomIntantiator with no parameters
			return "static_assert(std::is_invocable_r_v<" + className + "*, decltype(" + methodPtr + ")>, \"[Refureku] CustomInstantiator requires " + methodPtr + " to be a static method returning " + className + "* .\");";
		}
		else
		{
			return "static_assert(std::is_invocable_r_v<" + className + "*, decltype(" + methodPtr + "), " + std::move(parameters) + ">, \"[Refureku] CustomInstantiator requires " + methodPtr + " to be a static method returning " + className + "*.\");";
		}
	}
	else if (data->codeGenLocation == ECodeGenLocation::PropertyAdd)
	{
		return "type.addCustomInstantiator<" + static_cast<kodgen::MethodInfo const&>(entity).returnType.getCanonicalName() + ">(staticMethod); ";
	}
	
	return "";
}