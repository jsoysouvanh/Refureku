#pragma once

#include <Refureku/Properties/ParseAllNested.h>
#include <Refureku/Object.h>

#include "ClassTemplates/TestClassAB.h"

#include "Generated/SingleTypeTemplateClassTemplate.rfkh.h"

template <typename T>
class RFKClass(ParseAllNested) SingleTypeTemplateClassTemplate : public rfk::Object
{
	RFKField()
	T testField;

	RFKMethod()
	T testMethod(T const& param) { return param; }

	SingleTypeTemplateClassTemplate_T_GENERATED
};

File_SingleTypeTemplateClassTemplate_GENERATED

template class RFKClass() SingleTypeTemplateClassTemplate<TestClassA>;