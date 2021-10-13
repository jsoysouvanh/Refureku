#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplate.h"

#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateImpl.h"
#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgument.h"
#include "Refureku/TypeInfo/Entity/EntityUtility.h"

using namespace rfk;

ClassTemplate::ClassTemplate(char const* name, std::size_t id, bool isClass) noexcept:
	Struct(new ClassTemplateImpl(name, id, isClass))
{
}

ClassTemplate::~ClassTemplate() noexcept = default;

TemplateParameter const& ClassTemplate::getTemplateParameterAt(std::size_t index) const noexcept
{
	return *getPimpl()->getTemplateParameters()[index];
}

std::size_t ClassTemplate::getTemplateParametersCount() const noexcept
{
	return getPimpl()->getTemplateParameters().size();
}

std::size_t ClassTemplate::getTemplateInstantiationsCount() const noexcept
{
	return getPimpl()->getTemplateInstantiations().size();
}

ClassTemplateInstantiation const* ClassTemplate::getTemplateInstantiation(TemplateArgument const** firstArg, std::size_t argsCount) const noexcept
{
	for (ClassTemplateInstantiation const* instantiation : getPimpl()->getTemplateInstantiations())
	{
		for (std::size_t i = 0u; i < argsCount; i++)
		{
			if (instantiation->getTemplateArgumentAt(i) != **(firstArg + i))
			{
				break;
			}
			else if (i == argsCount - 1)
			{
				//If we reach this point, last 2 template arguments are equal
				return instantiation;
			}
		}
	}

	return nullptr;
}

bool ClassTemplate::foreachTemplateInstantiation(Visitor<ClassTemplateInstantiation> visitor, void* userData) const noexcept
{
	return EntityUtility::foreachEntity(getPimpl()->getTemplateInstantiations(),
										visitor,
										userData);
}

void ClassTemplate::addTemplateParameter(TemplateParameter const& param) noexcept
{
	getPimpl()->addTemplateParameter(param);
}

void ClassTemplate::registerTemplateInstantiation(ClassTemplateInstantiation const& inst) noexcept
{
	getPimpl()->addTemplateInstantiation(inst);
}