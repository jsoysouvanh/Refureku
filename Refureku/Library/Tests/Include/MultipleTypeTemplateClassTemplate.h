#pragma once

#include <Refureku/Object.h>

#include "Generated/MultipleTypeTemplateClassTemplate.rfkh.h"

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

File_MultipleTypeTemplateClassTemplate_GENERATED

VARIABLE()
extern MultipleTypeTemplateClassTemplate<int, float, double> multipleTypeTemplateClassTemplateImplicitInstantiation;

template class CLASS() MultipleTypeTemplateClassTemplate<int, int, int>;