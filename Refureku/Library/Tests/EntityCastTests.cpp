#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestNamespace.h"
#include "TestClass.h"
#include "TestStruct.h"
#include "TestEnum.h"
#include "TypeTemplateClassTemplate.h"

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
			v = rfk::getDatabase().getFileLevelVariableByName("var_global_extern");
			m = TestClass::staticGetArchetype().getMethodByName("getIntField");
			sm = TestClass::staticGetArchetype().getStaticMethodByName("getIntStaticField");
			func = rfk::getDatabase().getFileLevelFunctionByName("func_return_noParam");
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
//================= rfk::archetypeCast ====================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToArchetype)
{
	EXPECT_NE(rfk::archetypeCast(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToArchetype)
{
	EXPECT_NE(rfk::archetypeCast(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToArchetype)
{
	EXPECT_NE(rfk::archetypeCast(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToArchetype)
{
	EXPECT_NE(rfk::archetypeCast(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToArchetype)
{
	EXPECT_NE(rfk::archetypeCast(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToArchetype)
{
	EXPECT_NE(rfk::archetypeCast(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToArchetype)
{
	EXPECT_EQ(rfk::archetypeCast(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToArchetype)
{
	EXPECT_EQ(rfk::archetypeCast(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToArchetype)
{
	EXPECT_EQ(rfk::archetypeCast(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToArchetype)
{
	EXPECT_EQ(rfk::archetypeCast(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToArchetype)
{
	EXPECT_EQ(rfk::archetypeCast(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToArchetype)
{
	EXPECT_EQ(rfk::archetypeCast(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToArchetype)
{
	EXPECT_EQ(rfk::archetypeCast(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToArchetype)
{
	EXPECT_EQ(rfk::archetypeCast(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToArchetype)
{
	EXPECT_EQ(rfk::archetypeCast(nullptr), nullptr);
}

//=========================================================
//============ rfk::fundamentalArchetypeCast ==============
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToFundamentalArchetype)
{
	EXPECT_NE(rfk::fundamentalArchetypeCast(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToFundamentalArchetype)
{
	EXPECT_EQ(rfk::fundamentalArchetypeCast(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToFundamentalArchetype)
{
	EXPECT_EQ(rfk::fundamentalArchetypeCast(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToFundamentalArchetype)
{
	EXPECT_EQ(rfk::fundamentalArchetypeCast(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToFundamentalArchetype)
{
	EXPECT_EQ(rfk::fundamentalArchetypeCast(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToFundamentalArchetype)
{
	EXPECT_EQ(rfk::fundamentalArchetypeCast(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToFundamentalArchetype)
{
	EXPECT_EQ(rfk::fundamentalArchetypeCast(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToFundamentalArchetype)
{
	EXPECT_EQ(rfk::fundamentalArchetypeCast(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToFundamentalArchetype)
{
	EXPECT_EQ(rfk::fundamentalArchetypeCast(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToFundamentalArchetype)
{
	EXPECT_EQ(rfk::fundamentalArchetypeCast(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToFundamentalArchetype)
{
	EXPECT_EQ(rfk::fundamentalArchetypeCast(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToFundamentalArchetype)
{
	EXPECT_EQ(rfk::fundamentalArchetypeCast(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToFundamentalArchetype)
{
	EXPECT_EQ(rfk::fundamentalArchetypeCast(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToFundamentalArchetype)
{
	EXPECT_EQ(rfk::fundamentalArchetypeCast(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToFundamentalArchetype)
{
	EXPECT_EQ(rfk::fundamentalArchetypeCast(nullptr), nullptr);
}

//=========================================================
//=================== rfk::structCast =====================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToStruct)
{
	EXPECT_EQ(rfk::structCast(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToStruct)
{
	EXPECT_EQ(rfk::structCast(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToStruct)
{
	EXPECT_NE(rfk::structCast(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToStruct)
{
	EXPECT_EQ(rfk::structCast(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToStruct)
{
	EXPECT_EQ(rfk::structCast(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToStruct)
{
	EXPECT_EQ(rfk::structCast(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToStruct)
{
	EXPECT_EQ(rfk::structCast(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToStruct)
{
	EXPECT_EQ(rfk::structCast(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToStruct)
{
	EXPECT_EQ(rfk::structCast(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToStruct)
{
	EXPECT_EQ(rfk::structCast(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToStruct)
{
	EXPECT_EQ(rfk::structCast(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToStruct)
{
	EXPECT_EQ(rfk::structCast(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToStruct)
{
	EXPECT_EQ(rfk::structCast(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToStruct)
{
	EXPECT_EQ(rfk::structCast(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToStruct)
{
	EXPECT_EQ(rfk::structCast(nullptr), nullptr);
}

//=========================================================
//================ rfk::classTemplateCast =================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToClassTemplate)
{
	EXPECT_EQ(rfk::classTemplateCast(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToClassTemplate)
{
	EXPECT_EQ(rfk::classTemplateCast(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToClassTemplate)
{
	EXPECT_EQ(rfk::classTemplateCast(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToClassTemplate)
{
	EXPECT_EQ(rfk::classTemplateCast(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToClassTemplate)
{
	EXPECT_NE(rfk::classTemplateCast(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToClassTemplate)
{
	EXPECT_EQ(rfk::classTemplateCast(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToClassTemplate)
{
	EXPECT_EQ(rfk::classTemplateCast(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToClassTemplate)
{
	EXPECT_EQ(rfk::classTemplateCast(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToClassTemplate)
{
	EXPECT_EQ(rfk::classTemplateCast(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToClassTemplate)
{
	EXPECT_EQ(rfk::classTemplateCast(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToClassTemplate)
{
	EXPECT_EQ(rfk::classTemplateCast(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToClassTemplate)
{
	EXPECT_EQ(rfk::classTemplateCast(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToClassTemplate)
{
	EXPECT_EQ(rfk::classTemplateCast(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToClassTemplate)
{
	EXPECT_EQ(rfk::classTemplateCast(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToClassTemplate)
{
	EXPECT_EQ(rfk::classTemplateCast(nullptr), nullptr);
}

//=========================================================
//========== rfk::classTemplateInstantiationCast ==========
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::classTemplateInstantiationCast(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::classTemplateInstantiationCast(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::classTemplateInstantiationCast(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::classTemplateInstantiationCast(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::classTemplateInstantiationCast(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToClassTemplateInstantiation)
{
	EXPECT_NE(rfk::classTemplateInstantiationCast(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::classTemplateInstantiationCast(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::classTemplateInstantiationCast(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::classTemplateInstantiationCast(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::classTemplateInstantiationCast(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::classTemplateInstantiationCast(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::classTemplateInstantiationCast(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::classTemplateInstantiationCast(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::classTemplateInstantiationCast(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToClassTemplateInstantiation)
{
	EXPECT_EQ(rfk::classTemplateInstantiationCast(nullptr), nullptr);
}

//=========================================================
//==================== rfk::fieldCast =====================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToField)
{
	EXPECT_EQ(rfk::fieldCast(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToField)
{
	EXPECT_EQ(rfk::fieldCast(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToField)
{
	EXPECT_EQ(rfk::fieldCast(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToField)
{
	EXPECT_EQ(rfk::fieldCast(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToField)
{
	EXPECT_EQ(rfk::fieldCast(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToField)
{
	EXPECT_EQ(rfk::fieldCast(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToField)
{
	EXPECT_EQ(rfk::fieldCast(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToField)
{
	EXPECT_NE(rfk::fieldCast(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToField)
{
	EXPECT_EQ(rfk::fieldCast(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToField)
{
	EXPECT_EQ(rfk::fieldCast(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToField)
{
	EXPECT_EQ(rfk::fieldCast(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToField)
{
	EXPECT_EQ(rfk::fieldCast(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToField)
{
	EXPECT_EQ(rfk::fieldCast(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToField)
{
	EXPECT_EQ(rfk::fieldCast(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToField)
{
	EXPECT_EQ(rfk::fieldCast(nullptr), nullptr);
}

//=========================================================
//================= rfk::staticFieldCast ==================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToStaticField)
{
	EXPECT_EQ(rfk::staticFieldCast(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToStaticField)
{
	EXPECT_EQ(rfk::staticFieldCast(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToStaticField)
{
	EXPECT_EQ(rfk::staticFieldCast(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToStaticField)
{
	EXPECT_EQ(rfk::staticFieldCast(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToStaticField)
{
	EXPECT_EQ(rfk::staticFieldCast(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToStaticField)
{
	EXPECT_EQ(rfk::staticFieldCast(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToStaticField)
{
	EXPECT_EQ(rfk::staticFieldCast(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToStaticField)
{
	EXPECT_EQ(rfk::staticFieldCast(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToStaticField)
{
	EXPECT_NE(rfk::staticFieldCast(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToStaticField)
{
	EXPECT_EQ(rfk::staticFieldCast(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToStaticField)
{
	EXPECT_EQ(rfk::staticFieldCast(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToStaticField)
{
	EXPECT_EQ(rfk::staticFieldCast(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToStaticField)
{
	EXPECT_EQ(rfk::staticFieldCast(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToStaticField)
{
	EXPECT_EQ(rfk::staticFieldCast(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToStaticField)
{
	EXPECT_EQ(rfk::staticFieldCast(nullptr), nullptr);
}

//=========================================================
//=================== rfk::methodCast =====================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToMethod)
{
	EXPECT_EQ(rfk::methodCast(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToMethod)
{
	EXPECT_EQ(rfk::methodCast(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToMethod)
{
	EXPECT_EQ(rfk::methodCast(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToMethod)
{
	EXPECT_EQ(rfk::methodCast(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToMethod)
{
	EXPECT_EQ(rfk::methodCast(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToMethod)
{
	EXPECT_EQ(rfk::methodCast(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToMethod)
{
	EXPECT_EQ(rfk::methodCast(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToMethod)
{
	EXPECT_EQ(rfk::methodCast(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToMethod)
{
	EXPECT_EQ(rfk::methodCast(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToMethod)
{
	EXPECT_EQ(rfk::methodCast(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToMethod)
{
	EXPECT_NE(rfk::methodCast(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToMethod)
{
	EXPECT_EQ(rfk::methodCast(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToMethod)
{
	EXPECT_EQ(rfk::methodCast(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToMethod)
{
	EXPECT_EQ(rfk::methodCast(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToMethod)
{
	EXPECT_EQ(rfk::methodCast(nullptr), nullptr);
}

//=========================================================
//================ rfk::staticMethodCast ==================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToStaticMethod)
{
	EXPECT_EQ(rfk::staticMethodCast(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToStaticMethod)
{
	EXPECT_EQ(rfk::staticMethodCast(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToStaticMethod)
{
	EXPECT_EQ(rfk::staticMethodCast(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToStaticMethod)
{
	EXPECT_EQ(rfk::staticMethodCast(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToStaticMethod)
{
	EXPECT_EQ(rfk::staticMethodCast(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToStaticMethod)
{
	EXPECT_EQ(rfk::staticMethodCast(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToStaticMethod)
{
	EXPECT_EQ(rfk::staticMethodCast(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToStaticMethod)
{
	EXPECT_EQ(rfk::staticMethodCast(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToStaticMethod)
{
	EXPECT_EQ(rfk::staticMethodCast(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToStaticMethod)
{
	EXPECT_EQ(rfk::staticMethodCast(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToStaticMethod)
{
	EXPECT_EQ(rfk::staticMethodCast(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToStaticMethod)
{
	EXPECT_NE(rfk::staticMethodCast(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToStaticMethod)
{
	EXPECT_EQ(rfk::staticMethodCast(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToStaticMethod)
{
	EXPECT_EQ(rfk::staticMethodCast(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToStaticMethod)
{
	EXPECT_EQ(rfk::staticMethodCast(nullptr), nullptr);
}

//=========================================================
//==================== rfk::enumCast ======================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToEnum)
{
	EXPECT_EQ(rfk::enumCast(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToEnum)
{
	EXPECT_NE(rfk::enumCast(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToEnum)
{
	EXPECT_EQ(rfk::enumCast(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToEnum)
{
	EXPECT_EQ(rfk::enumCast(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToEnum)
{
	EXPECT_EQ(rfk::enumCast(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToEnum)
{
	EXPECT_EQ(rfk::enumCast(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToEnum)
{
	EXPECT_EQ(rfk::enumCast(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToEnum)
{
	EXPECT_EQ(rfk::enumCast(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToEnum)
{
	EXPECT_EQ(rfk::enumCast(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToEnum)
{
	EXPECT_EQ(rfk::enumCast(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToEnum)
{
	EXPECT_EQ(rfk::enumCast(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToEnum)
{
	EXPECT_EQ(rfk::enumCast(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToEnum)
{
	EXPECT_EQ(rfk::enumCast(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToEnum)
{
	EXPECT_EQ(rfk::enumCast(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToEnum)
{
	EXPECT_EQ(rfk::enumCast(nullptr), nullptr);
}

//=========================================================
//================= rfk::enumValueCast ====================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToEnumValue)
{
	EXPECT_EQ(rfk::enumValueCast(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToEnumValue)
{
	EXPECT_EQ(rfk::enumValueCast(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToEnumValue)
{
	EXPECT_EQ(rfk::enumValueCast(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToEnumValue)
{
	EXPECT_EQ(rfk::enumValueCast(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToEnumValue)
{
	EXPECT_EQ(rfk::enumValueCast(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToEnumValue)
{
	EXPECT_EQ(rfk::enumValueCast(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToEnumValue)
{
	EXPECT_NE(rfk::enumValueCast(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToEnumValue)
{
	EXPECT_EQ(rfk::enumValueCast(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToEnumValue)
{
	EXPECT_EQ(rfk::enumValueCast(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToEnumValue)
{
	EXPECT_EQ(rfk::enumValueCast(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToEnumValue)
{
	EXPECT_EQ(rfk::enumValueCast(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToEnumValue)
{
	EXPECT_EQ(rfk::enumValueCast(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToEnumValue)
{
	EXPECT_EQ(rfk::enumValueCast(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToEnumValue)
{
	EXPECT_EQ(rfk::enumValueCast(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToEnumValue)
{
	EXPECT_EQ(rfk::enumValueCast(nullptr), nullptr);
}

//=========================================================
//================= rfk::namespaceCast ====================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToNamespace)
{
	EXPECT_EQ(rfk::namespaceCast(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToNamespace)
{
	EXPECT_EQ(rfk::namespaceCast(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToNamespace)
{
	EXPECT_EQ(rfk::namespaceCast(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToNamespace)
{
	EXPECT_EQ(rfk::namespaceCast(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToNamespace)
{
	EXPECT_EQ(rfk::namespaceCast(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToNamespace)
{
	EXPECT_EQ(rfk::namespaceCast(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToNamespace)
{
	EXPECT_EQ(rfk::namespaceCast(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToNamespace)
{
	EXPECT_EQ(rfk::namespaceCast(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToNamespace)
{
	EXPECT_EQ(rfk::namespaceCast(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToNamespace)
{
	EXPECT_EQ(rfk::namespaceCast(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToNamespace)
{
	EXPECT_EQ(rfk::namespaceCast(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToNamespace)
{
	EXPECT_EQ(rfk::namespaceCast(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToNamespace)
{
	EXPECT_EQ(rfk::namespaceCast(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToNamespace)
{
	EXPECT_NE(rfk::namespaceCast(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToNamespace)
{
	EXPECT_EQ(rfk::namespaceCast(nullptr), nullptr);
}

//=========================================================
//================= rfk::variableCast =====================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToVariable)
{
	EXPECT_EQ(rfk::variableCast(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToVariable)
{
	EXPECT_EQ(rfk::variableCast(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToVariable)
{
	EXPECT_EQ(rfk::variableCast(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToVariable)
{
	EXPECT_EQ(rfk::variableCast(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToVariable)
{
	EXPECT_EQ(rfk::variableCast(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToVariable)
{
	EXPECT_EQ(rfk::variableCast(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToVariable)
{
	EXPECT_EQ(rfk::variableCast(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToVariable)
{
	EXPECT_EQ(rfk::variableCast(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToVariable)
{
	EXPECT_EQ(rfk::variableCast(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToVariable)
{
	EXPECT_NE(rfk::variableCast(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToVariable)
{
	EXPECT_EQ(rfk::variableCast(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToVariable)
{
	EXPECT_EQ(rfk::variableCast(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToVariable)
{
	EXPECT_EQ(rfk::variableCast(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToVariable)
{
	EXPECT_EQ(rfk::variableCast(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToVariable)
{
	EXPECT_EQ(rfk::variableCast(nullptr), nullptr);
}

//=========================================================
//================= rfk::functionCast =====================
//=========================================================

TEST_F(Rfk_entityCast, FundamentalArchetypeToFunction)
{
	EXPECT_EQ(rfk::functionCast(fa), nullptr);
}

TEST_F(Rfk_entityCast, EnumToFunction)
{
	EXPECT_EQ(rfk::functionCast(e), nullptr);
}

TEST_F(Rfk_entityCast, StructToFunction)
{
	EXPECT_EQ(rfk::functionCast(s), nullptr);
}

TEST_F(Rfk_entityCast, ClassToFunction)
{
	EXPECT_EQ(rfk::functionCast(c), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateToFunction)
{
	EXPECT_EQ(rfk::functionCast(ct), nullptr);
}

TEST_F(Rfk_entityCast, ClassTemplateInstantiationToFunction)
{
	EXPECT_EQ(rfk::functionCast(cti), nullptr);
}

TEST_F(Rfk_entityCast, EnumValueToFunction)
{
	EXPECT_EQ(rfk::functionCast(ev), nullptr);
}

TEST_F(Rfk_entityCast, FieldToFunction)
{
	EXPECT_EQ(rfk::functionCast(field), nullptr);
}

TEST_F(Rfk_entityCast, StaticFieldToFunction)
{
	EXPECT_EQ(rfk::functionCast(sf), nullptr);
}

TEST_F(Rfk_entityCast, VariableToFunction)
{
	EXPECT_EQ(rfk::functionCast(v), nullptr);
}

TEST_F(Rfk_entityCast, MethodToFunction)
{
	EXPECT_EQ(rfk::functionCast(m), nullptr);
}

TEST_F(Rfk_entityCast, StaticMethodToFunction)
{
	EXPECT_EQ(rfk::functionCast(sm), nullptr);
}

TEST_F(Rfk_entityCast, FunctionToFunction)
{
	EXPECT_NE(rfk::functionCast(func), nullptr);
}

TEST_F(Rfk_entityCast, NamespaceToFunction)
{
	EXPECT_EQ(rfk::functionCast(n), nullptr);
}

TEST_F(Rfk_entityCast, NullptrToFunction)
{
	EXPECT_EQ(rfk::functionCast(nullptr), nullptr);
}