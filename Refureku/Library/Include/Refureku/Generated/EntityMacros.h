#pragma once

#ifndef KODGEN_PARSING

#define RFKNamespace(...)
#define RFKClass(...)
#define RFKStruct(...)
#define RFKVariable(...)
#define RFKField(...)
#define RFKMethod(...)
#define RFKEnum(...)
#define RFKEnumVal(...)
#define RFKFunction(...)

/**
*	@brief Method property. Used to make a custom way to instantiate this class through the Struct::makeInstance() method. The method must be static and return void*.
*/
#define CustomInstantiator

/**
*	@brief Namespace, Struct and Class property. Indicates the generator to parse all direct nested entities without having to explicitly mark them with the macro.
*/
#define ParseAllNested

/**
*	@brief This property can be used with any entity. Used to specify the GeneratedCodeTemplate to use to generate code for this entity.
*
*	@param generatedCodeTemplateName	string Name of the registered generated code template to use for this entity.
*/
#define GenCodeTemplate(generatedCodeTemplateName)

#endif
