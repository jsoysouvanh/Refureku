#include <iostream>
#include <cassert>

#include "Misc/Filesystem.h"
#include "Properties/PropertyRules.h"

int main()
{
	kodgen::PropertyRules propertyRules;

	// Simple properties
	assert(propertyRules.addSimplePropertyRule("KodgenProp"));
	assert(!propertyRules.addSimplePropertyRule("KodgenProp"));
	assert(propertyRules.removeSimplePropertyRule("KodgenProp"));
	assert(propertyRules.addSimplePropertyRule("KodgenProp"));
	assert(propertyRules.addSimplePropertyRule("KodgenProp2"));

	assert(propertyRules.getSimplePropertyRule("KodgenProp") != nullptr);
	assert(propertyRules.getSimplePropertyRule("KodgenProp2") != nullptr);
	assert(propertyRules.getSimplePropertyRule("KodgenProp3") == nullptr);

	// Complex properties
	assert(propertyRules.addComplexPropertyRule("KodgenProp", "Test(This|OrThis)"));
	assert(!propertyRules.addComplexPropertyRule("KodgenProp", "Test(This|OrThis)"));
	assert(propertyRules.removeComplexPropertyRule("KodgenProp", "Test(This|OrThis)"));
	assert(propertyRules.addComplexPropertyRule("KodgenProp", "Test(This|OrThis)"));
	assert(propertyRules.addComplexPropertyRule("KodgenProp2", "Test(This|OrThis)"));

	assert(propertyRules.getComplexPropertyRule("KodgenProp") != nullptr);
	assert(propertyRules.getComplexPropertyRule("KodgenProp2") != nullptr);
	assert(propertyRules.getComplexPropertyRule("KodgenProp3") == nullptr);

	return EXIT_SUCCESS;
}