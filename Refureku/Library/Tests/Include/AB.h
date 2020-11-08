#pragma once

#include "CustomProperties.h"

#include "Generated/AB.rfk.h"

class RFKClass(CustomProperty2, CustomProperty(1, 2), CustomProperty2) A 
{
	RFKField(CustomProperty(1, 456)) 
	int field;

	RFKMethod(Tooltip("This is a test"))
	void testMethod() noexcept {}

	A_GENERATED
};

class RFKClass(CustomProperty(3, 4)) B : public A
{
	public:
		class RFKClass(CustomProperty(42, 42)) C
		{
			C_GENERATED
		};

	B_GENERATED
}; 

File_GENERATED