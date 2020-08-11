/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Struct.h"

namespace rfk
{
	class Class final : public Struct
	{
		public:
			Class(std::string&&	name,
				  uint64		id,
				  uint64		memorySize)	noexcept;
			Class(Class const&)				= delete;
			Class(Class&&)					= default;
			~Class()						= default;
	};
}