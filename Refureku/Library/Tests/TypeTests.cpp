#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestClass.h"

//=========================================================
//=================== rfk::getType<> ======================
//=========================================================

TEST(Rfk_getType, AddressCheck)
{
	EXPECT_EQ(&rfk::getType<TestClass>(), &rfk::getType<TestClass>());
}

//=========================================================
//============== Type::getTypePartsCount ==================
//=========================================================

TEST(Rfk_Type_getTypePartsCount, ValueType)
{
	EXPECT_EQ(rfk::getType<TestClass>().getTypePartsCount(), 1u);
}

TEST(Rfk_Type_getTypePartsCount, ConstValueType)
{
	EXPECT_EQ(rfk::getType<TestClass const>().getTypePartsCount(), 1u);
}

TEST(Rfk_Type_getTypePartsCount, NonConstLValueType)
{
	EXPECT_EQ(rfk::getType<TestClass&>().getTypePartsCount(), 2u);
}

TEST(Rfk_Type_getTypePartsCount, ConstLValueType)
{
	EXPECT_EQ(rfk::getType<TestClass const&>().getTypePartsCount(), 2u);
}

TEST(Rfk_Type_getTypePartsCount, RValueType)
{
	EXPECT_EQ(rfk::getType<TestClass&&>().getTypePartsCount(), 2u);
}

TEST(Rfk_Type_getTypePartsCount, NonConstTypePtr)
{
	EXPECT_EQ(rfk::getType<TestClass*>().getTypePartsCount(), 2u);
}

TEST(Rfk_Type_getTypePartsCount, ConstTypePtr)
{
	EXPECT_EQ(rfk::getType<TestClass const*>().getTypePartsCount(), 2u);
}

TEST(Rfk_Type_getTypePartsCount, TypeConstPtr)
{
	EXPECT_EQ(rfk::getType<TestClass* const>().getTypePartsCount(), 2u);
}

TEST(Rfk_Type_getTypePartsCount, ArrayType)
{
	EXPECT_EQ(rfk::getType<TestClass[5]>().getTypePartsCount(), 2u);
}

TEST(Rfk_Type_getTypePartsCount, ArrayTypeArraySize)
{
	EXPECT_EQ(rfk::getType<TestClass[42]>().getTypePartsCount(), 2u);
}

TEST(Rfk_Type_getTypePartsCount, VolatileType)
{
	EXPECT_EQ(rfk::getType<volatile TestClass>().getTypePartsCount(), 1u);
}

//=========================================================
//================= rfk::getTypePartAt ====================
//=========================================================

TEST(Rfk_Type_getTypePartAt, ValueType)
{
	EXPECT_TRUE(rfk::getType<TestClass>().getTypePartAt(0).isValue());
}

TEST(Rfk_Type_getTypePartAt, ConstValueType)
{
	EXPECT_TRUE(rfk::getType<TestClass const>().getTypePartAt(0).isValue());
}

TEST(Rfk_Type_getTypePartAt, NonConstLValueType)
{
	EXPECT_TRUE(rfk::getType<TestClass&>().getTypePartAt(0).isLValueReference());
	EXPECT_TRUE(rfk::getType<TestClass&>().getTypePartAt(1).isValue());
}

TEST(Rfk_Type_getTypePartAt, ConstLValueType)
{
	EXPECT_TRUE(rfk::getType<TestClass const&>().getTypePartAt(0).isLValueReference());
	EXPECT_TRUE(rfk::getType<TestClass const&>().getTypePartAt(1).isValue());
}

TEST(Rfk_Type_getTypePartAt, RValueType)
{
	EXPECT_TRUE(rfk::getType<TestClass&&>().getTypePartAt(0).isRValueReference());
	EXPECT_TRUE(rfk::getType<TestClass&&>().getTypePartAt(1).isValue());
}

TEST(Rfk_Type_getTypePartAt, NonConstTypePtr)
{
	EXPECT_TRUE(rfk::getType<TestClass*>().getTypePartAt(0).isPointer());
	EXPECT_TRUE(rfk::getType<TestClass*>().getTypePartAt(1).isValue());
}

TEST(Rfk_Type_getTypePartAt, ConstTypePtr)
{
	EXPECT_TRUE(rfk::getType<TestClass const*>().getTypePartAt(0).isPointer());
	EXPECT_TRUE(rfk::getType<TestClass const*>().getTypePartAt(1).isValue());
}

TEST(Rfk_Type_getTypePartAt, TypeConstPtr)
{
	EXPECT_TRUE(rfk::getType<TestClass* const>().getTypePartAt(0).isPointer());
	EXPECT_TRUE(rfk::getType<TestClass* const>().getTypePartAt(1).isValue());
}

