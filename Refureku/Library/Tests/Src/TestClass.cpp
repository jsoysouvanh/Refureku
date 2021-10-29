#include "Generated/TestClass.rfks.h"

int TestClass::_intStaticField = 42;
int TestClass::_intStaticField2 = 43;

int TestClass::getIntField() const noexcept
{
	return _intField;
}

int TestClass::getIntField() noexcept
{
	return _intField;
}

int TestClass::getIntStaticField() noexcept
{
	return _intStaticField;
}

int TestClass::getIntStaticField(int) noexcept
{
	return _intStaticField;
}