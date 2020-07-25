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
		_generatedNamespace = new Namespace(name, id);

		(*fillerMethod)(_generatedNamespace);

		Database::registerEntity(*_generatedNamespace);
	}
	else
	{
		std::cout << "b" << std::endl;

		//Sorry we need to get rid of that const to fill you...
		(*fillerMethod)(const_cast<Namespace*>(reinterpret_cast<Namespace const*>(foundNamespace)));
	}
}

NamespaceRegisterer::~NamespaceRegisterer() noexcept
{
	if (_generatedNamespace != nullptr)
	{
		delete _generatedNamespace;
	}
}