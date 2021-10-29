#include <Refureku/Config.h>

//All this is NOT supported on MSVC compiler
#if RFK_TEMPLATE_TEMPLATE_SUPPORT

#include "Generated/TemplateTemplateClassTemplate.rfks.h"

template class SingleTemplateTemplateClassTemplate<SingleTypeTemplateClassTemplate>;
template class MultipleTemplateTemplateClassTemplate<MultipleTypeTemplateClassTemplate, SingleTypeTemplateClassTemplate>;

#endif