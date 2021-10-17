#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "ConstructionTrackedClass.h"

//=========================================================
//==================== Vector::ctor =======================
//=========================================================

TEST(Rfk_Vector_ctor, InitialCapacityCtor)
{
	EXPECT_EQ(rfk::Vector<int>().capacity(), 0u);
	EXPECT_EQ(rfk::Vector<int>(1).capacity(), 1u);
	EXPECT_EQ(rfk::Vector<int>(2).capacity(), 2u);
}

TEST(Rfk_Vector_ctor, CopyCtor)
{
	rfk::Vector<ConstructionTrackedClass> vec1(4);

	for (int i = 0; i < 4; i++)
	{
		vec1.emplace_back(i);
	}

	EXPECT_EQ(vec1.size(), 4u);

	rfk::Vector<ConstructionTrackedClass> vecCopy = vec1;

	EXPECT_EQ(vec1.size(), vecCopy.size());
	for (std::size_t i = 0u; i < vecCopy.size(); i++)
	{
		EXPECT_EQ(vec1[i].getValue(), vecCopy[i].getValue());
	}
}

TEST(Rfk_Vector_ctor, MoveCtor)
{
	rfk::Vector<ConstructionTrackedClass> vec1(4);

	for (int i = 0; i < 4; i++)
	{
		vec1.emplace_back(i);
	}

	EXPECT_EQ(vec1.size(), 4u);

	rfk::Vector<ConstructionTrackedClass> vecMove = std::move(vec1);

	EXPECT_TRUE(vec1.empty());
	EXPECT_EQ(vecMove.size(), 4u);

	for (std::size_t i = 0u; i < vecMove.size(); i++)
	{
		EXPECT_EQ(vecMove[i].getValue(), i);
	}
}

TEST(Rfk_Vector_ctor, MoveDifferentElementTypeCtor)
{
	rfk::Vector<rfk::Function const*> vec1;

	vec1.push_back(rfk::getDatabase().getFunctionByName("func_return_noParam"));
	vec1.push_back(rfk::getDatabase().getFunctionByName("func_static_noParam"));
	vec1.push_back(rfk::getDatabase().getFunctionByName("func_noParam"));

	rfk::Vector<rfk::Entity const*> vec2 = std::move(vec1);

	EXPECT_TRUE(vec1.empty());
	EXPECT_EQ(vec2.size(), 3u);
	EXPECT_TRUE(vec2[0]->hasSameName("func_return_noParam"));
	EXPECT_TRUE(vec2[1]->hasSameName("func_static_noParam"));
	EXPECT_TRUE(vec2[2]->hasSameName("func_noParam"));
}

//=========================================================
//============== Vector::push_back (copy) =================
//=========================================================

TEST(Rfk_Vector_push_back, PushBackElementByCopy)
{
	rfk::Vector<ConstructionTrackedClass> vec;

	ConstructionTrackedClass ctc;

	vec.push_back(ctc);
	
	EXPECT_EQ(vec.capacity(), 1u);
	EXPECT_EQ(vec.size(), 1u);
	EXPECT_TRUE(vec[0].getCopyConstructed());
}

TEST(Rfk_Vector_push_back, PushBackElementByMove)
{
	rfk::Vector<ConstructionTrackedClass> vec;

	vec.push_back(ConstructionTrackedClass());

	EXPECT_EQ(vec.capacity(), 1u);
	EXPECT_EQ(vec.size(), 1u);
	EXPECT_TRUE(vec[0].getMoveConstructed());
}

TEST(Rfk_Vector_push_back, PushBackVectorByCopy)
{
	rfk::Vector<ConstructionTrackedClass> vec1;

	vec1.push_back(ConstructionTrackedClass());
	vec1.push_back(ConstructionTrackedClass());

	rfk::Vector<ConstructionTrackedClass> vec2(10);

	vec2.push_back(ConstructionTrackedClass());
	vec2.push_back(vec1);

	EXPECT_EQ(vec2.size(), 3u);
	EXPECT_TRUE(vec2[0].getMoveConstructed());
	EXPECT_TRUE(vec2[1].getCopyConstructed());
	EXPECT_TRUE(vec2[2].getCopyConstructed());
}

