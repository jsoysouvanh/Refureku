#include "ForwardDeclaredClass.h"

#include <stdexcept>	//std::logic_error

#include "Generated/TestStaticMethods.rfks.h"

void TestStaticMethodClass::noReturnNoParam()
{
}

int TestStaticMethodClass::returnIntNoParam()
{
	return 0; 
}

int TestStaticMethodClass::returnIntParamInt(int i)
{ 
	return i;
}

ForwardDeclaredClass* TestStaticMethodClass::returnFwdClassParamFwdClass(ForwardDeclaredClass* param)
{
	return param;
}

NonReflectedClass& TestStaticMethodClass::returnNonReflectedNoParam(NonReflectedClass& param)
{
	param.i = 42;

	return param;
}

void TestStaticMethodClass::throwing()
{
	throw std::logic_error("Something wrong happened");
}