#include "RefurekuGenerator/Properties/PropertySettingsPropertyCodeGen.h"

#include <Kodgen/InfoStructures/MethodInfo.h>

using namespace rfk;

PropertySettingsPropertyCodeGen::PropertySettingsPropertyCodeGen() noexcept:
	kodgen::MacroPropertyCodeGen("PropertySettings", kodgen::EEntityType::Class | kodgen::EEntityType::Struct)
{
}

bool PropertySettingsPropertyCodeGen::initialGenerateHeaderFileHeaderCode(kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	inout_result += "#include <Refureku/TypeInfo/Entity/EEntityKind.h>" + env.getSeparator();

	return true;
}

bool PropertySettingsPropertyCodeGen::generateClassFooterCodeForEntity(kodgen::EntityInfo const& entity, kodgen::Property const& property, kodgen::uint8 /* propertyIndex */,
															  kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	if (property.arguments.empty())
	{
		if (env.getLogger() != nullptr)
		{
			env.getLogger()->log("The PropertySettings class first constructor parameter is mandatory: " + entity.getFullName(), kodgen::ILogger::ELogSeverity::Error);
		}

		return false;
	}

	//Generate constexpr fields + get overrides
	//generate targetEntityKind
	inout_result += "public: static constexpr rfk::EEntityKind targetEntityKind = " + property.arguments[0] + ";" + env.getSeparator();
	inout_result += env.getExportSymbolMacro() + " virtual rfk::EEntityKind getTargetEntityKind() const noexcept override;" + env.getSeparator();
	
	if (property.arguments.size() >= 2)
	{
		//generate allowMultiple
		inout_result += "static constexpr bool allowMultiple = " + property.arguments[1] + ";" + env.getSeparator();
		inout_result += env.getExportSymbolMacro() + " virtual bool getAllowMultiple() const noexcept override;" + env.getSeparator();
	
		if (property.arguments.size() >= 3)
		{
			//generate shouldInherit
			inout_result += "static constexpr bool shouldInherit = " + property.arguments[2] + ";" + env.getSeparator();
			inout_result += env.getExportSymbolMacro() + " virtual bool getShouldInherit() const noexcept override;" + env.getSeparator();
		}
	}

	return true;
}

bool PropertySettingsPropertyCodeGen::initialGenerateSourceFileHeaderCode(kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	inout_result += "#include <type_traits>" + env.getSeparator(); //std::is_base_of

	return true;
}

bool PropertySettingsPropertyCodeGen::generateSourceFileHeaderCodeForEntity(kodgen::EntityInfo const& entity, kodgen::Property const& property, kodgen::uint8 /* propertyIndex **/,
																   kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept
{
	//Define getTargetEntityKind override
	inout_result += "rfk::EEntityKind " + entity.getFullName() + "::getTargetEntityKind() const noexcept { return targetEntityKind; }" + env.getSeparator();

	if (property.arguments.size() >= 2)
	{
		inout_result += "bool " + entity.getFullName() + "::getAllowMultiple() const noexcept { return allowMultiple; }" + env.getSeparator();

		if (property.arguments.size() >= 3)
		{
			inout_result += "bool " + entity.getFullName() + "::getShouldInherit() const noexcept { return shouldInherit; }" + env.getSeparator();
		}
	}
		
	//Static assert to make sure the property is attached to a class inheriting from rfk::Property.
	inout_result += "static_assert(std::is_base_of_v<rfk::Property, " + entity.getFullName() + ">, \"[Refureku] Can't attach " + property.name + " property to " + entity.getFullName() + " as it doesn't inherit from rfk::Property.\");" + env.getSeparator();

	return true;
}