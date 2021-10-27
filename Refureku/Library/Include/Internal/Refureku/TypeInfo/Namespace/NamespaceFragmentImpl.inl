/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline NamespaceFragment::NamespaceFragmentImpl::NamespaceFragmentImpl(char const* name, std::size_t id, std::shared_ptr<Namespace>&& mergedNamespace) noexcept:
	EntityImpl(name, id, EEntityKind::NamespaceFragment),
	_nestedEntities(),
	_mergedNamespace(std::forward<std::shared_ptr<Namespace>>(mergedNamespace))
{
}

inline void NamespaceFragment::NamespaceFragmentImpl::addNestedEntity(Entity const& nestedEntity) noexcept
{
	_nestedEntities.push_back(&nestedEntity);

	switch (nestedEntity.getKind())
	{
		case EEntityKind::NamespaceFragment:
			//The same namespace might be added multiple times by different namespace fragments
			//refering to the same namespace but it is not a problem since the underlying container only keeps the first one
			_mergedNamespace->addNamespace(static_cast<NamespaceFragment const&>(nestedEntity).getMergedNamespace());
			break;

		case EEntityKind::Struct:
			[[fallthrough]];
		case EEntityKind::Class:
			[[fallthrough]];
		case EEntityKind::Enum:
			_mergedNamespace->addArchetype(static_cast<Archetype const&>(nestedEntity));
			break;

		case EEntityKind::Variable:
			_mergedNamespace->addVariable(static_cast<Variable const&>(nestedEntity));
			break;

		case EEntityKind::Function:
			_mergedNamespace->addFunction(static_cast<Function const&>(nestedEntity));
			break;

		case EEntityKind::Namespace:
			//Nested namespaces should always be added though their NamespaceFragment
			[[fallthrough]];
		case EEntityKind::EnumValue:
			//None of these kind of entities should ever be a namespace nested entity
			[[fallthrough]];
		case EEntityKind::Field:
			[[fallthrough]];
		case EEntityKind::Method:
			[[fallthrough]];
		case EEntityKind::Undefined:
			[[fallthrough]];
		default:
			assert(false);	
			break;
	}
}

inline bool	NamespaceFragment::NamespaceFragmentImpl::addProperty(Property const* property) noexcept
{
	if (_mergedNamespace->getProperty(property->getArchetype(), false) == nullptr)
	{
		_mergedNamespace->addProperty(property);
	}

	return EntityImpl::addProperty(property);
}

inline void NamespaceFragment::NamespaceFragmentImpl::unmergeFragment() const noexcept
{
	//TODO: Should find a solution to remove properties...

	for (rfk::Entity const* entity : _nestedEntities)
	{
		switch (entity->getKind())
		{
			case EEntityKind::NamespaceFragment:
				//Unmerge the nested namespace fragment
				static_cast<NamespaceFragment const*>(entity)->getPimpl()->unmergeFragment();

				//If the fragment is the last namespace reference, we can remove the whole nested namespace
				if (static_cast<NamespaceFragment const*>(entity)->getPimpl()->_mergedNamespace.use_count() == 2)
				{
					_mergedNamespace->removeNamespace(static_cast<NamespaceFragment const*>(entity)->getMergedNamespace());
				}
				break;

			case EEntityKind::Struct:
				[[fallthrough]];
			case EEntityKind::Class:
				[[fallthrough]];
			case EEntityKind::Enum:
				_mergedNamespace->removeArchetype(*static_cast<Archetype const*>(entity));
				break;

			case EEntityKind::Variable:
				_mergedNamespace->removeVariable(*static_cast<Variable const*>(entity));
				break;

			case EEntityKind::Function:
				_mergedNamespace->removeFunction(*static_cast<Function const*>(entity));
				break;

			case EEntityKind::Namespace:
				[[fallthrough]];
			case EEntityKind::EnumValue:
				[[fallthrough]];
			case EEntityKind::Field:
				[[fallthrough]];
			case EEntityKind::Method:
				[[fallthrough]];
			case EEntityKind::Undefined:
				[[fallthrough]];
			default:
				assert(false);	//None of these kind of entities should ever be a namespace nested entity
				break;
		}
	}
}

inline void NamespaceFragment::NamespaceFragmentImpl::setNestedEntitiesCapacity(std::size_t capacity) noexcept
{
	_nestedEntities.reserve(capacity);
}

inline std::vector<Entity const*> const& NamespaceFragment::NamespaceFragmentImpl::getNestedEntities() const noexcept
{
	return _nestedEntities;
}

inline rfk::SharedPtr<Namespace> const& NamespaceFragment::NamespaceFragmentImpl::getMergedNamespace() const noexcept
{
	return _mergedNamespace;
}