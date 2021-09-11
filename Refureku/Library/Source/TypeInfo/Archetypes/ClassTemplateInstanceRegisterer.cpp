#include "Refureku/TypeInfo/Archetypes/ClassTemplateInstanceRegisterer.h"

#include "Refureku/TypeInfo/Database.h"
#include "Refureku/TypeInfo/Archetypes/ClassTemplateInstance.h"

using namespace rfk;

#include <iostream> //TODO: Delete this
ClassTemplateInstanceRegisterer::ClassTemplateInstanceRegisterer(ClassTemplateInstance const& classTemplateInstance) noexcept:
	_registeredClassTemplateInstance{classTemplateInstance}
{
	//Class template instances only register their ID to the database since they are already registered to their original class template.
	Database::registerEntity(classTemplateInstance, false);

	std::cout << "Register " << classTemplateInstance.name << " to database id " << classTemplateInstance.id << std::endl;
	for (int i = 0; i < classTemplateInstance.templateArguments.size(); i++)
	{
		std::cout << classTemplateInstance.templateArguments[i].archetype->name << std::endl;
	}
}

ClassTemplateInstanceRegisterer::~ClassTemplateInstanceRegisterer() noexcept
{
	Database::unregisterEntity(_registeredClassTemplateInstance, false);
}