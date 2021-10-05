#include <iostream>

#include <Refureku/Refureku.h>

#include "AB.h"

#include "Generated/GeneratedCodeInCpp.rfks.h"

void GeneratedCodeInCpp::testMethod(A* aptr)
{
	rfk::ArchetypeAPI const* archetype = rfk::getArchetypeAPI<decltype(aptr)>();

	std::cout << archetype << std::endl;
}