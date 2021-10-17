#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestNamespace.h"
#include "TestClass.h"
#include "TestStruct.h"
#include "TestEnum.h"
#include "SingleTypeTemplateClassTemplate.h"

class Rfk_entityCast : public testing::Test
{
	protected:
		static rfk::Entity const* fa;
		static rfk::Entity const* e;
		static rfk::Entity const* s;
		static rfk::Entity const* c;
		static rfk::Entity const* ct;
		static rfk::Entity const* cti;
		static rfk::Entity const* ev;
		static rfk::Entity const* field;
		static rfk::Entity const* sf;
		static rfk::Entity const* v;
		static rfk::Entity const* m;
		static rfk::Entity const* sm;
		static rfk::Entity const* func;
		static rfk::Entity const* n;

		static void SetUpTestSuite()
		{
			fa = rfk::getArchetype<int>();
			e = rfk::getEnum<TestEnum>();
			s = &TestStruct::staticGetArchetype();
			c = &TestClass::staticGetArchetype();
			ct = rfk::getArchetype<SingleTypeTemplateClassTemplate>();
			cti = &SingleTypeTemplateClassTemplate<int>::staticGetArchetype();
			ev = rfk::getEnum<TestEnum>()->getEnumValue(0);
			field = TestClass::staticGetArchetype().getFieldByName("_intField");
			sf = TestClass::staticGetArchetype().getStaticFieldByName("_intStaticField");
			v = rfk::getDatabase().getVariableByName("var_global_extern");
			m = TestClass::staticGetArchetype().getMethodByName("getIntField");
			sm = TestClass::staticGetArchetype().getStaticMethodByName("getIntStaticField");
			func = rfk::getDatabase().getFunctionByName("func_return_noParam");
			n = rfk::getDatabase().getNamespaceByName("test_namespace");
		}
};

rfk::Entity const* Rfk_entityCast::fa;
rfk::Entity const* Rfk_entityCast::e;
rfk::Entity const* Rfk_entityCast::s;
rfk::Entity const* Rfk_entityCast::c;
rfk::Entity const* Rfk_entityCast::ct;
rfk::Entity const* Rfk_entityCast::cti;
rfk::Entity const* Rfk_entityCast::ev;
rfk::Entity const* Rfk_entityCast::field;
rfk::Entity const* Rfk_entityCast::sf;
rfk::Entity const* Rfk_entityCast::v;
rfk::Entity const* Rfk_entityCast::m;
rfk::Entity const* Rfk_entityCast::sm;
rfk::Entity const* Rfk_entityCast::func;
rfk::Entity const* Rfk_entityCast::n;

//=========================================================
//================= Check environment =====================
//=========================================================

TEST_F(Rfk_entityCast, CheckEnv)
{
	EXPECT_NE(Rfk_entityCast::fa, nullptr);
	EXPECT_NE(Rfk_entityCast::e, nullptr);
	EXPECT_NE(Rfk_entityCast::s, nullptr);
	EXPECT_NE(Rfk_entityCast::c, nullptr);
	EXPECT_NE(Rfk_entityCast::ct, nullptr);
	EXPECT_NE(Rfk_entityCast::cti, nullptr);
	EXPECT_NE(Rfk_entityCast::ev, nullptr);
	EXPECT_NE(Rfk_entityCast::field, nullptr);
	EXPECT_NE(Rfk_entityCast::sf, nullptr);
	EXPECT_NE(Rfk_entityCast::v, nullptr);
	EXPECT_NE(Rfk_entityCast::m, nullptr);
	EXPECT_NE(Rfk_entityCast::sm, nullptr);
	EXPECT_NE(Rfk_entityCast::func, nullptr);
	EXPECT_NE(Rfk_entityCast::n, nullptr);
}

