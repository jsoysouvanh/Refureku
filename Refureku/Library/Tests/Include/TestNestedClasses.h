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

namespace rfk
{
	template <template <typename, int> typename>
	rfk::Archetype const* getArchetype() noexcept { return nullptr; }

	template <template <typename T, typename U, int Value> typename>
	rfk::Archetype const* getArchetype() noexcept { return nullptr; }

	template <template <typename, typename, std::size_t> typename>
	rfk::Archetype const* getArchetype() noexcept { return nullptr; }

	template <template <typename, typename, char> typename>
	rfk::Archetype const* getArchetype() noexcept { return nullptr; }

	template <template <typename, typename, bool> typename>
	rfk::Archetype const* getArchetype() noexcept { return nullptr; }
}

class CLASS() NonNestedNonTemplateClass
{
	private:
		template <typename T>
		class CLASS() Lvl1NestedTypeTemplateParamClass
		{
			NonNestedNonTemplateClass_Lvl1NestedTypeTemplateParamClass_GENERATED
		};

		template <typename T, int Value>
		class CLASS() Lvl1NestedTypeTemplateParamNonTypeTemplateParamClass
		{
			NonNestedNonTemplateClass_Lvl1NestedTypeTemplateParamNonTypeTemplateParamClass_GENERATED
		};

		class CLASS() Lvl1NestedNonTemplatePrivateClass
		{
			private:
				template <typename A, typename C, int Value>
				class CLASS() Lvl2NestedTemplatePrivateClass
				{
					NonNestedNonTemplateClass_Lvl1NestedNonTemplatePrivateClass_Lvl2NestedTemplatePrivateClass_GENERATED
				};

			public:
				template <typename A, typename C, std::size_t Value>
				class CLASS() Lvl2NestedTemplatePublicClass
				{
					NonNestedNonTemplateClass_Lvl1NestedNonTemplatePrivateClass_Lvl2NestedTemplatePublicClass_GENERATED
				};

			NonNestedNonTemplateClass_Lvl1NestedNonTemplatePrivateClass_GENERATED
		};

	public:
		class CLASS() Lvl1NestedNonTemplatePublicClass
		{
			private:
				template <typename A, typename C, char Value>
				class CLASS() Lvl2NestedTemplatePrivateClass2
				{
					NonNestedNonTemplateClass_Lvl1NestedNonTemplatePublicClass_Lvl2NestedTemplatePrivateClass2_GENERATED
				};

			public:
				template <typename A, typename C, bool Value>
				class CLASS() Lvl2NestedTemplatePublicClass2
				{
					NonNestedNonTemplateClass_Lvl1NestedNonTemplatePublicClass_Lvl2NestedTemplatePublicClass2_GENERATED
				};

			NonNestedNonTemplateClass_Lvl1NestedNonTemplatePublicClass_GENERATED
		};

	NonNestedNonTemplateClass_GENERATED
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