/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <Refureku/Object.h>
#include <Refureku/Properties/ParseAllNested.h>

#include "Generated/TypeTemplateClassTemplate.rfkh.h"

template <typename T>
class CLASS(kodgen::ParseAllNested) SingleTypeTemplateClassTemplate : public rfk::Object
{
	T testField = T();

	T testMethod(T const& param) { return param; }

	SingleTypeTemplateClassTemplate_T_GENERATED
};

template <typename T, typename U, typename V>
class CLASS() MultipleTypeTemplateClassTemplate : public rfk::Object
{
	private:
		FIELD()
		T fieldT = T();

	protected:
		FIELD()
		U fieldU = U();

	public:
		METHOD()
		T returnT(T const& t) { return t; }

		METHOD()
		T returnT(T const& t1, T const& t2) { return t1 + t2; }

		METHOD()
		U returnU(U const& u) { return u; }

		METHOD()
		V returnV(V const& v) { return v; }

	MultipleTypeTemplateClassTemplate_T_U_V_GENERATED
};

File_TypeTemplateClassTemplate_GENERATED

template class CLASS() SingleTypeTemplateClassTemplate<int>;
template class CLASS() MultipleTypeTemplateClassTemplate<int, float, double>;