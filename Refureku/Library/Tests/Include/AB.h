#pragma once

#include "CustomProperties.h"
#include "Test.h"

#include "Generated/AB.rfkh.h"

class RFKClass(CustomProperty2   , CustomProperty(1, 2) ,CustomProperty2) A
{
	RFKField(CustomProperty(1, 456)) 
	int field = 0;

	RFKField(Slider(0.0f, 10.0f))
	float sliderFloat = 5.0f; 

	RFKMethod()
	virtual void testMethod(int i) noexcept { static_cast<void>(i); }

	RFKMethod(Tooltip("This is a test"))
	virtual void testMethod() noexcept {}

	A_GENERATED
}; 

class RFKClass(CustomProperty(3 , 4)) B : public A
{
	B_GENERATED
};

class RFKClass() C : public A 
{
	enum class RFKEnum() PrivateNestedEnum
	{
		Value1,
		Value2
	};

	class RFKClass() PrivateNestedClass
	{
		enum class RFKEnum() PrivateNestedEnum
		{
			Value1,
			Value2
		};

		C_PrivateNestedClass_GENERATED
	};

	RFKField()
	int i = 0;

	RFKMethod()
	virtual void testMethod() noexcept override {}

	public:
		enum class RFKEnum() PublicNestedEnum
		{
			Value1,
			Value2
		};

	C_GENERATED
};

class RFKClass() E
{
	public:
		RFKField()
		static inline float const staticConstFloat = 3.14f;

		RFKField()
		float const constFloat = 3.14f;

	E_GENERATED
};

RFKVariable()
inline int const constGlobalInt = 2;

File_AB_GENERATED