/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Generated/TestNestedClasses.rfkh.h"

class NestedClassInspector;

class CLASS() NonNestedClass
{
	friend NestedClassInspector;

	private:
		class CLASS() PrivateClassNestedLvl1
		{
			friend NestedClassInspector;

			private:
				class CLASS() PrivateClassNestedLvl2
				{
					NonNestedClass_PrivateClassNestedLvl1_PrivateClassNestedLvl2_GENERATED
				};

			protected:
				class CLASS() ProtectedClassNestedLvl2
				{
					NonNestedClass_PrivateClassNestedLvl1_ProtectedClassNestedLvl2_GENERATED
				};

			public:
				class CLASS() PublicClassNestedLvl2
				{
					NonNestedClass_PrivateClassNestedLvl1_PublicClassNestedLvl2_GENERATED
				};

			NonNestedClass_PrivateClassNestedLvl1_GENERATED
		};

	protected:
		class CLASS() ProtectedClassNestedLvl1
		{
			friend NestedClassInspector;

			private:
				class CLASS() PrivateClassNestedLvl2
				{
					NonNestedClass_ProtectedClassNestedLvl1_PrivateClassNestedLvl2_GENERATED
				};

			protected:
				class CLASS() ProtectedClassNestedLvl2
				{
					NonNestedClass_ProtectedClassNestedLvl1_ProtectedClassNestedLvl2_GENERATED
				};

			public:
				class CLASS() PublicClassNestedLvl2
				{
					NonNestedClass_ProtectedClassNestedLvl1_PublicClassNestedLvl2_GENERATED
				};

			NonNestedClass_ProtectedClassNestedLvl1_GENERATED
		};

	public:
		class CLASS() PublicClassNestedLvl1
		{
			NonNestedClass_PublicClassNestedLvl1_GENERATED
		};

	NonNestedClass_GENERATED 
};

File_TestNestedClasses_GENERATED

class NestedClassInspector
{
	public:
		//NonNestedClass nested classes
		static rfk::Archetype const* getPrivateClassNestedLvl1Archetype() noexcept
		{
			return rfk::getArchetype<NonNestedClass::PrivateClassNestedLvl1>();
		}

		static rfk::Archetype const* getProtectedClassNestedLvl1Archetype() noexcept
		{
			return rfk::getArchetype<NonNestedClass::ProtectedClassNestedLvl1>();
		}

		//NonNestedClass::PrivateClassNestedLvl1 nested classes
		static rfk::Archetype const* getPrivateClassNestedLvl1_PrivateClassNestedLvl2_Archetype() noexcept
		{
			return rfk::getArchetype<NonNestedClass::PrivateClassNestedLvl1::PrivateClassNestedLvl2>();
		}
		
		static rfk::Archetype const* getPrivateClassNestedLvl1_ProtectedClassNestedLvl2_Archetype() noexcept
		{
			return rfk::getArchetype<NonNestedClass::PrivateClassNestedLvl1::ProtectedClassNestedLvl2>();
		}

		static rfk::Archetype const* getPrivateClassNestedLvl1_PublicClassNestedLvl2_Archetype() noexcept
		{
			return rfk::getArchetype<NonNestedClass::PrivateClassNestedLvl1::PublicClassNestedLvl2>();
		}

		//NonNestedClass::ProtectedClassNestedLvl1 nested classes
		static rfk::Archetype const* getProtectedClassNestedLvl1_PrivateClassNestedLvl2_Archetype() noexcept
		{
			return rfk::getArchetype<NonNestedClass::ProtectedClassNestedLvl1::PrivateClassNestedLvl2>();
		}

		static rfk::Archetype const* getProtectedClassNestedLvl1_ProtectedClassNestedLvl2_Archetype() noexcept
		{
			return rfk::getArchetype<NonNestedClass::ProtectedClassNestedLvl1::ProtectedClassNestedLvl2>();
		}

		static rfk::Archetype const* getProtectedClassNestedLvl1_PublicClassNestedLvl2_Archetype() noexcept
		{
			return rfk::getArchetype<NonNestedClass::ProtectedClassNestedLvl1::PublicClassNestedLvl2>();
		}
};