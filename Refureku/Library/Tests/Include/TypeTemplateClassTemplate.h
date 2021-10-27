/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
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

	SingleTypeTemplateClassTemplate_GENERATED
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

	MultipleTypeTemplateClassTemplate_GENERATED
};

namespace template_namespace NAMESPACE()
{
	template <typename T>
	class CLASS() ClassTemplateInNamespace
	{
		template_namespace_ClassTemplateInNamespace_GENERATED
	};
}

class CLASS() ClassWithNestedClassTemplate
{
	private:
		/*template <typename T>
		class CLASS() PrivateClassTemplateInClass
		{
			ClassWithNestedClassTemplate_PrivateClassTemplateInClass_GENERATED
		};*/

	protected:
		/*template <typename T>
		class CLASS() ProtectedClassTemplateInClass
		{
			ClassWithNestedClassTemplate_ProtectedClassTemplateInClass_GENERATED
		};*/
		
	public:
		template <typename T>
		class CLASS() PublicClassTemplateInClass
		{
			ClassWithNestedClassTemplate_PublicClassTemplateInClass_GENERATED
		};

	ClassWithNestedClassTemplate_GENERATED
};

File_TypeTemplateClassTemplate_GENERATED