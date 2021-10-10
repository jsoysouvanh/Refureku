#include "Generated/ReworkTest.rfks.h"

int reworkVariable = 0;
int ReworkStruct::reworkStaticField = 0;

int rework_namespace::reworkNamespaceVariable = 0;

void rework_namespace::reworkNamespaceFunction(int, float) noexcept {}

void reworkFunction(int, float) noexcept {}

void ReworkClass::reworkMethod(int, float) {}

void ReworkClass::reworkMethod(int, float) const {}

float ReworkStruct::reworkStaticMethod() noexcept { return 0.0f; }