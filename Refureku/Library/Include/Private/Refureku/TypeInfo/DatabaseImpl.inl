/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline DatabaseAPI::DatabaseImpl::EntitiesById const& DatabaseAPI::DatabaseImpl::getEntitiesById() const noexcept
{
	return _entitiesById;
}

inline DatabaseAPI::DatabaseImpl::NamespacesByName const& DatabaseAPI::DatabaseImpl::getFileLevelNamespacesByName() const noexcept
{
	return _fileLevelNamespacesByName;
}

//inline DatabaseAPI::DatabaseImpl::FundamentalArchetypesByName const&	DatabaseAPI::DatabaseImpl::getFundamentalArchetypesByName() const noexcept
//{
//	return _fundamentalArchetypes;
//}

inline DatabaseAPI::DatabaseImpl::StructsByName const& DatabaseAPI::DatabaseImpl::getFileLevelStructsByName() const noexcept
{
	return _fileLevelStructsByName;
}

inline DatabaseAPI::DatabaseImpl::ClassesByName const& DatabaseAPI::DatabaseImpl::getFileLevelClassesByName() const	noexcept
{
	return _fileLevelClassesByName;
}

inline DatabaseAPI::DatabaseImpl::EnumsByName const& DatabaseAPI::DatabaseImpl::getFileLevelEnumsByName() const noexcept
{
	return _fileLevelEnumsByName;
}

inline DatabaseAPI::DatabaseImpl::VariablesByName const& DatabaseAPI::DatabaseImpl::getFileLevelVariablesByName() const noexcept
{
	return _fileLevelVariablesByName;
}

inline DatabaseAPI::DatabaseImpl::FunctionsByName const& DatabaseAPI::DatabaseImpl::getFileLevelFunctionsByName() const noexcept
{
	return _fileLevelFunctionsByName;
}

inline DatabaseAPI::DatabaseImpl::GenNamespaces const& DatabaseAPI::DatabaseImpl::getGeneratedNamespaces() const noexcept
{
	return _generatedNamespaces;
}