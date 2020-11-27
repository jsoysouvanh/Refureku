#include "RefurekuGenerator/Properties/CustomInstantiatorPropertyRule.h"

#include <Kodgen/InfoStructures/MethodInfo.h>

#include "RefurekuGenerator/Properties/NativeProperties.h"
#include "RefurekuGenerator/Properties/CodeGenData/PropertyCodeGenPropertyAddData.h"

using namespace rfk;

CustomInstantiatorPropertyRule::CustomInstantiatorPropertyRule() noexcept:
	DefaultSimplePropertyRule(NativeProperties::customInstantiatorProperty, kodgen::EEntityType::Method)
{
}

std::string CustomInstantiatorPropertyRule::generatePrePropertyAddCode(kodgen::EntityInfo const& entity, kodgen::Property const& /* property */, PropertyCodeGenPropertyAddData& data) const noexcept
{
	return "type.addCustomInstantiator<" + static_cast<kodgen::MethodInfo const&>(entity).returnType.getCanonicalName() + ">(" + data.getEntityVariableName() + "); ";
}

std::string CustomInstantiatorPropertyRule::generateClassFooterCode(kodgen::EntityInfo const& entity, kodgen::Property const& /* property */, PropertyCodeGenClassFooterData& /* data */) const noexcept
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