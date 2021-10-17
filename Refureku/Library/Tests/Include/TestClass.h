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
		struct STRUCT(UniqueInheritedProperty(1)) NestedStruct
		{
			TestClass_NestedStruct_GENERATED
		};

		struct STRUCT() NestedStruct2
		{
			TestClass_NestedStruct2_GENERATED
		};

		FIELD(UniqueInheritedProperty(1))
		int			_intField	= 0;

		FIELD()
		int			_intField2	= 0;

		FIELD()
		static int	_intStaticField;

		FIELD()
		static int	_intStaticField2;

	protected:
		class CLASS(UniqueInheritedProperty(1)) NestedClass
		{
			TestClass_NestedClass_GENERATED
		};

		class CLASS() NestedClass2
		{
			TestClass_NestedClass2_GENERATED
		};

	public:
		enum class ENUM(UniqueInheritedProperty(1)) NestedEnum
		{
			Value1
		};

		enum class ENUM() NestedEnum2
		{
			Value1
		};

		METHOD()
		int			getIntField()	const	noexcept;

		METHOD()
		int			getIntField()			noexcept;

		METHOD()
		static int	getIntStaticField()		noexcept;

		METHOD()
		static int	getIntStaticField(int)	noexcept;

		bool operator==(TestClass const& other) const noexcept { return _intField == other._intField; }
		bool operator!=(TestClass const& other) const noexcept { return !(*this == other); }

	TestClass_GENERATED
};

File_TestClass_GENERATED