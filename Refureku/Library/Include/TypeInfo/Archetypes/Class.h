/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "TypeInfo/Archetypes/Struct.h"

namespace rfk
{
	class Class : public Struct
	{
		public:
			Class(std::string&& newName, uint64 newId, ECategory newCategory, uint64 newMemorySize)	noexcept;
			Class(Class const&)																		= delete;
			Class(Class&&)																			= default;
			~Class()																				= default;

			Class& operator=(Class const&)	= delete;
			Class& operator=(Class&&)		= default;
	};
}