#include "Refureku/TypeInfo/Archetypes/ClassTemplateInstanceRegisterer.h"

#include "Refureku/TypeInfo/Database.h"
#include "Refureku/TypeInfo/Archetypes/ClassTemplateInstance.h"

using namespace rfk;

ClassTemplateInstanceRegisterer::ClassTemplateInstanceRegisterer(ClassTemplateInstance const& classTemplateInstance) noexcept:
	_registeredClassTemplateInstance{classTemplateInstance}
{
	//Class template instances only register their ID to the database since they are already registered to their original class template.
	Database::getInternal().registerEntity(classTemplateInstance, false);
}

ClassTemplateInstanceRegisterer::~ClassTemplateInstanceRegisterer() noexcept
{
	Database::getInternal().unregisterEntity(_registeredClassTemplateInstance, false);
}