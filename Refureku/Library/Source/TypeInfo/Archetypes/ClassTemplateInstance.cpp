#include "Refureku/TypeInfo/Archetypes/ClassTemplateInstance.h"

#include <cassert>

#include "Refureku/TypeInfo/Archetypes/ClassTemplate.h"

using namespace rfk;

ClassTemplateInstance::ClassTemplateInstance(std::string&& name, uint64 id, uint64 memorySize, bool isClass, Archetype const* instantiatedFrom) noexcept:
	Class(std::forward<std::string>(name), id, memorySize, isClass, EClassKind::TemplateInstance)
{
	//A getArchetype specialization should be generated for each template specialization, so instantiatedFrom should contain a ClassTemplate
	assert(instantiatedFrom->kind == rfk::EEntityKind::Class || instantiatedFrom->kind == rfk::EEntityKind::Struct);
	assert(reinterpret_cast<Class const*>(instantiatedFrom)->classKind == EClassKind::Template);

	const_cast<ClassTemplate*>(reinterpret_cast<ClassTemplate const*>(instantiatedFrom))->registerClassTemplateInstance(*this);
}