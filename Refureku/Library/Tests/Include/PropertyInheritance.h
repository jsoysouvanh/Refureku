/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

//Properties can be forward declared
class UniqueInheritedProperty;
class MultipleInheritedProperty;
class UniqueNonInheritedProperty;
class MultipleNonInheritedProperty;

#include "Generated/PropertyInheritance.rfkh.h"

class CLASS(UniqueInheritedProperty(0),
			MultipleInheritedProperty(0),
			UniqueNonInheritedProperty(0),
			MultipleNonInheritedProperty(0)) PropertyInheritanceTestClass
{
	public:
		METHOD(UniqueInheritedProperty(0),
			   MultipleInheritedProperty(0),
			   UniqueNonInheritedProperty(0),
			   MultipleNonInheritedProperty(0))
		virtual void methodPropertyInheritance(){}

		METHOD(UniqueInheritedProperty(0),
			   MultipleInheritedProperty(0),
			   UniqueNonInheritedProperty(0),
			   MultipleNonInheritedProperty(0))
		virtual void methodPropertyInheritanceOverride(){}

	PropertyInheritanceTestClass_GENERATED
};

class CLASS() PropertyInheritanceTestClassChild1 : public PropertyInheritanceTestClass
{
	public:
		METHOD()
		virtual void methodPropertyInheritance() override {}

	PropertyInheritanceTestClassChild1_GENERATED
};

class CLASS(UniqueInheritedProperty(2),
			MultipleInheritedProperty(2)) PropertyInheritanceTestClassChild2 : public PropertyInheritanceTestClassChild1
{
	public:
		METHOD()
		virtual void methodPropertyInheritance() override {}

		METHOD(UniqueInheritedProperty(2),
			   MultipleInheritedProperty(2),
			   UniqueNonInheritedProperty(2),
			   MultipleNonInheritedProperty(2))
		virtual void methodPropertyInheritanceOverride() override {}

	PropertyInheritanceTestClassChild2_GENERATED
};

File_PropertyInheritance_GENERATED