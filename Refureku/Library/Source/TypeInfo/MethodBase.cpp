#include "TypeInfo/MethodBase.h"

using namespace refureku;

MethodBase::MethodBase(ICallable* internalMethod) noexcept:
	_internalMethod{internalMethod}
{}

MethodBase::MethodBase(MethodBase&& other) noexcept:
	_internalMethod{other._internalMethod}
{
	other._internalMethod = nullptr;
}

MethodBase::~MethodBase() noexcept
{
	if (_internalMethod != nullptr)
		delete _internalMethod;
}