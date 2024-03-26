#pragma once

#include "Refureku/TypeInfo/Archetypes/Archetype.h"
#include "Refureku/TypeInfo/Archetypes/Enum.h"
#include "Generated/TestNestedEnums.rfkh.h"

class NestedEnumInspector;

class CLASS() NonNestedEnum
{
	friend NestedEnumInspector;

	private:
		enum class ENUM() PrivateEnumNestedLvl1
		{
			Value1,
			Value2
		};

	NonNestedEnum_GENERATED 
};

class CLASS() NonNestedEnum1
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

			NonNestedEnum1_PrivateClassNestedLvl1_GENERATED
		};

	NonNestedEnum1_GENERATED 
};

class CLASS() NonNestedEnum2
{
	friend NestedEnumInspector;

	private:
		class CLASS() PrivateClassNestedLvl1
		{
			friend NestedEnumInspector;

			public:
				enum class ENUM() PublicEnumNestedLvl2
				{
					Value1,
					Value2
				};

			NonNestedEnum2_PrivateClassNestedLvl1_GENERATED
		};

	NonNestedEnum2_GENERATED 
};

class CLASS() NonNestedEnum3
{
	friend NestedEnumInspector;

	public:
		enum class ENUM() PublicEnumNestedLvl1
		{
			Value1,
			Value2
		};

	NonNestedEnum3_GENERATED 
}; 

File_TestNestedEnums_GENERATED

class NestedEnumInspector
{
	public:
		//NonNestedEnum nested enums
		static rfk::Archetype const* getPublicEnumNestedLvl1Archetype() noexcept
		{
			return rfk::getArchetype<NonNestedEnum3::PublicEnumNestedLvl1>();
		}

		static rfk::Enum const* getPublicEnumNestedLvl1Enum() noexcept
		{
			return rfk::getEnum<NonNestedEnum3::PublicEnumNestedLvl1>();
		}

		static rfk::Archetype const* getPrivateEnumNestedLvl1Archetype() noexcept
		{
			return rfk::getArchetype<NonNestedEnum::PrivateEnumNestedLvl1>();
		}

		static rfk::Enum const* getProtectedEnumNestedLvl1Enum() noexcept
		{
			return rfk::getEnum<NonNestedEnum::PrivateEnumNestedLvl1>();
		}

		//NonNestedClass::PrivateClassNestedLvl1 nested enums
		static rfk::Archetype const* getPrivateClassNestedLvl1_PrivateEnumNestedLvl2_Archetype() noexcept
		{
			return rfk::getArchetype<NonNestedEnum1::PrivateClassNestedLvl1::PrivateEnumNestedLvl2>();
		}

		static rfk::Enum const* getPrivateClassNestedLvl1_PrivateEnumNestedLvl2_Enum() noexcept
		{
			return rfk::getEnum<NonNestedEnum1::PrivateClassNestedLvl1::PrivateEnumNestedLvl2>();
		}

		static rfk::Archetype const* getPrivateClassNestedLvl1_PublicEnumNestedLvl2_Archetype() noexcept
		{
			return rfk::getArchetype<NonNestedEnum2::PrivateClassNestedLvl1::PublicEnumNestedLvl2>();
		}

		static rfk::Enum const* getPrivateClassNestedLvl1_PublicEnumNestedLvl2_Enum() noexcept
		{
			return rfk::getEnum<NonNestedEnum2::PrivateClassNestedLvl1::PublicEnumNestedLvl2>();
		}
};