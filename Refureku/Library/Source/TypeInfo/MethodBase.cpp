#include "TypeInfo/MethodBase.h"

using namespace refureku;

MethodBase::MethodBase(std::string&& methodName, uint64 methodId, EAccessSpecifier accessSpecifier, ICallable* internalMethod) noexcept:
	_id{std::forward<uint64>(methodId)},
	_internalMethod{internalMethod},
	name{std::forward<std::string>(methodName)},
	access{std::forward<EAccessSpecifier>(accessSpecifier)}
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