#include "Refureku/TypeInfo/Archetypes/ClassTemplate.h"

#include <utility>	//std::forward

#include "Refureku/TypeInfo/Archetypes/ClassTemplateInstance.h"
#include "Refureku/TypeInfo/Archetypes/TemplateParameter.h"

using namespace rfk;

ClassTemplate::ClassTemplate(std::string&& name, std::size_t id, bool isClass) noexcept:
	Class(std::forward<std::string>(name), id, 0u, isClass, EClassKind::Template)
{
}

void ClassTemplate::addTemplateParameter(TemplateParameter const& templateParameter) noexcept
{
	_templateParameters.push_back(&templateParameter);
}

void ClassTemplate::registerClassTemplateInstance(ClassTemplateInstance& instance) noexcept
{
	instance.inheritAllProperties(*this);

	_instantiations.push_back(&instance);
}

TemplateParameter const& ClassTemplate::getTemplateParameter(std::size_t parameterIndex) const
{
	return *_templateParameters.at(parameterIndex);
}

std::size_t ClassTemplate::getTemplateParametersCount() const noexcept
{
	return _templateParameters.size();
}

ClassTemplateInstance const& ClassTemplate::getInstantiation(std::size_t instanceIndex) const
{
	return *_instantiations.at(instanceIndex);
}

std::size_t ClassTemplate::getInstantiationsCount() const noexcept
{
	return _instantiations.size();
}