TEST(Rfk_Type_getTypePartAt, ArrayType)
{
	EXPECT_TRUE(rfk::getType<TestClass[5]>().getTypePartAt(0).isCArray());
	EXPECT_TRUE(rfk::getType<TestClass[5]>().getTypePartAt(1).isValue());
}

TEST(Rfk_Type_getTypePartAt, VolatileType)
{
	EXPECT_TRUE(rfk::getType<volatile TestClass>().getTypePartAt(0).isValue());
}

//=========================================================
//=================== rfk::isPointer ======================
//=========================================================

TEST(Rfk_Type_isPointer, ValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass>().isPointer());
}

TEST(Rfk_Type_isPointer, ConstValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass const>().isPointer());
}

TEST(Rfk_Type_isPointer, NonConstLValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass&>().isPointer());
}

TEST(Rfk_Type_isPointer, ConstLValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass const&>().isPointer());
}

TEST(Rfk_Type_isPointer, RValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass&&>().isPointer());
}

TEST(Rfk_Type_isPointer, NonConstTypePtr)
{
	EXPECT_TRUE(rfk::getType<TestClass*>().isPointer());
}

TEST(Rfk_Type_isPointer, ConstTypePtr)
{
	EXPECT_TRUE(rfk::getType<TestClass const*>().isPointer());
}

TEST(Rfk_Type_isPointer, TypeConstPtr)
{
	EXPECT_TRUE(rfk::getType<TestClass* const>().isPointer());
}

TEST(Rfk_Type_isPointer, ArrayType)
{
	EXPECT_FALSE(rfk::getType<TestClass[5]>().isPointer());
}

TEST(Rfk_Type_isPointer, VolatileType)
{
	EXPECT_FALSE(rfk::getType<volatile TestClass>().isPointer());
}

//=========================================================
//=============== rfk::isLValueReference ==================
//=========================================================

TEST(Rfk_Type_isLValueReference, ValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass>().isLValueReference());
}

TEST(Rfk_Type_isLValueReference, ConstValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass const>().isLValueReference());
}

TEST(Rfk_Type_isLValueReference, NonConstLValueType)
{
	EXPECT_TRUE(rfk::getType<TestClass&>().isLValueReference());
}

TEST(Rfk_Type_isLValueReference, ConstLValueType)
{
	EXPECT_TRUE(rfk::getType<TestClass const&>().isLValueReference());
}

TEST(Rfk_Type_isLValueReference, RValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass&&>().isLValueReference());
}

TEST(Rfk_Type_isLValueReference, NonConstTypePtr)
{
	EXPECT_FALSE(rfk::getType<TestClass*>().isLValueReference());
}

TEST(Rfk_Type_isLValueReference, ConstTypePtr)
{
	EXPECT_FALSE(rfk::getType<TestClass const*>().isLValueReference());
}

TEST(Rfk_Type_isLValueReference, TypeConstPtr)
{
	EXPECT_FALSE(rfk::getType<TestClass* const>().isLValueReference());
}

TEST(Rfk_Type_isLValueReference, ArrayType)
{
	EXPECT_FALSE(rfk::getType<TestClass[5]>().isLValueReference());
}

TEST(Rfk_Type_isLValueReference, VolatileType)
{
	EXPECT_FALSE(rfk::getType<volatile TestClass>().isLValueReference());
}

//=========================================================
//=============== rfk::isRValueReference ==================
//=========================================================

TEST(Rfk_Type_isRValueReference, ValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass>().isRValueReference());
}

TEST(Rfk_Type_isRValueReference, ConstValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass const>().isRValueReference());
}

TEST(Rfk_Type_isRValueReference, NonConstLValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass&>().isRValueReference());
}

TEST(Rfk_Type_isRValueReference, ConstLValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass const&>().isRValueReference());
}

TEST(Rfk_Type_isRValueReference, RValueType)
{
	EXPECT_TRUE(rfk::getType<TestClass&&>().isRValueReference());
}

TEST(Rfk_Type_isRValueReference, NonConstTypePtr)
{
	EXPECT_FALSE(rfk::getType<TestClass*>().isRValueReference());
}

TEST(Rfk_Type_isRValueReference, ConstTypePtr)
{
	EXPECT_FALSE(rfk::getType<TestClass const*>().isRValueReference());
}

TEST(Rfk_Type_isRValueReference, TypeConstPtr)
{
	EXPECT_FALSE(rfk::getType<TestClass* const>().isRValueReference());
}

