/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <Refureku/Properties/PropertySettings.h>

#include "Generated/TestProperties.rfkh.h"

//Every entity kind except Undefined
static constexpr rfk::EEntityKind const allEntityKinds = static_cast<rfk::EEntityKind>(~0 & ~static_cast<int>(rfk::EEntityKind::Undefined));

class CLASS(rfk::PropertySettings(allEntityKinds)) BaseTestProperty : public rfk::Property
{
	public:
		int value;

		inline BaseTestProperty(int value_):
			value{ value_ }
		{
		}

	BaseTestProperty_GENERATED
};

class CLASS(rfk::PropertySettings(allEntityKinds, false, true)) UniqueInheritedProperty : public BaseTestProperty
{
	public:
		inline UniqueInheritedProperty(int value_):
			BaseTestProperty(value_)
		{
		}

	UniqueInheritedProperty_GENERATED
};

class CLASS(rfk::PropertySettings(allEntityKinds, false, true)) UniqueInheritedPropertyChild : public UniqueInheritedProperty
{
	public:
		inline UniqueInheritedPropertyChild(int value_):
			UniqueInheritedProperty(value_)
		{
		}

	UniqueInheritedPropertyChild_GENERATED
};

class CLASS(rfk::PropertySettings(allEntityKinds, true, true)) MultipleInheritedProperty : public BaseTestProperty
{
	public:
		inline MultipleInheritedProperty(int value_):
			BaseTestProperty(value_)
		{
		}

	MultipleInheritedProperty_GENERATED
};

class CLASS(rfk::PropertySettings(allEntityKinds, true, true)) MultipleInheritedPropertyChild : public MultipleInheritedProperty
{
	public:
		inline MultipleInheritedPropertyChild(int value_):
			MultipleInheritedProperty(value_)
		{
		}

	MultipleInheritedPropertyChild_GENERATED
};

class CLASS(rfk::PropertySettings(allEntityKinds, false, false)) UniqueNonInheritedProperty : public BaseTestProperty
{
	public:
		inline UniqueNonInheritedProperty(int value_):
			BaseTestProperty(value_)
		{
		}

	UniqueNonInheritedProperty_GENERATED
};

class CLASS(rfk::PropertySettings(allEntityKinds, true, false)) MultipleNonInheritedProperty : public BaseTestProperty
{
	public:
		inline MultipleNonInheritedProperty(int value_):
			BaseTestProperty(value_)
		{
		}

	MultipleNonInheritedProperty_GENERATED
};

File_TestProperties_GENERATED