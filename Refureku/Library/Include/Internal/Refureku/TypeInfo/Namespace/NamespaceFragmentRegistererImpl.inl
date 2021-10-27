/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline internal::NamespaceFragmentRegistererImpl::NamespaceFragmentRegistererImpl(NamespaceFragment const& namespaceFragment) noexcept:
	_registeredFragment{namespaceFragment}
{
	//Only register file level namespaces
	assert(namespaceFragment.getOuterEntity() == nullptr);

	Database::getInstance()._pimpl->registerFileLevelEntity(_registeredFragment, true);
}

inline internal::NamespaceFragmentRegistererImpl::~NamespaceFragmentRegistererImpl() noexcept
{
	//Unregister namespace fragment from database
	Database::getInstance()._pimpl->unregisterEntity(_registeredFragment, true);

	/**
	*	The registerer destructor is guaranteed to run before any of the nested entity destructor because
	*	it completed its construction last, so we initiate the fragment unmerging from here.
	*/
	_registeredFragment.unmergeFragment();
}