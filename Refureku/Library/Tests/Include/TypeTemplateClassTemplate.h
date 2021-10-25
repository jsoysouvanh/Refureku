/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

//#include <vector>

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

namespace TESTNP NAMESPACE()
{
	template <typename T>
	class CLASS() ClassTemplateInNamespace
	{
		TESTNP_ClassTemplateInNamespace_T_GENERATED
	};
}

//class CLASS() TESTCLASS
//{
//	protected:
//		template <typename T>
//		class CLASS() ClassTemplateInCLASS
//		{
//			TESTCLASS_ClassTemplateInCLASS_T_GENERATED
//		};
//
//	TESTCLASS_GENERATED
//};

//template <typename T>
//class CLASS() Vector : public std::vector<T>
//{
//	friend rfk::internal::CodeGenerationHelpers;
//	friend implements_template1__rfk_registerChildClass<Vector<T>, void, void(rfk::Struct&)>;
//
//	private: template <typename ChildClass> static void _rfk_registerChildClass(rfk::Struct & childClass) noexcept
//	{
//		rfk::internal::CodeGenerationHelpers::registerChildClass<std::vector<T>, ChildClass>(childClass);
//		rfk::Struct const& thisClass = staticGetArchetype();
//		if constexpr (!std::is_same_v<ChildClass, Vector<T>>) const_cast<rfk::Struct&>(thisClass).addSubclass(childClass);
//	}
//
//
//	public: static rfk::ClassTemplateInstantiation const& staticGetArchetype() noexcept {
//		static bool initialized = false;
//		static rfk::ClassTemplateInstantiation type("Vector", std::hash<std::string>()(std::string("c:@ST>1#T@Vector") + rfk::internal::getTypename<Vector>()), sizeof(Vector), 1, *rfk::getArchetype<::Vector>());
//		if (!initialized)
//		{
//			initialized = true;
//			static rfk::TypeTemplateArgument arg0(rfk::getArchetype<T>());
//			type.addTemplateArgument(arg0);
//			type.setDirectParentsCapacity(1);
//			type.addDirectParent(rfk::getArchetype<std::vector>(), static_cast<rfk::EAccessSpecifier>(1));
//			Vector<T>::_rfk_registerChildClass<Vector<T>>(type);
//			static rfk::StaticMethod defaultSharedInstantiator("", 0u, rfk::getType<rfk::SharedPtr<Vector<T>>>(), new rfk::NonMemberFunction<rfk::SharedPtr<Vector<T>>()>(&rfk::internal::CodeGenerationHelpers::defaultSharedInstantiator<Vector<T>>), rfk::EMethodFlags::Default, nullptr);
//			type.addSharedInstantiator(defaultSharedInstantiator);
//		}
//		return type;
//	}
//
//	private: static inline rfk::ClassTemplateInstantiationRegisterer _rfk_registerer = staticGetArchetype(); rfk::internal::ForceGenerateSymbol<&_rfk_registerer> _rfk_forceRegister() = delete;
//
//	//Vector_T_GENERATED
//};

File_TypeTemplateClassTemplate_GENERATED

//template class CLASS() Vector<int>;
