#include "Refureku/TypeInfo/Archetypes/ClassTemplate.h"

#include <utility>	//std::forward

#include "Refureku/TypeInfo/Archetypes/ClassTemplateInstance.h"

using namespace rfk;

ClassTemplate::ClassTemplate(std::string&& name, uint64 id, bool isClass) noexcept:
	Class(std::forward<std::string>(name), id, 0u, isClass, EClassKind::Template)
{
}

void ClassTemplate::addTemplateParameter(TemplateParameter&& templateParameter)	noexcept
{
	templateParameters.emplace_back(std::forward<TemplateParameter>(templateParameter));
}

void ClassTemplate::registerClassTemplateInstance(ClassTemplateInstance& instance) noexcept
{
	instance.inheritAllProperties(*this);

	instances.insert(&instance);
}