TEST(Rfk_Vector_push_back, PushBackVectorByMove)
{
	rfk::Vector<ConstructionTrackedClass> vec1(10);
	ConstructionTrackedClass ctc;

	vec1.push_back(ctc);
	vec1.push_back(ctc);

	EXPECT_TRUE(vec1[0].getCopyConstructed());
	EXPECT_TRUE(vec1[1].getCopyConstructed());

	rfk::Vector<ConstructionTrackedClass> vec2(10);

	vec2.push_back(ConstructionTrackedClass());
	vec2.push_back(std::move(vec1));

	EXPECT_EQ(vec2.size(), 3u);
	EXPECT_TRUE(vec2[0].getMoveConstructed());
	EXPECT_TRUE(vec2[1].getMoveConstructed());
	EXPECT_TRUE(vec2[2].getMoveConstructed());
}

//=========================================================
//================ Vector::emplace_back ===================
//=========================================================

TEST(Rfk_Vector_emplace_back, emplace_back)
{
	rfk::Vector<ConstructionTrackedClass> vec;

	vec.emplace_back(1);
	vec.emplace_back(2);
	vec.emplace_back(3);

	EXPECT_EQ(vec.size(), 3u);
	EXPECT_EQ(vec[0].getValue(), 1);
	EXPECT_EQ(vec[1].getValue(), 2);
	EXPECT_EQ(vec[2].getValue(), 3);
}

//=========================================================
//==================== Vector::front ======================
//=========================================================

TEST(Rfk_Vector_front, frontConst)
{
	rfk::Vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	rfk::Vector<int> const& constRef = vec;

	EXPECT_EQ(constRef.front(), 1);
	EXPECT_EQ(constRef.front(), vec[0]);
}

TEST(Rfk_Vector_front, frontNonConst)
{
	rfk::Vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	EXPECT_EQ(vec.front(), 1);
	EXPECT_EQ(vec.front(), vec[0]);
}

//=========================================================
//===================== Vector::back ======================
//=========================================================

TEST(Rfk_Vector_back, backConst)
{
	rfk::Vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	rfk::Vector<int> const& constRef = vec;

	EXPECT_EQ(constRef.back(), 3);
	EXPECT_EQ(constRef.back(), vec[2]);
}

TEST(Rfk_Vector_back, backNonConst)
{
	rfk::Vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	EXPECT_EQ(vec.back(), 3);
	EXPECT_EQ(vec.back(), vec[2]);
}

//=========================================================
//===================== Vector::data ======================
//=========================================================

TEST(Rfk_Vector_data, dataConst)
{
	rfk::Vector<int> vec;
	rfk::Vector<int> const& constRef = vec;

	EXPECT_EQ(constRef.data(), nullptr);

	vec.push_back(1);

	EXPECT_EQ(constRef.data(), &vec[0]);
}

TEST(Rfk_Vector_data, dataNonConst)
{
	rfk::Vector<int> vec;

	EXPECT_EQ(vec.data(), nullptr);

	vec.push_back(1);

	EXPECT_EQ(vec.data(), &vec[0]);
}

//=========================================================
//==================== Vector::reserve ====================
//=========================================================

TEST(Rfk_Vector_reserve, reserve)
{
	rfk::Vector<int> vec;

	EXPECT_EQ(vec.capacity(), 0u);

	vec.reserve(4);

	EXPECT_EQ(vec.capacity(), 4u);

	vec.push_back(1);
	vec.push_back(1);
	vec.push_back(1);
	vec.push_back(1);

	EXPECT_EQ(vec.capacity(), 4u);
}

//=========================================================
//==================== Vector::resize =====================
//=========================================================

TEST(Rfk_Vector_resize, GrowResize)
{
	rfk::Vector<int> vec;

	EXPECT_EQ(vec.size(), 0u);

	vec.resize(10u);

	EXPECT_EQ(vec.size(), 10u);

	for (int i = 0; i < 10; i++)
	{
		EXPECT_EQ(vec[i], 0);
	}
}

TEST(Rfk_Vector_resize, ShrinkResize)
{
	rfk::Vector<int> vec(10);

	for (int i = 0; i < 10; i++)
	{
		vec.push_back(i);
	}

	EXPECT_EQ(vec.size(), 10u);

	vec.resize(5u);

	EXPECT_EQ(vec.size(), 5u);
}

TEST(Rfk_Vector_resize, SameSize)
{
	rfk::Vector<int> vec(10);

	EXPECT_EQ(vec.size(), 0u);
	
	vec.push_back(1);
	vec.push_back(2);

	EXPECT_EQ(vec.size(), 2u);
	
	vec.resize(2u);

	EXPECT_EQ(vec.size(), 2u);
	EXPECT_EQ(vec[0], 1);
	EXPECT_EQ(vec[1], 2);
}

//=========================================================
//==================== Vector::empty ======================
//=========================================================

