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
	class DatabaseAPI final
	{
		public:
			REFUREKU_INTERNAL DatabaseAPI()		noexcept;
			DatabaseAPI(DatabaseAPI const&)		= delete;
			DatabaseAPI(DatabaseAPI&&)			= delete;
			REFUREKU_INTERNAL ~DatabaseAPI()	noexcept;



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