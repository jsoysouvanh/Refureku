/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline internal::ArchetypeRegistererImpl::ArchetypeRegistererImpl(Archetype const& archetype) noexcept:
	_registeredArchetype{archetype}
{
	//Archetypes which are not at file level should not be registered
	assert(archetype.getOuterEntity() == nullptr);

	Database::getInstance()._pimpl->registerFileLevelEntityRecursive(archetype);
}

inline internal::ArchetypeRegistererImpl::~ArchetypeRegistererImpl() noexcept
{
	Database::getInstance()._pimpl->unregisterEntityRecursive(_registeredArchetype);
}

inline Archetype const& internal::ArchetypeRegistererImpl::getRegisteredArchetype() const noexcept
{
	return _registeredArchetype;
}