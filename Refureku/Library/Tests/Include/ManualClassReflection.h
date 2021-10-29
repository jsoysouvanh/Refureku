/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

//Third party class
class ThirdPartyClass
{
	protected:
		int protectedField = 0;

		void protectedMethod(){}
};

#include "Generated/ManualClassReflection.rfkh.h"

class CLASS() ThirdPartyClassWrapper : public ThirdPartyClass
{
	protected:
		METHOD()
		inline void protectedMethod()
		{
			ThirdPartyClass::protectedMethod();
		}

	public:
		METHOD()
		inline int& getProtectedField() { return protectedField; }

	ThirdPartyClassWrapper_GENERATED
};

File_ManualClassReflection_GENERATED