TEST(Rfk_Vector_empty, empty)
{
	rfk::Vector<int> vec;

	EXPECT_TRUE(vec.empty());

	vec.reserve(10u);

	EXPECT_TRUE(vec.empty());

	vec.push_back(1);

	EXPECT_FALSE(vec.empty());
}

//=========================================================
//==================== Vector::clear ======================
//=========================================================

TEST(Rfk_Vector_clear, clear)
{
	rfk::Vector<int> vec;

	EXPECT_TRUE(vec.empty());

	vec.push_back(1);

	EXPECT_FALSE(vec.empty());

	vec.clear();

	EXPECT_TRUE(vec.empty());
}

//=========================================================
//=================== Vector::forloop =====================
//=========================================================

TEST(Rfk_Vector_forloop, NonConstIteratorBasedLoop)
{
	rfk::Vector<int> vec;

	for (int i = 0; i < 10; i++)
	{
		vec.push_back(1);
	}

	int sum = 0;

	for (auto it = vec.begin(); it != vec.end(); it++)
	{
		sum += *it;
	}

	EXPECT_EQ(sum, 10);
}

TEST(Rfk_Vector_forloop, ConstIteratorBasedLoop)
{
	rfk::Vector<int> vec;
	auto const& constVec = vec;

	for (int i = 0; i < 10; i++)
	{
		vec.push_back(1);
	}

	int sum = 0;
	int sum2 = 0;

	//Use const overload for begin/end
	for (auto it = constVec.begin(); it != constVec.end(); it++)
	{
		sum += *it;
	}

	for (auto it = constVec.cbegin(); it != constVec.cend(); it++)
	{
		sum2 += *it;
	}

	EXPECT_EQ(sum, 10);
	EXPECT_EQ(sum, sum2);
}

TEST(Rfk_Vector_forloop, RangeBasedLoop)
{
	rfk::Vector<int> vec;

	for (int i = 0; i < 10; i++)
	{
		vec.push_back(1);
	}

	int sum = 0;

	for (int i : vec)
	{
		sum += i;
	}

	EXPECT_EQ(sum, 10);
}

//=========================================================
//================== Vector::operator[] ===================
//=========================================================

TEST(Rfk_Vector_accessOperator, NonConstAccess)
{
	rfk::Vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);

	EXPECT_EQ(vec[0], 1);
	EXPECT_EQ(vec[1], 2);
}

TEST(Rfk_Vector_accessOperator, ConstAccess)
{
	rfk::Vector<int> vec;

	vec.push_back(1);
	vec.push_back(2);

	auto const& constVec = vec;

	EXPECT_EQ(constVec[0], 1);
	EXPECT_EQ(constVec[1], 2);
}

//=========================================================
//================== Vector::operator= ====================
//=========================================================

TEST(Rfk_Vector_assignmentOperator, CopyAssignment)
{
	rfk::Vector<ConstructionTrackedClass> vec1(2);
	rfk::Vector<ConstructionTrackedClass> vec2(2);

	vec1.emplace_back(1);
	vec2.emplace_back(2);

	EXPECT_EQ(vec1.size(), 1u);
	EXPECT_TRUE(vec1.front().getDefaultConstructed());
	EXPECT_EQ(vec2.size(), 1u);
	EXPECT_TRUE(vec2.front().getDefaultConstructed());

	vec2 = vec1;

	EXPECT_EQ(vec1.size(), 1u);
	EXPECT_TRUE(vec1.front().getDefaultConstructed());

	EXPECT_EQ(vec2.size(), 1u);
	EXPECT_TRUE(vec2.front().getCopyConstructed());
	EXPECT_EQ(vec2.front().getValue(), 1);
}

TEST(Rfk_Vector_assignmentOperator, MoveAssignment)
{
	rfk::Vector<ConstructionTrackedClass> vec1(2);
	rfk::Vector<ConstructionTrackedClass> vec2(2);

	vec1.emplace_back(1);
	vec2.emplace_back(2);

	EXPECT_EQ(vec1.size(), 1u);
	EXPECT_TRUE(vec1.front().getDefaultConstructed());
	EXPECT_EQ(vec2.size(), 1u);
	EXPECT_TRUE(vec2.front().getDefaultConstructed());

	vec2 = std::move(vec1);

	EXPECT_TRUE(vec1.empty());
	EXPECT_EQ(vec1.data(), nullptr);

	EXPECT_EQ(vec2.size(), 1u);
	EXPECT_TRUE(vec2.front().getDefaultConstructed());
	EXPECT_EQ(vec2.front().getValue(), 1);
}