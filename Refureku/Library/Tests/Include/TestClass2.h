/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "TestClass.h"

#include "Generated/TestClass2.rfkh.h"

class CLASS(UniqueInheritedPropertyChild(1), MultipleInheritedPropertyChild(3)) TestClass2 : public TestClass
{
	private:
		enum class ENUM() PrivateNestedEnum
		{
		};

	protected:
		enum class ENUM() ProtectedNestedEnum
		{
		};

	TestClass2_GENERATED
};


class CLASS(MultipleInheritedPropertyChild(5), UniqueInheritedProperty(6)) TestClass3 : public TestClass
{
	TestClass3_GENERATED
};

class CLASS() TestGetOrderedFieldsBase
{
	public:
		FIELD()
		int i;

	protected:
		FIELD()
		int j;

	private:
		FIELD()
		int k;

	public:
		FIELD()
		int l;

	protected:
		FIELD()
		int m;

	private:
		FIELD()
		int n;

	public:
		virtual ~TestGetOrderedFieldsBase() = default;

	TestGetOrderedFieldsBase_GENERATED
};

class CLASS() TestGetOrderedFieldsBase2
{
	public:
		FIELD()
		int o;

	protected:
		FIELD()
		int p;

	private:
		FIELD()
		int q;

	TestGetOrderedFieldsBase2_GENERATED
};

class CLASS() TestGetOrderedFieldsSingleInheritanceChild : public TestGetOrderedFieldsBase
{
	public:
		FIELD()
		int r;

	protected:
		FIELD()
		int s;

	private:
		FIELD()
		int t;

	TestGetOrderedFieldsSingleInheritanceChild_GENERATED
};

class CLASS() TestGetOrderedFieldsMultipleInheritanceChild : public TestGetOrderedFieldsBase, public TestGetOrderedFieldsBase2
{
	public:
		FIELD()
		int r;

	protected:
		FIELD()
		int s;

	private:
		FIELD()
		int t;

	TestGetOrderedFieldsMultipleInheritanceChild_GENERATED
};

File_TestClass2_GENERATED