//=========================================================
//============= rfk::entityCast<Archetype> ================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToArchetype)
{
	EXPECT_NE(rfk::entityCast<rfk::Archetype>(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToArchetype)
{
	EXPECT_NE(rfk::entityCast<rfk::Archetype>(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToArchetype)
{
	EXPECT_NE(rfk::entityCast<rfk::Archetype>(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToArchetype)
{
	EXPECT_NE(rfk::entityCast<rfk::Archetype>(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToArchetype)
{
	EXPECT_NE(rfk::entityCast<rfk::Archetype>(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToArchetype)
{
	EXPECT_NE(rfk::entityCast<rfk::Archetype>(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::Archetype>(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::Archetype>(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::Archetype>(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::Archetype>(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::Archetype>(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::Archetype>(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::Archetype>(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::Archetype>(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::Archetype>(nullptr), nullptr);
}

//=========================================================
//======== rfk::entityCast<FundamentalArchetype> ==========
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToFundamentalArchetype)
{
	EXPECT_NE(rfk::entityCast<rfk::FundamentalArchetype>(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToFundamentalArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::FundamentalArchetype>(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToFundamentalArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::FundamentalArchetype>(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToFundamentalArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::FundamentalArchetype>(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToFundamentalArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::FundamentalArchetype>(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToFundamentalArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::FundamentalArchetype>(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToFundamentalArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::FundamentalArchetype>(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToFundamentalArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::FundamentalArchetype>(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToFundamentalArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::FundamentalArchetype>(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToFundamentalArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::FundamentalArchetype>(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToFundamentalArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::FundamentalArchetype>(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToFundamentalArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::FundamentalArchetype>(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToFundamentalArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::FundamentalArchetype>(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToFundamentalArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::FundamentalArchetype>(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToFundamentalArchetype)
{
	EXPECT_EQ(rfk::entityCast<rfk::FundamentalArchetype>(nullptr), nullptr);
}

//=========================================================
//=============== rfk::entityCast<Struct> =================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToStruct)
{
	EXPECT_EQ(rfk::entityCast<rfk::Struct>(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToStruct)
{
	EXPECT_EQ(rfk::entityCast<rfk::Struct>(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToStruct)
{
	EXPECT_NE(rfk::entityCast<rfk::Struct>(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToStruct)
{
	EXPECT_NE(rfk::entityCast<rfk::Struct>(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToStruct)
{
	EXPECT_NE(rfk::entityCast<rfk::Struct>(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToStruct)
{
	EXPECT_NE(rfk::entityCast<rfk::Struct>(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToStruct)
{
	EXPECT_EQ(rfk::entityCast<rfk::Struct>(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToStruct)
{
	EXPECT_EQ(rfk::entityCast<rfk::Struct>(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToStruct)
{
	EXPECT_EQ(rfk::entityCast<rfk::Struct>(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToStruct)
{
	EXPECT_EQ(rfk::entityCast<rfk::Struct>(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToStruct)
{
	EXPECT_EQ(rfk::entityCast<rfk::Struct>(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToStruct)
{
	EXPECT_EQ(rfk::entityCast<rfk::Struct>(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToStruct)
{
	EXPECT_EQ(rfk::entityCast<rfk::Struct>(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToStruct)
{
	EXPECT_EQ(rfk::entityCast<rfk::Struct>(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToStruct)
{
	EXPECT_EQ(rfk::entityCast<rfk::Struct>(nullptr), nullptr);
}

//=========================================================
//============ rfk::entityCast<ClassTemplate> =============
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToClassTemplate)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplate>(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToClassTemplate)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplate>(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToClassTemplate)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplate>(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToClassTemplate)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplate>(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToClassTemplate)
{
	EXPECT_NE(rfk::entityCast<rfk::ClassTemplate>(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToClassTemplate)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplate>(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToClassTemplate)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplate>(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToClassTemplate)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplate>(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToClassTemplate)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplate>(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToClassTemplate)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplate>(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToClassTemplate)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplate>(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToClassTemplate)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplate>(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToClassTemplate)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplate>(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToClassTemplate)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplate>(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToClassTemplate)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplate>(nullptr), nullptr);
}

//=========================================================
//====== rfk::entityCast<ClassTemplateInstantiation> ======
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplateInstantiation>(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplateInstantiation>(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplateInstantiation>(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplateInstantiation>(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplateInstantiation>(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToClassTemplateInstantiation)
{
	EXPECT_NE(rfk::entityCast<rfk::ClassTemplateInstantiation>(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplateInstantiation>(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplateInstantiation>(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplateInstantiation>(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplateInstantiation>(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplateInstantiation>(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplateInstantiation>(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplateInstantiation>(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplateInstantiation>(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::entityCast<rfk::ClassTemplateInstantiation>(nullptr), nullptr);
}

//=========================================================
//============== rfk::entityCast<FieldBase> ===============
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToFieldBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::FieldBase>(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToFieldBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::FieldBase>(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToFieldBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::FieldBase>(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToFieldBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::FieldBase>(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToFieldBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::FieldBase>(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToFieldBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::FieldBase>(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToFieldBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::FieldBase>(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToFieldBase)
{
	EXPECT_NE(rfk::entityCast<rfk::FieldBase>(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToFieldBase)
{
	EXPECT_NE(rfk::entityCast<rfk::FieldBase>(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToFieldBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::FieldBase>(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToFieldBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::FieldBase>(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToFieldBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::FieldBase>(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToFieldBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::FieldBase>(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToFieldBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::FieldBase>(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToFieldBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::FieldBase>(nullptr), nullptr);
}

//=========================================================
//================ rfk::entityCast<Field> =================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToField)
{
	EXPECT_EQ(rfk::entityCast<rfk::Field>(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToField)
{
	EXPECT_EQ(rfk::entityCast<rfk::Field>(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToField)
{
	EXPECT_EQ(rfk::entityCast<rfk::Field>(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToField)
{
	EXPECT_EQ(rfk::entityCast<rfk::Field>(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToField)
{
	EXPECT_EQ(rfk::entityCast<rfk::Field>(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToField)
{
	EXPECT_EQ(rfk::entityCast<rfk::Field>(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToField)
{
	EXPECT_EQ(rfk::entityCast<rfk::Field>(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToField)
{
	EXPECT_NE(rfk::entityCast<rfk::Field>(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToField)
{
	EXPECT_EQ(rfk::entityCast<rfk::Field>(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToField)
{
	EXPECT_EQ(rfk::entityCast<rfk::Field>(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToField)
{
	EXPECT_EQ(rfk::entityCast<rfk::Field>(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToField)
{
	EXPECT_EQ(rfk::entityCast<rfk::Field>(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToField)
{
	EXPECT_EQ(rfk::entityCast<rfk::Field>(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToField)
{
	EXPECT_EQ(rfk::entityCast<rfk::Field>(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToField)
{
	EXPECT_EQ(rfk::entityCast<rfk::Field>(nullptr), nullptr);
}

//=========================================================
//============= rfk::entityCast<StaticField> ==============
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToStaticField)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticField>(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToStaticField)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticField>(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToStaticField)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticField>(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToStaticField)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticField>(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToStaticField)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticField>(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToStaticField)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticField>(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToStaticField)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticField>(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToStaticField)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticField>(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToStaticField)
{
	EXPECT_NE(rfk::entityCast<rfk::StaticField>(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToStaticField)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticField>(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToStaticField)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticField>(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToStaticField)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticField>(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToStaticField)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticField>(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToStaticField)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticField>(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToStaticField)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticField>(nullptr), nullptr);
}

//=========================================================
//============= rfk::entityCast<MethodBase> ===============
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToMethodBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::MethodBase>(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToMethodBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::MethodBase>(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToMethodBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::MethodBase>(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToMethodBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::MethodBase>(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToMethodBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::MethodBase>(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToMethodBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::MethodBase>(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToMethodBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::MethodBase>(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToMethodBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::MethodBase>(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToMethodBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::MethodBase>(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToMethodBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::MethodBase>(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToMethodBase)
{
	EXPECT_NE(rfk::entityCast<rfk::MethodBase>(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToMethodBase)
{
	EXPECT_NE(rfk::entityCast<rfk::MethodBase>(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToMethodBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::MethodBase>(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToMethodBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::MethodBase>(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToMethodBase)
{
	EXPECT_EQ(rfk::entityCast<rfk::MethodBase>(nullptr), nullptr);
}

//=========================================================
//=============== rfk::entityCast<Method> =================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::Method>(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::Method>(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::Method>(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::Method>(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::Method>(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::Method>(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::Method>(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::Method>(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::Method>(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::Method>(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToMethod)
{
	EXPECT_NE(rfk::entityCast<rfk::Method>(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::Method>(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::Method>(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::Method>(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::Method>(nullptr), nullptr);
}

//=========================================================
//============ rfk::entityCast<StaticMethod> ==============
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToStaticMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticMethod>(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToStaticMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticMethod>(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToStaticMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticMethod>(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToStaticMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticMethod>(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToStaticMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticMethod>(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToStaticMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticMethod>(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToStaticMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticMethod>(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToStaticMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticMethod>(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToStaticMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticMethod>(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToStaticMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticMethod>(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToStaticMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticMethod>(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToStaticMethod)
{
	EXPECT_NE(rfk::entityCast<rfk::StaticMethod>(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToStaticMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticMethod>(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToStaticMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticMethod>(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToStaticMethod)
{
	EXPECT_EQ(rfk::entityCast<rfk::StaticMethod>(nullptr), nullptr);
}

//=========================================================
//================ rfk::entityCast<Enum> ==================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToEnum)
{
	EXPECT_EQ(rfk::entityCast<rfk::Enum>(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToEnum)
{
	EXPECT_NE(rfk::entityCast<rfk::Enum>(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToEnum)
{
	EXPECT_EQ(rfk::entityCast<rfk::Enum>(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToEnum)
{
	EXPECT_EQ(rfk::entityCast<rfk::Enum>(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToEnum)
{
	EXPECT_EQ(rfk::entityCast<rfk::Enum>(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToEnum)
{
	EXPECT_EQ(rfk::entityCast<rfk::Enum>(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToEnum)
{
	EXPECT_EQ(rfk::entityCast<rfk::Enum>(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToEnum)
{
	EXPECT_EQ(rfk::entityCast<rfk::Enum>(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToEnum)
{
	EXPECT_EQ(rfk::entityCast<rfk::Enum>(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToEnum)
{
	EXPECT_EQ(rfk::entityCast<rfk::Enum>(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToEnum)
{
	EXPECT_EQ(rfk::entityCast<rfk::Enum>(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToEnum)
{
	EXPECT_EQ(rfk::entityCast<rfk::Enum>(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToEnum)
{
	EXPECT_EQ(rfk::entityCast<rfk::Enum>(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToEnum)
{
	EXPECT_EQ(rfk::entityCast<rfk::Enum>(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToEnum)
{
	EXPECT_EQ(rfk::entityCast<rfk::Enum>(nullptr), nullptr);
}

//=========================================================
//============= rfk::entityCast<EnumValue> ================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToEnumValue)
{
	EXPECT_EQ(rfk::entityCast<rfk::EnumValue>(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToEnumValue)
{
	EXPECT_EQ(rfk::entityCast<rfk::EnumValue>(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToEnumValue)
{
	EXPECT_EQ(rfk::entityCast<rfk::EnumValue>(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToEnumValue)
{
	EXPECT_EQ(rfk::entityCast<rfk::EnumValue>(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToEnumValue)
{
	EXPECT_EQ(rfk::entityCast<rfk::EnumValue>(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToEnumValue)
{
	EXPECT_EQ(rfk::entityCast<rfk::EnumValue>(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToEnumValue)
{
	EXPECT_NE(rfk::entityCast<rfk::EnumValue>(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToEnumValue)
{
	EXPECT_EQ(rfk::entityCast<rfk::EnumValue>(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToEnumValue)
{
	EXPECT_EQ(rfk::entityCast<rfk::EnumValue>(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToEnumValue)
{
	EXPECT_EQ(rfk::entityCast<rfk::EnumValue>(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToEnumValue)
{
	EXPECT_EQ(rfk::entityCast<rfk::EnumValue>(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToEnumValue)
{
	EXPECT_EQ(rfk::entityCast<rfk::EnumValue>(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToEnumValue)
{
	EXPECT_EQ(rfk::entityCast<rfk::EnumValue>(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToEnumValue)
{
	EXPECT_EQ(rfk::entityCast<rfk::EnumValue>(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToEnumValue)
{
	EXPECT_EQ(rfk::entityCast<rfk::EnumValue>(nullptr), nullptr);
}

//=========================================================
//============= rfk::entityCast<Namespace> ================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToNamespace)
{
	EXPECT_EQ(rfk::entityCast<rfk::Namespace>(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToNamespace)
{
	EXPECT_EQ(rfk::entityCast<rfk::Namespace>(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToNamespace)
{
	EXPECT_EQ(rfk::entityCast<rfk::Namespace>(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToNamespace)
{
	EXPECT_EQ(rfk::entityCast<rfk::Namespace>(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToNamespace)
{
	EXPECT_EQ(rfk::entityCast<rfk::Namespace>(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToNamespace)
{
	EXPECT_EQ(rfk::entityCast<rfk::Namespace>(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToNamespace)
{
	EXPECT_EQ(rfk::entityCast<rfk::Namespace>(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToNamespace)
{
	EXPECT_EQ(rfk::entityCast<rfk::Namespace>(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToNamespace)
{
	EXPECT_EQ(rfk::entityCast<rfk::Namespace>(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToNamespace)
{
	EXPECT_EQ(rfk::entityCast<rfk::Namespace>(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToNamespace)
{
	EXPECT_EQ(rfk::entityCast<rfk::Namespace>(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToNamespace)
{
	EXPECT_EQ(rfk::entityCast<rfk::Namespace>(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToNamespace)
{
	EXPECT_EQ(rfk::entityCast<rfk::Namespace>(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToNamespace)
{
	EXPECT_NE(rfk::entityCast<rfk::Namespace>(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToNamespace)
{
	EXPECT_EQ(rfk::entityCast<rfk::Namespace>(nullptr), nullptr);
}

//=========================================================
//============= rfk::entityCast<Variable> =================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToVariable)
{
	EXPECT_EQ(rfk::entityCast<rfk::Variable>(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToVariable)
{
	EXPECT_EQ(rfk::entityCast<rfk::Variable>(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToVariable)
{
	EXPECT_EQ(rfk::entityCast<rfk::Variable>(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToVariable)
{
	EXPECT_EQ(rfk::entityCast<rfk::Variable>(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToVariable)
{
	EXPECT_EQ(rfk::entityCast<rfk::Variable>(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToVariable)
{
	EXPECT_EQ(rfk::entityCast<rfk::Variable>(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToVariable)
{
	EXPECT_EQ(rfk::entityCast<rfk::Variable>(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToVariable)
{
	EXPECT_EQ(rfk::entityCast<rfk::Variable>(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToVariable)
{
	EXPECT_EQ(rfk::entityCast<rfk::Variable>(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToVariable)
{
	EXPECT_NE(rfk::entityCast<rfk::Variable>(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToVariable)
{
	EXPECT_EQ(rfk::entityCast<rfk::Variable>(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToVariable)
{
	EXPECT_EQ(rfk::entityCast<rfk::Variable>(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToVariable)
{
	EXPECT_EQ(rfk::entityCast<rfk::Variable>(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToVariable)
{
	EXPECT_EQ(rfk::entityCast<rfk::Variable>(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToVariable)
{
	EXPECT_EQ(rfk::entityCast<rfk::Variable>(nullptr), nullptr);
}

//=========================================================
//============= rfk::entityCast<Function> =================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToFunction)
{
	EXPECT_EQ(rfk::entityCast<rfk::Function>(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToFunction)
{
	EXPECT_EQ(rfk::entityCast<rfk::Function>(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToFunction)
{
	EXPECT_EQ(rfk::entityCast<rfk::Function>(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToFunction)
{
	EXPECT_EQ(rfk::entityCast<rfk::Function>(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToFunction)
{
	EXPECT_EQ(rfk::entityCast<rfk::Function>(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToFunction)
{
	EXPECT_EQ(rfk::entityCast<rfk::Function>(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToFunction)
{
	EXPECT_EQ(rfk::entityCast<rfk::Function>(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToFunction)
{
	EXPECT_EQ(rfk::entityCast<rfk::Function>(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToFunction)
{
	EXPECT_EQ(rfk::entityCast<rfk::Function>(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToFunction)
{
	EXPECT_EQ(rfk::entityCast<rfk::Function>(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToFunction)
{
	EXPECT_EQ(rfk::entityCast<rfk::Function>(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToFunction)
{
	EXPECT_EQ(rfk::entityCast<rfk::Function>(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToFunction)
{
	EXPECT_NE(rfk::entityCast<rfk::Function>(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToFunction)
{
	EXPECT_EQ(rfk::entityCast<rfk::Function>(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToFunction)
{
	EXPECT_EQ(rfk::entityCast<rfk::Function>(nullptr), nullptr);
}