TEST(Rfk_Type_isRValueReference, ArrayType)
{
	EXPECT_FALSE(rfk::getType<TestClass[5]>().isRValueReference());
}

TEST(Rfk_Type_isRValueReference, VolatileType)
{
	EXPECT_FALSE(rfk::getType<volatile TestClass>().isRValueReference());
}

//=========================================================
//=================== rfk::isCArray =======================
//=========================================================

TEST(Rfk_Type_isCArray, ValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass>().isCArray());
}

TEST(Rfk_Type_isCArray, ConstValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass const>().isCArray());
}

TEST(Rfk_Type_isCArray, NonConstLValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass&>().isCArray());
}

TEST(Rfk_Type_isCArray, ConstLValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass const&>().isCArray());
}

TEST(Rfk_Type_isCArray, RValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass&&>().isCArray());
}

TEST(Rfk_Type_isCArray, NonConstTypePtr)
{
	EXPECT_FALSE(rfk::getType<TestClass*>().isCArray());
}

TEST(Rfk_Type_isCArray, ConstTypePtr)
{
	EXPECT_FALSE(rfk::getType<TestClass const*>().isCArray());
}

TEST(Rfk_Type_isCArray, TypeConstPtr)
{
	EXPECT_FALSE(rfk::getType<TestClass* const>().isCArray());
}

TEST(Rfk_Type_isCArray, ArrayType)
{
	EXPECT_TRUE(rfk::getType<TestClass[5]>().isCArray());
}

TEST(Rfk_Type_isCArray, VolatileType)
{
	EXPECT_FALSE(rfk::getType<volatile TestClass>().isCArray());
}

//=========================================================
//=================== rfk::isValue ========================
//=========================================================

TEST(Rfk_Type_isValue, ValueType)
{
	EXPECT_TRUE(rfk::getType<TestClass>().isValue());
}

TEST(Rfk_Type_isValue, ConstValueType)
{
	EXPECT_TRUE(rfk::getType<TestClass const>().isValue());
}

TEST(Rfk_Type_isValue, NonConstLValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass&>().isValue());
}

TEST(Rfk_Type_isValue, ConstLValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass const&>().isValue());
}

TEST(Rfk_Type_isValue, RValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass&&>().isValue());
}

TEST(Rfk_Type_isValue, NonConstTypePtr)
{
	EXPECT_FALSE(rfk::getType<TestClass*>().isValue());
}

TEST(Rfk_Type_isValue, ConstTypePtr)
{
	EXPECT_FALSE(rfk::getType<TestClass const*>().isValue());
}

TEST(Rfk_Type_isValue, TypeConstPtr)
{
	EXPECT_FALSE(rfk::getType<TestClass* const>().isValue());
}

TEST(Rfk_Type_isValue, ArrayType)
{
	EXPECT_FALSE(rfk::getType<TestClass[5]>().isValue());
}

TEST(Rfk_Type_isValue, VolatileType)
{
	EXPECT_TRUE(rfk::getType<volatile TestClass>().isValue());
}

//=========================================================
//=================== rfk::isConst ========================
//=========================================================

TEST(Rfk_Type_isConst, ValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass>().isConst());
}

TEST(Rfk_Type_isConst, ConstValueType)
{
	EXPECT_TRUE(rfk::getType<TestClass const>().isConst());
}

TEST(Rfk_Type_isConst, NonConstLValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass&>().isConst());
}

TEST(Rfk_Type_isConst, ConstLValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass const&>().isConst());
}

TEST(Rfk_Type_isConst, RValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass&&>().isConst());
}

TEST(Rfk_Type_isConst, NonConstTypePtr)
{
	EXPECT_FALSE(rfk::getType<TestClass*>().isConst());
}

TEST(Rfk_Type_isConst, ConstTypePtr)
{
	EXPECT_FALSE(rfk::getType<TestClass const*>().isConst());
}

TEST(Rfk_Type_isConst, TypeConstPtr)
{
	EXPECT_TRUE(rfk::getType<TestClass* const>().isConst());
}

TEST(Rfk_Type_isConst, ArrayType)
{
	EXPECT_FALSE(rfk::getType<TestClass[5]>().isConst());
}

TEST(Rfk_Type_isConst, VolatileType)
{
	EXPECT_FALSE(rfk::getType<volatile TestClass>().isConst());
}

//=========================================================
//================== rfk::isVolatile ======================
//=========================================================

TEST(Rfk_Type_isVolatile, ValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass>().isVolatile());
}

TEST(Rfk_Type_isVolatile, ConstValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass const>().isVolatile());
}

TEST(Rfk_Type_isVolatile, NonConstLValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass&>().isVolatile());
}

