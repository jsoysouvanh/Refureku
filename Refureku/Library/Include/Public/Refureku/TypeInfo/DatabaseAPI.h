/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/Utility/Pimpl.h"

namespace rfk
{
	//Forward declaration
	class EntityAPI;
	class NamespaceAPI;

	class DatabaseAPI final
	{
		public:
			REFUREKU_INTERNAL DatabaseAPI()		noexcept;
			DatabaseAPI(DatabaseAPI const&)		= delete;
			DatabaseAPI(DatabaseAPI&&)			= delete;
			REFUREKU_INTERNAL ~DatabaseAPI()	noexcept;

			/**
			*	@brief Retrieve an entity by id.
			*
			*	@param id The id of the entity.
			*
			*	@return A constant pointer to the queried entity if it exists, else nullptr.
			*/
			REFUREKU_API EntityAPI const*					getEntityById(std::size_t id)		const	noexcept;

			/**
			*	@brief Retrieve a namespace by id.
			*
			*	@param id The id of the namespace.
			*
			*	@return A constant pointer to the queried namespace if it exists, else nullptr.
			*/
			REFUREKU_API NamespaceAPI const*				getNamespaceById(std::size_t id)	const	noexcept;

		private:
			//Forward declaration
			class DatabaseImpl;

			Pimpl<DatabaseImpl>	_pimpl;

			REFUREKU_API static DatabaseAPI& getInstance() noexcept;


		friend REFUREKU_API DatabaseAPI const& getDatabaseAPI() noexcept;
	};

	/**
	*	@brief Get a reference to the database of this program.
	* 
	*	@return A reference to the database of this program.
	*/
	REFUREKU_API DatabaseAPI const& getDatabaseAPI() noexcept;
}