#include "RefurekuGenerator/CodeGen/FileGenerator.h"

using namespace rfk;

FileGenerator::FileGenerator() noexcept:
	kodgen::FileGenerator()
{
	//Generated files will use .rfk.h extension
	settings.generatedFilesExtension = ".rfk.h";

	//Only parse .h and .hpp files
	settings.supportedExtensions.emplace(".h");
	settings.supportedExtensions.emplace(".hpp");

	//Bind name -> templates
	addGeneratedCodeTemplate("RefurekuNamespace", &_namespaceCodeTemplate);
	addGeneratedCodeTemplate("RefurekuClass", &_classCodeTemplate);
	addGeneratedCodeTemplate("RefurekuEnum", &_enumCodeTemplate);
	addGeneratedCodeTemplate("RefurekuVariable", &_variableCodeTemplate);
	addGeneratedCodeTemplate("RefurekuFunction", &_functionCodeTemplate);

	/**
	*	namespace MyNamespace RFKNamespace() {}
	*	class RFKClass() MyClass {};
	*	enum [class] RFKEnum() MyEnum {};
	*/
	setDefaultGeneratedCodeTemplate(kodgen::EEntityType::Namespace, "RefurekuNamespace");
	setDefaultGeneratedCodeTemplate(kodgen::EEntityType::Class, "RefurekuClass");
	setDefaultGeneratedCodeTemplate(kodgen::EEntityType::Struct, "RefurekuClass");
	setDefaultGeneratedCodeTemplate(kodgen::EEntityType::Enum, "RefurekuEnum");
	setDefaultGeneratedCodeTemplate(kodgen::EEntityType::Variable, "RefurekuVariable");
	setDefaultGeneratedCodeTemplate(kodgen::EEntityType::Function, "RefurekuFunction");
}