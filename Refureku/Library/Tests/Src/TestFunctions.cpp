#include "Generated/TestFunctions.rfks.h"

TestClass& func_return_noParam()
{
	static TestClass testClass;

	return testClass;
}

void func_noParam()
{
}

int func_return_singleParam(int i)
{
	return i;
}

int func_return_MultipleParams(int i, int j)
{
	return i + j;
}

void func_singleParam(int i)
{
	(void)i;
}

void func_MultipleParams(int i, int j)
{
	(void)i;
	(void)j;
}

int func_overloaded()
{
	return 0;
}

int func_overloaded(int i)
{
	return 1;
}