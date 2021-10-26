/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline internal::DefaultEntityRegistererImpl::DefaultEntityRegistererImpl(Entity const& entity) noexcept:
	_registeredEntity{entity}
{
	//Entities which are not at file level should not be registered
	assert(entity.getOuterEntity() == nullptr);

	//Register to database
	Database::getInstance()._pimpl->registerFileLevelEntity(entity, false);
}

inline internal::DefaultEntityRegistererImpl::~DefaultEntityRegistererImpl() noexcept
{
	//Unregister from database
	Database::getInstance()._pimpl->unregisterEntity(_registeredEntity, false);
}

inline Entity const& internal::DefaultEntityRegistererImpl::getRegisteredEntity() const noexcept
{
	return _registeredEntity;
}