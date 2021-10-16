/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Generated/TestFieldBase.rfkh.h"

class CLASS() TestFieldBaseClass
{
	private:
		FIELD()
		static inline int privateStaticInt		= 0;

		FIELD()
		int privateInt							= 0;

		FIELD()
		mutable int privateMutableInt			= 0;

	protected:
		FIELD()
		static inline int protectedStaticInt	= 0;

		FIELD()
		int protectedInt						= 0;

	public:
		FIELD()
		static inline int publicStaticInt		= 0;

		FIELD()
		int publicInt							= 0;

	TestFieldBaseClass_GENERATED
};

class CLASS() TestFieldBaseClassChild : public TestFieldBaseClass
{
	TestFieldBaseClassChild_GENERATED
};

File_TestFieldBase_GENERATED