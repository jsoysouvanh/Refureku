#pragma once

#include "Generated/TestNestedEnums.rfkh.h"

class NestedEnumInspector;

class CLASS() NonNestedEnum
{
	friend NestedEnumInspector;

	private:
		class CLASS() PrivateClassNestedLvl1
		{
			friend NestedEnumInspector;

			private:
				enum class ENUM() PrivateEnumNestedLvl2
				{
					Value1,
					Value2
				};

			protected:
				enum class ENUM() ProtectedEnumNestedLvl2
				{
					Value1,
					Value2
				};

			public:
				enum class ENUM() PublicEnumNestedLvl2
				{
					Value1,
					Value2
				};

			NonNestedEnum_PrivateClassNestedLvl1_GENERATED
		};

	protected:
		enum class ENUM() ProtectedEnumNestedLvl1
		{
			Value1,
			Value2
		};

	public:
		enum class ENUM() PublicEnumNestedLvl1
		{
			Value1,
			Value2
		};

	NonNestedEnum_GENERATED 
};

File_TestNestedEnums_GENERATED

class NestedEnumInspector
{
	public:
		//NonNestedEnum nested enums
		static rfk::Archetype const* getPublicEnumNestedLvl1Archetype() noexcept
		{
			return rfk::getArchetype<NonNestedEnum::PublicEnumNestedLvl1>();
		}

		static rfk::Enum const* getPublicEnumNestedLvl1Enum() noexcept
		{
			return rfk::getEnum<NonNestedEnum::PublicEnumNestedLvl1>();
		}

		static rfk::Archetype const* getProtectedEnumNestedLvl1Archetype() noexcept
		{
			return rfk::getArchetype<NonNestedEnum::ProtectedEnumNestedLvl1>();
		}

		static rfk::Enum const* getProtectedEnumNestedLvl1Enum() noexcept
		{
			return rfk::getEnum<NonNestedEnum::ProtectedEnumNestedLvl1>();
		}

		//NonNestedClass::PrivateClassNestedLvl1 nested enums
		static rfk::Archetype const* getPrivateClassNestedLvl1_PrivateEnumNestedLvl2_Archetype() noexcept
		{
			return rfk::getArchetype<NonNestedEnum::PrivateClassNestedLvl1::PrivateEnumNestedLvl2>();
		}

		static rfk::Enum const* getPrivateClassNestedLvl1_PrivateEnumNestedLvl2_Enum() noexcept
		{
			return rfk::getEnum<NonNestedEnum::PrivateClassNestedLvl1::PrivateEnumNestedLvl2>();
		}

		static rfk::Archetype const* getPrivateClassNestedLvl1_ProtectedEnumNestedLvl2_Archetype() noexcept
		{
			return rfk::getArchetype<NonNestedEnum::PrivateClassNestedLvl1::ProtectedEnumNestedLvl2>();
		}

		static rfk::Enum const* getPrivateClassNestedLvl1_ProtectedEnumNestedLvl2_Enum() noexcept
		{
			return rfk::getEnum<NonNestedEnum::PrivateClassNestedLvl1::ProtectedEnumNestedLvl2>();
		}

		static rfk::Archetype const* getPrivateClassNestedLvl1_PublicEnumNestedLvl2_Archetype() noexcept
		{
			return rfk::getArchetype<NonNestedEnum::PrivateClassNestedLvl1::PublicEnumNestedLvl2>();
		}

		static rfk::Enum const* getPrivateClassNestedLvl1_PublicEnumNestedLvl2_Enum() noexcept
		{
			return rfk::getEnum<NonNestedEnum::PrivateClassNestedLvl1::PublicEnumNestedLvl2>();
		}

	/*
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
	*/
};