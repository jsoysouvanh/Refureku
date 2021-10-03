#include "Refureku/Generated/PropertySettings.rfks.h"

//first [[maybe_unused]] is written after the variable name for pre-gcc 9.3 compatibility
PropertySettings::PropertySettings(rfk::EEntityKind targetEntityKind_ [[maybe_unused]], [[maybe_unused]] bool allowMultiple_, [[maybe_unused]] bool shouldInherit_) noexcept
{
}

PropertySettings::~PropertySettings() noexcept
{
	//Must define default destructor for correct vtable export on GCC/Clang
}