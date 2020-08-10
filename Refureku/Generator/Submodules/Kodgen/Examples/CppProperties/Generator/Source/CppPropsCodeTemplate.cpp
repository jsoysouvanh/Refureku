#include "CppPropsCodeTemplate.h"

#include <cctype>
#include <cassert>

#include <Kodgen/InfoStructures/StructClassInfo.h>

void CppPropsCodeTemplate::generateCode(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& entityInfo) noexcept
{
	static std::string GetterPropName = "Get";
	static std::string SetterPropName = "Set";

	std::string mainMacroName = entityInfo.name + "_GENERATED";

	undefMacros(generatedFile, mainMacroName);

	//Main macro
	generatedFile.writeMacro(std::move(mainMacroName), "DEFINE_GETTERS_AND_SETTERS");

	//Getters and setters macro
	generatedFile.writeLines("#define DEFINE_GETTERS_AND_SETTERS		\\", "public:	\\");

	kodgen::StructClassInfo const& classInfo = static_cast<kodgen::StructClassInfo const&>(entityInfo);

	for (kodgen::FieldInfo const& fieldInfo : classInfo.fields)
	{
		for (kodgen::ComplexProperty const& complexProp : fieldInfo.properties.complexProperties)
		{
			//Getter
			if (complexProp.mainProperty == GetterPropName)
			{
				generatedFile.writeLine(generateGetter(fieldInfo, complexProp) + "	\\");
			}
			//Setter
			else if (complexProp.mainProperty == SetterPropName)
			{
				generatedFile.writeLine(generateSetter(fieldInfo, complexProp) + "	\\");
			}
		}
	}

	generatedFile.writeLine("private:");
}

void CppPropsCodeTemplate::undefMacros(kodgen::GeneratedFile& generatedFile, std::string const& generatedMacroName) const noexcept
{
	generatedFile.writeLines("#ifdef " + generatedMacroName, "\t#undef " + generatedMacroName, "#endif");
	generatedFile.writeLines("#ifdef DEFINE_GETTERS_AND_SETTERS", "\t#undef DEFINE_GETTERS_AND_SETTERS", "#endif\n");
}

std::string CppPropsCodeTemplate::generateGetter(kodgen::FieldInfo const& fieldInfo, kodgen::ComplexProperty const& complexProp) const noexcept
{
	std::string postQualifiers;
	std::string rawReturnType		= fieldInfo.type.getName() + " ";
	std::string returnName			= fieldInfo.name;
	bool		isConst				= false;
	bool		isRef				= false;
	bool		isPtr				= false;
	bool		isExplicit			= false;

	for (std::string const& subprop : complexProp.subProperties)
	{
		if (!isConst && subprop.at(0) == 'c')			//const
		{
			isConst = true;
		}
		else if (!isExplicit && subprop.at(0) == 'e')	//explicit
		{
			isExplicit = true;
		}
		else if (!(isRef || isPtr))
		{
			if (subprop.at(0) == '&')					//&
			{
				isRef = true;
			}
			else if (subprop.at(0) == '*')				//*
			{
				isPtr = true;
			}
		}
	}

	std::string preTypeQualifiers;
		
	//Upper case the first field info char if applicable
	std::string methodName = fieldInfo.name;
	methodName.replace(0, 1, 1, static_cast<char>(std::toupper(methodName.at(0))));
	methodName.insert(0, "get");
	methodName += "()";

	if (fieldInfo.isStatic)
	{
		preTypeQualifiers = "static";
		postQualifiers.clear();	//remove the const
	}
	else if (isConst || !(isRef || isPtr))	//Field can't be const and static so else if is fine
	{
		postQualifiers = " const";	//A const field or a getter-by-value implies a const getter even if not specified
	}

	if (isConst && (isRef || isPtr))
	{
		rawReturnType += " const ";
	}

	if (isRef)
	{
		rawReturnType += "& ";
	}
	else if (isPtr)
	{
		rawReturnType += "* ";
		returnName.insert(0, "&");
	}

	if (isExplicit)
	{
		return preTypeQualifiers + rawReturnType + methodName + postQualifiers + ";";
	}
	else
	{
		return preTypeQualifiers + rawReturnType + methodName + postQualifiers + " { return " + returnName + "; }";
	}
}

std::string CppPropsCodeTemplate::generateSetter(kodgen::FieldInfo const& fieldInfo, kodgen::ComplexProperty const& complexProp) const noexcept
{
	//Can't generate any setter if the field is originally const qualified
	if (fieldInfo.type.typeParts.back().descriptor & kodgen::ETypeDescriptor::Const)
	{
		//TODO: issue error
		return "";
	}

	std::string paramName		= "_kodgen" + fieldInfo.name;
	bool		isExplicit		= false;

	if (!complexProp.subProperties.empty())	//explicit is the only supported subprop, so if it is not empty is must be explicit
		isExplicit = true;

	std::string preTypeQualifiers;

	//Upper case the first field info char if applicable
	std::string methodName = fieldInfo.name;
	methodName.replace(0, 1, 1, static_cast<char>(std::toupper(methodName.at(0)))); 
	methodName.insert(0, "set");
	methodName += "(";

	methodName += fieldInfo.type.getName();
	methodName += ((fieldInfo.type.sizeInBytes == 0u || fieldInfo.type.sizeInBytes > 4u) &&
				   !(fieldInfo.type.typeParts.back().descriptor & kodgen::ETypeDescriptor::Ptr)	&&
				   !(fieldInfo.type.typeParts.back().descriptor & kodgen::ETypeDescriptor::LRef)) ? " const& " : " ";
	methodName += paramName;

	methodName += ")";

	if (fieldInfo.isStatic)
	{
		preTypeQualifiers = "static";
	}

	if (isExplicit)
	{
		return preTypeQualifiers + "void " + methodName + ";";
	}
	else
	{
		return preTypeQualifiers + "void " + methodName + " { " + fieldInfo.name + " = " + paramName + "; }";
	}
}