/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline internal::ClassTemplateInstantiationRegistererImpl::ClassTemplateInstantiationRegistererImpl(ClassTemplateInstantiation const& instantiation) noexcept:
	_registeredClassTemplateInstantiation{instantiation}
{
	Database::getInstance()._pimpl->registerEntityIdRecursive(instantiation);
}

inline internal::ClassTemplateInstantiationRegistererImpl::~ClassTemplateInstantiationRegistererImpl() noexcept
{
	Database::getInstance()._pimpl->unregisterEntityRecursive(_registeredClassTemplateInstantiation);
}