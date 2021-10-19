#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "PropertyInheritance.h"

//=========================================================
//============= Class property inheritance ================
//=========================================================

TEST(PropertyInheritanceTests, CodeCoverage)
{
	//Just for code coverage
	PropertyInheritanceTestClass		a;
	PropertyInheritanceTestClassChild1	b;
	PropertyInheritanceTestClassChild2	c;

	a.methodPropertyInheritance();
	b.methodPropertyInheritance();
	c.methodPropertyInheritance();

	a.methodPropertyInheritanceOverride();
	b.methodPropertyInheritanceOverride();
	c.methodPropertyInheritanceOverride();
}

TEST(Rfk_Class_inheritProperties, InheritedUniquePropertyCorrectlyInherited)
{
	EXPECT_EQ(PropertyInheritanceTestClass::staticGetArchetype().getProperty<UniqueInheritedProperty>()->value, 0);

	//Child class inherit this property
	EXPECT_EQ(PropertyInheritanceTestClassChild1::staticGetArchetype().getProperty<UniqueInheritedProperty>()->value, 0);
}

TEST(Rfk_Class_inheritProperties, InheritedUniquePropertyOverride)
{
	EXPECT_EQ(PropertyInheritanceTestClassChild2::staticGetArchetype().getProperty<UniqueInheritedProperty>()->value, 2);
	EXPECT_EQ(PropertyInheritanceTestClassChild2::staticGetArchetype().getProperties<UniqueInheritedProperty>().size(), 1u);
}

TEST(Rfk_Class_inheritProperties, InheritedMultiplePropertyCorrectlyInherited)
{
	EXPECT_EQ(PropertyInheritanceTestClass::staticGetArchetype().getProperty<MultipleInheritedProperty>()->value, 0);

	//Child class inherit this property
	EXPECT_EQ(PropertyInheritanceTestClassChild1::staticGetArchetype().getProperty<MultipleInheritedProperty>()->value, 0);
}

TEST(Rfk_Class_inheritProperties, InheritedMultiplePropertyStacking)
{
	EXPECT_EQ(PropertyInheritanceTestClassChild2::staticGetArchetype().getProperties<MultipleInheritedProperty>().size(), 2u);
	EXPECT_EQ(PropertyInheritanceTestClassChild2::staticGetArchetype().getProperties<MultipleInheritedProperty>()[0]->value, 2u);
	EXPECT_EQ(PropertyInheritanceTestClassChild2::staticGetArchetype().getProperties<MultipleInheritedProperty>()[1]->value, 0u);
	EXPECT_EQ(PropertyInheritanceTestClassChild2::staticGetArchetype().getProperty<MultipleInheritedProperty>()->value, 2u);
}

TEST(Rfk_Class_inheritProperties, NonInheritedUniquePropertyNotInherited)
{
	EXPECT_EQ(PropertyInheritanceTestClass::staticGetArchetype().getProperty<UniqueNonInheritedProperty>()->value, 0);

	//Child class DO NOT inherit this property
	EXPECT_EQ(PropertyInheritanceTestClassChild1::staticGetArchetype().getProperty<UniqueNonInheritedProperty>(), nullptr);
}

TEST(Rfk_Class_inheritProperties, NonInheritedMulitplePropertyNotInherited)
{
	EXPECT_EQ(PropertyInheritanceTestClass::staticGetArchetype().getProperty<MultipleNonInheritedProperty>()->value, 0);

	//Child class DO NOT inherit this property
	EXPECT_EQ(PropertyInheritanceTestClassChild1::staticGetArchetype().getProperty<MultipleNonInheritedProperty>(), nullptr);
}

//=========================================================
//============= Method property inheritance ===============
//=========================================================

TEST(Rfk_Method_inheritProperties, InheritedUniquePropertyCorrectlyInherited)
{
	EXPECT_EQ(PropertyInheritanceTestClass::staticGetArchetype().getMethodByName("methodPropertyInheritance")
			  ->getProperty<UniqueInheritedProperty>()->value, 0);

	//Override method inherit this property
	EXPECT_EQ(PropertyInheritanceTestClassChild1::staticGetArchetype().getMethodByName("methodPropertyInheritance")
			  ->getProperty<UniqueInheritedProperty>()->value, 0);

	EXPECT_EQ(PropertyInheritanceTestClassChild2::staticGetArchetype().getMethodByName("methodPropertyInheritance")
			  ->getProperty<UniqueInheritedProperty>()->value, 0);
}

TEST(Rfk_Method_inheritProperties, InheritedUniquePropertyOverride)
{
	EXPECT_EQ(PropertyInheritanceTestClassChild2::staticGetArchetype().getMethodByName("methodPropertyInheritanceOverride")
			  ->getProperty<UniqueInheritedProperty>()->value, 2);
	EXPECT_EQ(PropertyInheritanceTestClassChild2::staticGetArchetype().getMethodByName("methodPropertyInheritanceOverride")
			  ->getProperties<UniqueInheritedProperty>().size(), 1u);
}

