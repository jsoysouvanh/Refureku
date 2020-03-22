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
					for (std::pair<EAccessSpecifier, std::vector<TypeInfo>> const baseClassIt : static_cast<StructClassInfo const&>(entityInfo).parents)
					{
						generatedFile.writeLine(toString(baseClassIt.first));

						for (TypeInfo const& baseClass : baseClassIt.second)
						{
							generatedFile.writeLine(baseClass.getName(true, true) + " -> " + baseClass.getCanonicalName(true, true));
						}
					}

					generatedFile.writeLine("Fields");
					for (std::pair<EAccessSpecifier, std::vector<FieldInfo>> const fieldIt : static_cast<StructClassInfo const&>(entityInfo).fields)
					{
						generatedFile.writeLine(toString(fieldIt.first));

						for (FieldInfo const& field : fieldIt.second)
						{
							generatedFile.writeLine(field.type.getName(true, true) + " -> " + field.type.getCanonicalName(true, true) + " " + field.name);
						}
					}

					generatedFile.writeLine("Methods");
					for (std::pair<EAccessSpecifier, std::vector<MethodInfo>> const methodIt : static_cast<StructClassInfo const&>(entityInfo).methods)
					{
						generatedFile.writeLine(toString(methodIt.first));

						for (MethodInfo const& method : methodIt.second)
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
					}

					generatedFile.writeLine("*/");

					break;

				case EntityInfo::EType::Struct:
					generatedFile.writeLine(	"#define _RFRK_GENERATED_STRUCT_" + entityInfo.name + " //TODO something");
					break;

				case EntityInfo::EType::Enum:
					generatedFile.writeLines(	"#define _RFRK_GENERATED_ENUM_" + entityInfo.name + " //TODO something",
												"/*",
												"enum class " + static_cast<EnumInfo const&>(entityInfo).name + "Reflect : " + static_cast<EnumInfo const&>(entityInfo).underlyingType,
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