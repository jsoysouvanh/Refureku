#pragma once

#include <Refureku/Object.h>

#include "Generated/MultipleTypeTemplateClassTemplate.rfkh.h"

template <typename T, typename U, typename V>
class RFKClass() MultipleTypeTemplateClassTemplate : public rfk::Object
{
	private:
		RFKField()
		T fieldT;

	protected:
		RFKField()
		T fieldU;

	public:
		RFKMethod()
		T returnT(T const& t) { return t; }

		RFKMethod()
		T returnT(T const& t1, T const& t2) { return t1 + t2; }

		RFKMethod()
		U returnU(U const& u) { return u; }

		RFKMethod()
		V returnV(V const& v) { return v; }
		
	MultipleTypeTemplateClassTemplate_T_U_V_GENERATED
};

File_MultipleTypeTemplateClassTemplate_GENERATED

template class RFKClass() MultipleTypeTemplateClassTemplate<int, int, int>;