TEST(Rfk_Type_isVolatile, ConstLValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass const&>().isVolatile());
}

TEST(Rfk_Type_isVolatile, RValueType)
{
	EXPECT_FALSE(rfk::getType<TestClass&&>().isVolatile());
}

TEST(Rfk_Type_isVolatile, NonConstTypePtr)
{
	EXPECT_FALSE(rfk::getType<TestClass*>().isVolatile());
}

TEST(Rfk_Type_isVolatile, ConstTypePtr)
{
	EXPECT_FALSE(rfk::getType<TestClass const*>().isVolatile());
}

TEST(Rfk_Type_isVolatile, TypeConstPtr)
{
	EXPECT_FALSE(rfk::getType<TestClass* const>().isVolatile());
}

TEST(Rfk_Type_isVolatile, ArrayType)
{
	EXPECT_FALSE(rfk::getType<TestClass[5]>().isVolatile());
}

TEST(Rfk_Type_isVolatile, VolatileType)
{
	EXPECT_TRUE(rfk::getType<volatile TestClass>().isVolatile());
}

//=========================================================
//================= rfk::getCArraySize ====================
//=========================================================

TEST(Rfk_Type_getCArraySize, ValueType)
{
	EXPECT_EQ(rfk::getType<TestClass>().getCArraySize(), 0u);
}

TEST(Rfk_Type_getCArraySize, ConstValueType)
{
	EXPECT_EQ(rfk::getType<TestClass const>().getCArraySize(), 0u);
}

TEST(Rfk_Type_getCArraySize, NonConstLValueType)
{
	EXPECT_EQ(rfk::getType<TestClass&>().getCArraySize(), 0u);
}

TEST(Rfk_Type_getCArraySize, ConstLValueType)
{
	EXPECT_EQ(rfk::getType<TestClass const&>().getCArraySize(), 0u);
}

TEST(Rfk_Type_getCArraySize, RValueType)
{
	EXPECT_EQ(rfk::getType<TestClass&&>().getCArraySize(), 0u);
}

TEST(Rfk_Type_getCArraySize, NonConstTypePtr)
{
	EXPECT_EQ(rfk::getType<TestClass*>().getCArraySize(), 0u);
}

TEST(Rfk_Type_getCArraySize, ConstTypePtr)
{
	EXPECT_EQ(rfk::getType<TestClass const*>().getCArraySize(), 0u);
}

TEST(Rfk_Type_getCArraySize, TypeConstPtr)
{
	EXPECT_EQ(rfk::getType<TestClass* const>().getCArraySize(), 0u);
}

TEST(Rfk_Type_getCArraySize, ArrayType)
{
	EXPECT_EQ(rfk::getType<TestClass[5]>().getCArraySize(), 5u);
}

//=========================================================
//================== rfk::getArchetype ====================
//=========================================================

TEST(Rfk_Type_getArchetype, ValueType)
{
	EXPECT_EQ(rfk::getType<TestClass>().getArchetype(), rfk::getArchetype<TestClass>());
}

TEST(Rfk_Type_getArchetype, ConstValueType)
{
	EXPECT_EQ(rfk::getType<TestClass const>().getArchetype(), rfk::getArchetype<TestClass>());
}

TEST(Rfk_Type_getArchetype, NonConstLValueType)
{
	EXPECT_EQ(rfk::getType<TestClass&>().getArchetype(), rfk::getArchetype<TestClass>());
}

TEST(Rfk_Type_getArchetype, ConstLValueType)
{
	EXPECT_EQ(rfk::getType<TestClass const&>().getArchetype(), rfk::getArchetype<TestClass>());
}

TEST(Rfk_Type_getArchetype, RValueType)
{
	EXPECT_EQ(rfk::getType<TestClass&&>().getArchetype(), rfk::getArchetype<TestClass>());
}

TEST(Rfk_Type_getArchetype, NonConstTypePtr)
{
	EXPECT_EQ(rfk::getType<TestClass*>().getArchetype(), rfk::getArchetype<TestClass>());
}

TEST(Rfk_Type_getArchetype, ConstTypePtr)
{
	EXPECT_EQ(rfk::getType<TestClass const*>().getArchetype(), rfk::getArchetype<TestClass>());
}

TEST(Rfk_Type_getArchetype, TypeConstPtr)
{
	EXPECT_EQ(rfk::getType<TestClass* const>().getArchetype(), rfk::getArchetype<TestClass>());
}

TEST(Rfk_Type_getArchetype, ArrayType)
{
	EXPECT_EQ(rfk::getType<TestClass[5]>().getArchetype(), rfk::getArchetype<TestClass>());
}