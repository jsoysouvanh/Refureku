#include "Refureku/Object.h"

#include <Refureku/TypeInfo/Archetypes/Struct.h>

using namespace rfk;

Struct const& Object::getArchetype() const noexcept
{
    static rfk::Class type("NULL", 0u, sizeof(int), true);
    return type;
}
