#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgument.h"

#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgumentImpl.h"
#include "Refureku/TypeInfo/Archetypes/Template/TypeTemplateArgument.h"
#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateArgument.h"
#include "Refureku/TypeInfo/Archetypes/Template/TemplateTemplateArgument.h"

using namespace rfk;

TemplateArgument::TemplateArgument(TemplateArgumentImpl* implementation) noexcept:
	_pimpl(implementation)
{
}

TemplateArgument::~TemplateArgument() noexcept = default;

ETemplateParameterKind TemplateArgument::getKind() const noexcept
{
	return _pimpl->getKind();
}

bool TemplateArgument::operator==(TemplateArgument const& other) const noexcept
{
	if (_pimpl->getKind() == other._pimpl->getKind())
	{
		switch (_pimpl->getKind())
		{
			case ETemplateParameterKind::TypeTemplateParameter:
				return static_cast<TypeTemplateArgument const&>(*this) == static_cast<TypeTemplateArgument const&>(other);

			case ETemplateParameterKind::NonTypeTemplateParameter:
				return static_cast<NonTypeTemplateArgument const&>(*this) == static_cast<NonTypeTemplateArgument const&>(other);

			case ETemplateParameterKind::TemplateTemplateParameter:
				return static_cast<TemplateTemplateArgument const&>(*this) == static_cast<TemplateTemplateArgument const&>(other);
		}
	}
	
	return false;
}

bool TemplateArgument::operator!=(TemplateArgument const& other) const noexcept
{
	return !(*this == other);
}