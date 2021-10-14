/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <Refureku/Properties/PropertySettings.h>

#include "Generated/TestProperties.rfkh.h"

//Every entity kind except Undefined
static constexpr rfk::EEntityKind const allEntityKinds = static_cast<rfk::EEntityKind>(~0 & ~static_cast<int>(rfk::EEntityKind::Undefined));

class CLASS(PropertySettings(allEntityKinds, false, true)) UniqueInheritedProperty : public rfk::Property
{
	public:
		int value;

		inline UniqueInheritedProperty(int value_):
			value{ value_ }
		{
		}

	UniqueInheritedProperty_GENERATED
};

class CLASS(PropertySettings(allEntityKinds, false, true)) UniqueInheritedPropertyChild : public UniqueInheritedProperty
{
	public:
		inline UniqueInheritedPropertyChild(int value_):
			UniqueInheritedProperty(value_)
		{
		}

	UniqueInheritedPropertyChild_GENERATED
};

class CLASS(PropertySettings(allEntityKinds, true, true)) MultipleInheritedProperty : public rfk::Property
{
	public:
		int value;

		inline MultipleInheritedProperty(int value_):
			value{ value_ }
		{
		}

	MultipleInheritedProperty_GENERATED
};

class CLASS(PropertySettings(allEntityKinds, true, true)) MultipleInheritedPropertyChild : public MultipleInheritedProperty
{
	public:
		inline MultipleInheritedPropertyChild(int value_):
			MultipleInheritedProperty(value_)
		{
		}

	MultipleInheritedPropertyChild_GENERATED
};

class CLASS(PropertySettings(allEntityKinds, false, false)) UniqueNonInheritedProperty : public rfk::Property
{
	public:
		int value;

		inline UniqueNonInheritedProperty(int value_):
			value{ value_ }
		{
		}

	UniqueNonInheritedProperty_GENERATED
};

class CLASS(PropertySettings(allEntityKinds, true, false)) MultipleNonInheritedProperty : public rfk::Property
{
	public:
		int value;

		inline MultipleNonInheritedProperty(int value_):
			value{ value_ }
		{
		}

	MultipleNonInheritedProperty_GENERATED
};

File_TestProperties_GENERATED