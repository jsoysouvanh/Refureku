#include <Refureku/Refureku.h>

#include "AB.h"

#include "GeneratedCodeInCpp.h"
File_GENERATED

void GeneratedCodeInCpp::testMethod(A* aptr)
{
	rfk::Archetype const* archetype = rfk::getArchetype<decltype(aptr)>();

	std::cout << archetype << std::endl;
}