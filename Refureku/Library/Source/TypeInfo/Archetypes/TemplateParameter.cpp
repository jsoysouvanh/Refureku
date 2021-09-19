#include "Refureku/TypeInfo/Archetypes/TemplateParameter.h"

#include <utility>	//std::forward

using namespace rfk;

TemplateParameter::TemplateParameter(std::string&& name, ETemplateParameterKind kind) noexcept:
	_name{std::forward<std::string>(name)},
	_kind{kind}
{
}

std::string const& TemplateParameter::getName() const noexcept
{
	return _name;
}

ETemplateParameterKind TemplateParameter::getKind() const noexcept
{
	return _kind;
}

TypeTemplateParameter::TypeTemplateParameter(std::string&& name) noexcept:
	TemplateParameter{std::forward<std::string>(name), ETemplateParameterKind::TypeTemplateParameter}
{
}

NonTypeTemplateParameter::NonTypeTemplateParameter(std::string&& name, Archetype const* archetype) noexcept:
	TemplateParameter{std::forward<std::string>(name), ETemplateParameterKind::NonTypeTemplateParameter},
	archetype{archetype}
{
}

TemplateTemplateParameter::TemplateTemplateParameter(std::string&& name) noexcept:
	TemplateParameter{std::forward<std::string>(name), ETemplateParameterKind::TemplateTemplateParameter}
{

}

TemplateTemplateParameter& TemplateTemplateParameter::addTemplateParameter(TemplateParameter&& templateParameter) noexcept
{
	templateParameters.emplace_back(std::forward<TemplateParameter>(templateParameter));

	return *this;
}