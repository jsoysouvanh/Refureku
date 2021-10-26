/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Exceptions/TypeMismatch.h"

namespace rfk
{
	class ReturnTypeMismatch : public TypeMismatch
	{
		public:
			using TypeMismatch::TypeMismatch;
	};
}