#include "TypeInfo/NamespaceRegisterer.h"

#include "TypeInfo/Database.h"

using namespace rfk;

NamespaceRegisterer::NamespaceRegisterer(char const* name, uint64 id, NamespaceFillerPrototype fillerMethod) noexcept
{
	std::cout << "NamespaceRegisterer: " << name << " -> " << id << std::endl;

	//Try to get an existing namespace
	Entity const* foundNamespace = Database::getEntity(id);

	if (foundNamespace == nullptr)
	{
		std::cout << "a" << std::endl;

		//This namespace hasn't been registered yet, create it and start filling
		_namespaceInstance = new Namespace(name, id);
		_isNamespaceOwner	= true;

		(*fillerMethod)(_namespaceInstance);

		Database::registerFileLevelEntity(*_namespaceInstance);
	}
	else
	{
		std::cout << "b" << std::endl;

		//Sorry we need to get rid of that const to fill you...
		_namespaceInstance = const_cast<Namespace*>(reinterpret_cast<Namespace const*>(foundNamespace));

		//TODO: PROBLEM -> subEntities have already been registered during first registerEntity call...
		//Newly added entities won't be registered in Database::entitiesById;
		//Idea: Instead of adding entities through a method, have an intermediate class and register manually elements of this intermediate class then append it to the real namespace instance.
		(*fillerMethod)(_namespaceInstance);
	}
}

NamespaceRegisterer::~NamespaceRegisterer() noexcept
{
	if (_isNamespaceOwner)
	{
		delete _namespaceInstance;
	}
}

Namespace const* NamespaceRegisterer::getNamespaceInstance() const noexcept
{
	return _namespaceInstance;
}