#include "GeneratedEnumCodeTemplate.h"

#include <cassert>

using namespace rfk;

void GeneratedEnumCodeTemplate::generateCode(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& entityInfo) const noexcept
{
	assert(entityInfo.entityType == kodgen::EntityInfo::EType::Enum);

	generateEnumCode(generatedFile, static_cast<kodgen::EnumInfo const&>(entityInfo));
}

void GeneratedEnumCodeTemplate::generateEnumCode(kodgen::GeneratedFile& generatedFile, kodgen::EnumInfo const& enumInfo) const noexcept
{
	std::string	mainMacroName			= _externalPrefix + enumInfo.name + "_GENERATED";
	std::string specializationMacroName	= generateGetEnumSpecialization(generatedFile, enumInfo);
	std::string registerMacroName		= generateRegistrationMacro(generatedFile, enumInfo);

	generatedFile.writeMacro(std::move(mainMacroName),
							 "namespace rfk {",
								std::move(specializationMacroName),
								std::move(registerMacroName),
							 "}");
}

std::string GeneratedEnumCodeTemplate::generateGetEnumSpecialization(kodgen::GeneratedFile& generatedFile, kodgen::EnumInfo const& enumInfo) const noexcept
{
	std::string macroName = _internalPrefix + enumInfo.name + "_GenerateGetEnumSpecialization";

	//with namespace
	std::string typeName = enumInfo.type.getCanonicalName();
	std::string properties;

	generatedFile.writeLines("#define " + macroName + "\t\\",
							 "	template <>\t\\",
							 "	inline rfk::Enum const* getEnum<" + typeName + ">() noexcept\t\\",
							 "	{\t\\",
							 "		static bool			initialized = false;\t\\",
							 "		static rfk::Enum	type(\"" + enumInfo.name + "\", " + std::to_string(_stringHasher(enumInfo.id)) + ", sizeof(" + typeName + "));\t\\");
	
	generatedFile.writeLines("		if (!initialized)\t\\",
							 "		{\t\\",
							 "			initialized = true;\t\\");

	//Fill enum properties
	properties = fillEntityProperties(enumInfo, "type.");
	if (!properties.empty())
		generatedFile.writeLine("			" + properties + "\t\\");

	if (!enumInfo.enumValues.empty())
	{
		generatedFile.writeLines("			std::unordered_set<EnumValue, Entity::NameHasher, Entity::EqualName>::iterator	valueIt;\t\\",
								 "			rfk::EnumValue*																	ev;\t\\",
								 "			type.values.reserve(" + std::to_string(enumInfo.enumValues.size()) + ");\t\\");

		for (kodgen::EnumValueInfo const& ev : enumInfo.enumValues)
		{
			generatedFile.writeLine("			valueIt = type.values.emplace(\"" + ev.name + "\", " + std::to_string(_stringHasher(ev.id)) + "u, " + std::to_string(ev.defaultValue) + "u).first;\t\\");

			//Fill enum value properties
			properties = fillEntityProperties(ev, "ev->");
			if (!properties.empty())
				generatedFile.writeLines("			ev = const_cast<rfk::EnumValue*>(&*valueIt);\t\\",
										 "			" + properties + "\t\\");
		}
	}

	generatedFile.writeLine("		}\t\\");

	generatedFile.writeLines("		return &type;\t\\",
							 "	}",
							 "");

	return macroName;
}

std::string GeneratedEnumCodeTemplate::generateRegistrationMacro(kodgen::GeneratedFile& generatedFile, kodgen::EnumInfo const& enumInfo) const noexcept
{
	std::string macroName = _internalPrefix + enumInfo.name + "_RegisterEnum";

	//Wrap into a namespace to avoid pollution in rfk namespace, + Class so that the registration happens once only
	generatedFile.writeMacro(std::string(macroName),
								"namespace generated { class " + enumInfo.name + std::to_string(_stringHasher(enumInfo.id)) + " { static inline rfk::ArchetypeRegisterer register" + enumInfo.name + " = getEnum<" + enumInfo.type.getCanonicalName() + ">(); }; }");

	return macroName;
}