TEST(Rfk_Method_inheritProperties, InheritedMultiplePropertyCorrectlyInherited)
{
	EXPECT_EQ(PropertyInheritanceTestClass::staticGetArchetype().getMethodByName("methodPropertyInheritance")
			  ->getProperty<MultipleInheritedProperty>()->value, 0);
	EXPECT_EQ(PropertyInheritanceTestClass::staticGetArchetype().getMethodByName("methodPropertyInheritanceOverride")
			  ->getProperty<MultipleInheritedProperty>()->value, 0);

	//Override method inherit this property
	EXPECT_EQ(PropertyInheritanceTestClassChild1::staticGetArchetype().getMethodByName("methodPropertyInheritance")
			  ->getProperty<MultipleInheritedProperty>()->value, 0);
	EXPECT_EQ(PropertyInheritanceTestClassChild1::staticGetArchetype().getMethodByName("methodPropertyInheritanceOverride", rfk::EMethodFlags::Default, true)
			  ->getProperty<MultipleInheritedProperty>()->value, 0);

	EXPECT_EQ(PropertyInheritanceTestClassChild2::staticGetArchetype().getMethodByName("methodPropertyInheritance")
			  ->getProperty<MultipleInheritedProperty>()->value, 0);
}

TEST(Rfk_Method_inheritProperties, InheritedMultiplePropertyStacking)
{
	EXPECT_EQ(PropertyInheritanceTestClassChild2::staticGetArchetype().getMethodByName("methodPropertyInheritanceOverride")
			  ->getProperties<MultipleInheritedProperty>().size(), 2u);
	EXPECT_EQ(PropertyInheritanceTestClassChild2::staticGetArchetype().getMethodByName("methodPropertyInheritanceOverride")
			  ->getProperties<MultipleInheritedProperty>()[0]->value, 2u);
	EXPECT_EQ(PropertyInheritanceTestClassChild2::staticGetArchetype().getMethodByName("methodPropertyInheritanceOverride")
			  ->getProperties<MultipleInheritedProperty>()[1]->value, 0u);
	EXPECT_EQ(PropertyInheritanceTestClassChild2::staticGetArchetype().getMethodByName("methodPropertyInheritanceOverride")
			  ->getProperty<MultipleInheritedProperty>()->value, 2u);
}

TEST(Rfk_Method_inheritProperties, NonInheritedUniquePropertyNotInherited)
{
	EXPECT_EQ(PropertyInheritanceTestClass::staticGetArchetype().getMethodByName("methodPropertyInheritance")
			  ->getProperty<UniqueNonInheritedProperty>()->value, 0);

	//Override method NO NOT inherit this property
	EXPECT_EQ(PropertyInheritanceTestClassChild1::staticGetArchetype().getMethodByName("methodPropertyInheritance")
			  ->getProperty<UniqueNonInheritedProperty>(), nullptr);
	EXPECT_EQ(PropertyInheritanceTestClassChild2::staticGetArchetype().getMethodByName("methodPropertyInheritance")
			  ->getProperty<UniqueNonInheritedProperty>(), nullptr);
}

TEST(Rfk_Method_inheritProperties, NonInheritedMulitplePropertyNotInherited)
{
	EXPECT_EQ(PropertyInheritanceTestClass::staticGetArchetype().getMethodByName("methodPropertyInheritance")
			  ->getProperty<MultipleNonInheritedProperty>()->value, 0);

	//Override method DO NOT inherit this property
	EXPECT_EQ(PropertyInheritanceTestClassChild1::staticGetArchetype().getMethodByName("methodPropertyInheritance")
			  ->getProperty<MultipleNonInheritedProperty>(), nullptr);
	EXPECT_EQ(PropertyInheritanceTestClassChild2::staticGetArchetype().getMethodByName("methodPropertyInheritance")
			  ->getProperty<MultipleNonInheritedProperty>(), nullptr);
}

//=========================================================
//========= Template class property inheritance ===========
//=========================================================

TEST(Rfk_ClassTemplate_inheritProperties, PropagePropertiesToClassInstantiations)
{
	rfk::ClassTemplate const* classTemplate = rfk::entityCast<rfk::ClassTemplate>(rfk::getDatabase().getFileLevelClassByName("SingleTypeTemplateClassTemplate"));

	EXPECT_NE(classTemplate, nullptr);

	rfk::TypeTemplateArgument arg1(rfk::getArchetype<int>());
	rfk::TemplateArgument const* templateArgs[] = { &arg1 };

	rfk::ClassTemplateInstantiation const* inst = classTemplate->getTemplateInstantiation(templateArgs);

	EXPECT_NE(inst, nullptr);

	EXPECT_NE(inst->getProperty<ParseAllNested>(), nullptr);
}