#include "ForwardDeclaredClass.h"

#include <stdexcept>	//std::logic_error

#include "Generated/TestMethods.rfks.h"

void TestMethodClass::noReturnNoParam()
{
}

int TestMethodClass::returnIntNoParam()
{
	return 0; 
}

int TestMethodClass::returnIntParamInt(int i)
{ 
	return i;
}

ForwardDeclaredClass* TestMethodClass::returnFwdClassParamFwdClass(ForwardDeclaredClass* param)
{
	return param;
}

NonReflectedClass& TestMethodClass::returnNonReflectedNoParam(NonReflectedClass& param)
{
	param.i = 42;

	return param;
}

void TestMethodClass::throwing()
{
	throw std::logic_error("Something wrong happened");
}

void TestMethodClass::constNoReturnNoParam() const
{

}