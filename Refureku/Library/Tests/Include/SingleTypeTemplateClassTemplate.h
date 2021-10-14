#pragma once

#include <Refureku/Properties/ParseAllNested.h>
#include <Refureku/Object.h>

#include "Generated/SingleTypeTemplateClassTemplate.rfkh.h"

template <typename T>
class CLASS(ParseAllNested) SingleTypeTemplateClassTemplate : public rfk::Object
{
	FIELD()
	T testField;

	METHOD()
	T testMethod(T const& param) { return param; }

	SingleTypeTemplateClassTemplate_T_GENERATED
};

File_SingleTypeTemplateClassTemplate_GENERATED

template class CLASS() SingleTypeTemplateClassTemplate<int>;