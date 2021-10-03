/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline internal::ArchetypeRegistererImpl::ArchetypeRegistererImpl(ArchetypeAPI const& archetype) noexcept:
	_registeredArchetype{archetype}
{
	//Archetypes which are not at file level should not be registered
	assert(archetype.getOuterEntity() == nullptr);

	DatabaseAPI::getInstance()._pimpl->registerFileLevelEntity(archetype, true);
}

inline internal::ArchetypeRegistererImpl::~ArchetypeRegistererImpl() noexcept
{
	DatabaseAPI::getInstance()._pimpl->unregisterEntity(_registeredArchetype, true);
}

inline ArchetypeAPI const& internal::ArchetypeRegistererImpl::getRegisteredArchetype() const noexcept
{
	return _registeredArchetype;
}