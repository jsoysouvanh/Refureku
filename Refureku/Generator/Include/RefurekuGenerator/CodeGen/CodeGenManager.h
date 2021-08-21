/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <Kodgen/CodeGen/CodeGenManager.h>

namespace rfk
{
	class CodeGenManager : public kodgen::CodeGenManager
	{
		public:
			CodeGenManager() noexcept;
	};
}