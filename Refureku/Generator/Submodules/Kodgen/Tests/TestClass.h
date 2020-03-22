#pragma once

#include "Misc/PropertyMacros.h"
//#include "Generated/TestClass.kodgen.h"

#include <filesystem>
#include <vector>
#include <string>

namespace TestNamespace
{
	class Class1{};

	class KGClass(GenTemplate[TestTemplate], ClassProp1, ClassProp2[ClassSubProp21, ClassSubProp22], ClassProp3) TestClass final : public Class1
	{
		//_RFRK_GENERATED_TestClass

		private:
			#pragma region Variables

			KGField(FieldProp1, FieldProp2[FieldSubProp21, FieldSubProp22], FieldProp3)
			const volatile int* const&	var1;

			#pragma endregion

		protected:
			KGField(FieldProp2[])
			class Hey*		var4 = nullptr;
	
		public:
			KGField(FieldProp1)
			int var2 : 1;

			#pragma region Methods

			KGMethod(MethodProp1, MethodProp2[MethodSubProp21, MethodSubProp22], MethodProp3)
			virtual const volatile int* const& someMethod(int param1, class Hey* param2) const final;

			KGMethod(MethodProp1, MethodProp2[MethodSubProp21, MethodSubProp22], MethodProp3)
			virtual int someMethod2(int param1, class Hey* param2) final
			{

			}

			int dsomeMethod3(int) noexcept;
			//int someMethosd3(int) override;
			virtual int someMethodd3(int) const;

			#pragma endregion

			RfrkField()
			float const		var3;
	};

	enum class KGEnum(GenTemplate[TestTemplate], EnumProp1, EnumProp2[EnumSubProp21, EnumSubProp22], EnumProp3) MyEnum : uint8_t
	{
		EVal1 KGEnumVal(EnumValueProp1, EnumValueProp2[EnumValueSubProp21, EnumValueSubProp22], EnumValueProp3) = 1 << 0,
		EVal2 = 1 << 1,
		a,
		b,
		Count = 42,
		c
	};

	class KGClass() TestClass2
	{
		//_RFRK_GENERATED_TestClass2

		private:
			#pragma region Variables

			KGField()
			int				var1 = 42;
			float			var2;

			#pragma endregion

			protected:

			public:
			#pragma region Methods

			KGMethod()
			int someMethod(int);
			int dsomeMethod3(int) noexcept;
			virtual int someMethodd3(int) const;

			#pragma endregion
	};
}