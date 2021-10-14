/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "TestProperties.h"

#include "Generated/TestClass.rfkh.h"

class CLASS(UniqueInheritedProperty(1),
			MultipleInheritedPropertyChild(2),
			MultipleInheritedProperty(4),
			UniqueNonInheritedProperty(100),
			MultipleNonInheritedProperty(101)) TestClass
{
	private:
		FIELD()
		int			_intField;

		FIELD()
		static int	_intStaticField;

	protected:
		class CLASS() NestedClass
		{
			TestClass_NestedClass_GENERATED
		};

		struct STRUCT() NestedStruct
		{
			TestClass_NestedStruct_GENERATED
		};

	public:
		enum class ENUM() NestedEnum
		{
			Value1
		};

		METHOD()
		int			getIntField() const	noexcept;

		METHOD()
		static int	getIntStaticField()	noexcept;

	TestClass_GENERATED
};

File_TestClass_GENERATED