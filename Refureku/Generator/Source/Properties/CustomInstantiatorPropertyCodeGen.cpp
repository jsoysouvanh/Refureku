#include "RefurekuGenerator/Properties/CustomInstantiatorPropertyCodeGen.h"

#include <Kodgen/InfoStructures/MethodInfo.h>

#include "RefurekuGenerator/Properties/NativeProperties.h"

using namespace rfk;

bool CustomInstantiatorPropertyCodeGen::generateClassFooterCode(kodgen::EntityInfo const& entity, kodgen::Property const& /* property */, kodgen::uint8 propertyIndex, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	//TODO
	return true;
}

bool CustomInstantiatorPropertyCodeGen::shouldGenerateCode(kodgen::EntityInfo const& entity, kodgen::Property const& property, kodgen::uint8 propertyIndex) const noexcept
{
	//TODO
	return false;
}

//std::string CustomInstantiatorPropertyRule::generatePrePropertyAddCode(kodgen::EntityInfo const& entity, kodgen::Property const& /* property */, PropertyCodeGenPropertyAddData& data) const noexcept
//{
//	return "type.addCustomInstantiator<" + static_cast<kodgen::MethodInfo const&>(entity).returnType.getCanonicalName() + ">(" + data.getEntityVariableName() + "); ";
//}

//std::string CustomInstantiatorPropertyRule::generateClassFooterCode(kodgen::EntityInfo const& entity, kodgen::Property const& /* property */, PropertyCodeGenClassFooterData& /* data */) const noexcept
//{
//	kodgen::MethodInfo const&	method		= static_cast<kodgen::MethodInfo const&>(entity);
//	std::string					className	= entity.outerEntity->getFullName();
//	std::string					parameters	= method.getParameterTypes();
//	std::string					methodPtr	= "&" + className + "::" + method.name;
//
//	if (parameters.empty())
//	{
//		//CustomIntantiator with no parameters
//		return "static_assert(std::is_invocable_r_v<" + className + "*, decltype(" + methodPtr + ")>, \"[Refureku] CustomInstantiator requires " + methodPtr + " to be a static method returning " + className + "* .\");";
//	}
//	else
//	{
//		return "static_assert(std::is_invocable_r_v<" + className + "*, decltype(" + methodPtr + "), " + std::move(parameters) + ">, \"[Refureku] CustomInstantiator requires " + methodPtr + " to be a static method returning " + className + "*.\");";
//	}
//}