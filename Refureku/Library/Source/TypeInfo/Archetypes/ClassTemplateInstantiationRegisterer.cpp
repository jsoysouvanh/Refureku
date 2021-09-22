#include "Refureku/TypeInfo/Archetypes/ClassTemplateInstantiationRegisterer.h"

#include "Refureku/TypeInfo/Database.h"
#include "Refureku/TypeInfo/Archetypes/ClassTemplateInstantiation.h"

using namespace rfk;

ClassTemplateInstantiationRegisterer::ClassTemplateInstantiationRegisterer(ClassTemplateInstantiation const& classTemplateInstance) noexcept:
	_registeredClassTemplateInstantiation{classTemplateInstance}
{
	//Class template instantiations only register their ID to the database since they are already registered to their original class template.
	Database::getInternal().registerEntity(classTemplateInstance, false);
}

ClassTemplateInstantiationRegisterer::~ClassTemplateInstantiationRegisterer() noexcept
{
	Database::getInternal().unregisterEntity(_registeredClassTemplateInstantiation, false);
}