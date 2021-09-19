#include "Refureku/TypeInfo/Archetypes/ClassTemplateInstance.h"

#include <cassert>

#include "Refureku/TypeInfo/Archetypes/ClassTemplate.h"

using namespace rfk;

ClassTemplateInstance::ClassTemplateInstance(std::string&& name, uint64 id, uint64 memorySize, bool isClass, Archetype const& instantiatedFrom) noexcept:
	Class(std::forward<std::string>(name), id, memorySize, isClass, EClassKind::TemplateInstance),
	instantiatedFrom{static_cast<ClassTemplate const&>(instantiatedFrom)}
{
	//A getArchetype specialization should be generated for each template specialization, so instantiatedFrom should contain a ClassTemplate
	assert(instantiatedFrom.getKind() == rfk::EEntityKind::Class || instantiatedFrom.getKind() == rfk::EEntityKind::Struct);
	assert(static_cast<Class const&>(instantiatedFrom).classKind == EClassKind::Template);

	const_cast<ClassTemplate&>(static_cast<ClassTemplate const&>(instantiatedFrom)).registerClassTemplateInstance(*this);
}