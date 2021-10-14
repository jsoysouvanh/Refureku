#include "Generated/TestClass.rfks.h"

int TestClass::_intStaticField = 42;

int TestClass::getIntField() const noexcept
{
	return _intField;
}

int TestClass::getIntStaticField() noexcept
{
	return _intStaticField;
}