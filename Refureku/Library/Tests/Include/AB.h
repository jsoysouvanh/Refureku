#pragma once

#include "CustomProperties.h"
#include "Test.h"

#include "Generated/AB.rfk.h"

class RFKClass(CustomProperty2, CustomProperty(1, 2), CustomProperty2) A 
{
	RFKField(CustomProperty(1, 456)) 
	int field = 0;

	RFKField(Slider(0.0f, 10.0f))
	float sliderFloat = 5.0f; 

	RFKMethod()
	virtual void testMethod(int i) noexcept {}

	RFKMethod(Tooltip("This is a test"))
	virtual void testMethod() noexcept {} 

	A_GENERATED
}; 

class RFKClass(CustomProperty(3, 4)) B : public A
{
	B_GENERATED
};

class RFKClass() C : public A
{
	RFKMethod()
	virtual void testMethod() noexcept override {}

	C_GENERATED
};

File_GENERATED