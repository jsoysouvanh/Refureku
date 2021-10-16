/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Generated/PropertyInheritance.rfkh.h"

class CLASS() PropertyInheritanceTestClass
{
	private:
		METHOD()
		virtual void privateMethodPropertyInheritance(){}

		METHOD()
		virtual void privateMethodPropertyInheritance2(){}

	protected:
		METHOD()
		virtual void protectedMethodPropertyInheritance(){}

		METHOD()
		virtual void protectedMethodPropertyInheritance2(){}
		
	public:
		METHOD()
		virtual void publicMethodPropertyInheritance(){}

		METHOD()
		virtual void publicMethodPropertyInheritance2(){}

	PropertyInheritanceTestClass_GENERATED
};

class CLASS() PropertyInheritanceTestClassChild1 : public PropertyInheritanceTestClass
{
	private:
		METHOD()
		virtual void privateMethodPropertyInheritance() override {}

	protected:
		METHOD()
		virtual void protectedMethodPropertyInheritance() override {}

	public:
		METHOD()
		virtual void publicMethodPropertyInheritance() override {}

	PropertyInheritanceTestClassChild1_GENERATED
};

class CLASS() PropertyInheritanceTestClassChild2 : public PropertyInheritanceTestClassChild1
{
	private:
		METHOD()
		virtual void privateMethodPropertyInheritance() override {}

		METHOD()
		virtual void privateMethodPropertyInheritance2() override {}

	protected:
		METHOD()
		virtual void protectedMethodPropertyInheritance() override {}

		METHOD()
		virtual void protectedMethodPropertyInheritance2() override {}

	public:
		METHOD()
		virtual void publicMethodPropertyInheritance() override {}

		METHOD()
		virtual void publicMethodPropertyInheritance2() override {}

	PropertyInheritanceTestClassChild2_GENERATED
};

File_PropertyInheritance_GENERATED