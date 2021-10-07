#include <iostream>

#include <Refureku/Refureku.h>

#include "AB.h"

#include "Generated/GeneratedCodeInCpp.rfks.h"

void GeneratedCodeInCpp::testMethod(A* aptr)
{
	rfk::Archetype const* archetype = rfk::getArchetype<decltype(aptr)>();

	std::cout << archetype << std::endl;
}