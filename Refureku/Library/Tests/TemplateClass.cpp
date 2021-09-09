#include "Include/Generated/TemplateClass.rfks.h"

//GENERATED.rfks.h

template <>
rfk::Archetype const* rfk::getArchetype<TestSimpleClassTemplate>() noexcept
{
	static bool initialized = false;
	static rfk::ClassTemplate type("TestSimpleClassTemplate", 123456789, true);

	if (!initialized)
	{
		initialized = true;

		std::cout << "INITIALIZE TestSimpleClassTemplate TEMPLATE" << std::endl;

		type.properties.reserve(1);
		static_assert((ParseAllNested::targetEntityKind & rfk::EEntityKind::Class) != rfk::EEntityKind::Undefined, "[Refureku] ParseAllNested can't be applied to a rfk::EEntityKind::Class");
		static ParseAllNested property_TestSimpleClassTemplate_ParseAllNested_0_10287443313144419217u;
		type.properties.emplace_back(&property_TestSimpleClassTemplate_ParseAllNested_0_10287443313144419217u);

		//type.directParents.reserve(1);
		//type.addToParents<std::vector<T>>(static_cast<rfk::EAccessSpecifier>(1));
		//Vector<T, U, V>::_rfk_registerChildClass<Vector<T, U, V>>(type);

		rfk::TypeTemplateParameter parameter("T");
		type.addTemplateParameter(std::move(parameter));
	}

	return &type;
}

template <>
rfk::Archetype const* rfk::getArchetype<NamespaceForTemplateClass::Vector>() noexcept
{
	return nullptr;
}

namespace rfk::generated
{
	static rfk::ArchetypeRegisterer _register_TestSimpleClassTemplate = *rfk::getArchetype<TestSimpleClassTemplate>();
}