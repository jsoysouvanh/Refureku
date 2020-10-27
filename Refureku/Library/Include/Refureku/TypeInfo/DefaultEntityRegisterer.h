/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

namespace rfk
{
	//Forward declaration
	class Entity;

	class DefaultEntityRegisterer
	{
		private:
			/** Registered variable. */
			Entity const* _registeredEntity = nullptr;

		public:
			DefaultEntityRegisterer()								= delete;
			DefaultEntityRegisterer(Entity const* entity)			noexcept;
			DefaultEntityRegisterer(DefaultEntityRegisterer const&)	= delete;
			DefaultEntityRegisterer(DefaultEntityRegisterer&&)		= delete;
			~DefaultEntityRegisterer()								noexcept;
	};
}