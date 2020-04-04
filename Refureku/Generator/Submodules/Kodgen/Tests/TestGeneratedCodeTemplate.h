#pragma once

#include "CodeGen/GeneratedCodeTemplate.h"

namespace kodgen
{
	class TestGeneratedCodeTemplate : public GeneratedCodeTemplate
	{
		virtual void generateCode(GeneratedFile& generatedFile, EntityInfo const& entityInfo) const noexcept override
		{
			switch (entityInfo.entityType)
			{
				case EntityInfo::EType::Class:
					generatedFile.writeLines(	"#define _RFRK_GENERATED_CLASS_" + entityInfo.name + " //TODO something",
												"",
												"/**");

					generatedFile.writeLine("is Final: " + std::to_string(static_cast<StructClassInfo const&>(entityInfo).qualifiers.isFinal));

					generatedFile.writeLine("Base classes");
					for (StructClassInfo::ParentInfo const& baseClass : static_cast<StructClassInfo const&>(entityInfo).parents)
					{
						generatedFile.writeLine(baseClass.type.getName(true, true) + " -> " + baseClass.type.getCanonicalName(true, true));
					}

					generatedFile.writeLine("Fields");
					for (FieldInfo const& field : static_cast<StructClassInfo const&>(entityInfo).fields)
					{
						generatedFile.writeLine(field.type.getName(true, true) + " -> " + field.type.getCanonicalName(true, true) + " " + field.name);
					}

					generatedFile.writeLine("Methods");
					for (MethodInfo const& method : static_cast<StructClassInfo const&>(entityInfo).methods)
					{
						std::string methodAsString;

						methodAsString += method.name + "(";

						for (MethodParamInfo parameter : method.parameters)
						{
							methodAsString += parameter.type.getName(true, true) + " -> " + parameter.type.getCanonicalName(true, true) + " " + parameter.name + ", ";
						}

						methodAsString += ")";

						generatedFile.writeLine(methodAsString);
					}

					generatedFile.writeLine("*/");

					break;

				case EntityInfo::EType::Struct:
					generatedFile.writeLine(	"#define _RFRK_GENERATED_STRUCT_" + entityInfo.name + " //TODO something");
					break;

				case EntityInfo::EType::Enum:
					generatedFile.writeLines(	"#define _RFRK_GENERATED_ENUM_" + entityInfo.name + " //TODO something",
												"/*",
												"enum class " + static_cast<EnumInfo const&>(entityInfo).name + "Reflect : " + static_cast<EnumInfo const&>(entityInfo).underlyingType.getName(),
												"{");

					for (EnumValueInfo const& evi : static_cast<EnumInfo const&>(entityInfo).enumValues)
					{
						generatedFile.writeLine("\t" + evi.name + " = " + std::to_string(evi.defaultValue) + ",");
					}

					generatedFile.writeLines(	"};",
												"this",
												"is",
												"a",
												"test",
												"*/");

					generatedFile.writeMacro(	"SOME_MACRO(...)",
												"here",
												"is",
												"a",
												"test");

					break;

				default:
					break;
			}
		}
	};
}