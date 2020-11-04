/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "RefurekuGenerator/Properties/ECodeGenLocation.h"

namespace rfk
{
	struct PropertyCodeGenData
	{
		/**
		*	Location in which the property code is generated.
		*/
		ECodeGenLocation codeGenLocation;
	};
}