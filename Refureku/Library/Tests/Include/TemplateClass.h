#pragma once

#include <vector>
#include <iostream>

#include "Generated/TemplateClass.rfkh.h"

class RFKClass() TestClassA
{
	public:
		using Type = float;

	TestClassA_GENERATED
};

class RFKClass() TestClassB
{
	public:
		using Type = int;

	TestClassB_GENERATED
};

namespace TEST
{
	template <typename T, template <typename A, typename B> typename U, int V>
	class RFKClass() Vector : public std::vector<T>
	{
		RFKField()
			int i;

		public:
			RFKField()
				typename T::Type t;

			RFKMethod()
			static void testStaticMethod(T const& t) {}

		//GENERATED CODE
		friend rfk::Struct;
		friend rfk::CodeGenerationHelpers;
		friend implements_template1__rfk_registerChildClass<Vector<T, U, V>, void, void(rfk::Struct&)>; 
		
		public: static rfk::Class const& staticGetArchetype() noexcept
		{
			static bool initialized = false;

			//TODO: Change Name without template types
			//TODO: Change combine hash of all archetypes
			static rfk::Class type("Vector<T, U, V>", 9918884327437644209u, sizeof(Vector<T, U, V>), true);

			if (!initialized)
			{
				initialized = true;

				std::cout << "INITIALIZE Vector: " << rfk::getArchetype<T>()->name << std::endl;

				type.setDefaultInstantiator(&rfk::defaultInstantiator<Vector<T, U, V>>);
				type.directParents.reserve(1);
				type.addToParents<std::vector<T>>(static_cast<rfk::EAccessSpecifier>(1));
				Vector<T, U, V>::_rfk_registerChildClass<Vector<T, U, V>>(type);
				[[maybe_unused]] rfk::Method* method = nullptr; [[maybe_unused]] rfk::StaticMethod* staticMethod = nullptr;
				staticMethod = type.addStaticMethod("testStaticMethod", 5430318730629265774u, rfk::Type::getType<void>(), std::make_unique<rfk::NonMemberFunction<void (const T &)>>(static_cast<void (*)(const T &)>(& Vector<T, U, V>::testStaticMethod)), static_cast<rfk::EMethodFlags>(25));
				staticMethod->parameters.reserve(1); staticMethod->addParameter("t", rfk::Type::getType<const T &>());
			}

			return type;
		}
		
		_RFK_UNPACK_IF_NOT_PARSING(private: static inline rfk::ArchetypeRegisterer _rfk_archetypeRegisterer = &staticGetArchetype();)
		
		private: template <typename ChildClass> static void _rfk_registerChildClass(rfk::Struct& childClass) noexcept
		{
			rfk::CodeGenerationHelpers::registerChildClass<std::vector<T>, ChildClass>(childClass);
			rfk::Struct const& thisClass = staticGetArchetype();

			if constexpr (!std::is_same_v<ChildClass, Vector<T, U, V>>) const_cast<rfk::Struct&>(thisClass).subclasses.insert(&childClass);

			[[maybe_unused]] rfk::Field* field = nullptr;
			[[maybe_unused]] rfk::StaticField* staticField = nullptr;

			__RFK_DISABLE_WARNING_PUSH
			__RFK_DISABLE_WARNING_OFFSETOF

			field = childClass.addField("i", 2732867638607707709u, rfk::Type::getType<int>(), static_cast<rfk::EFieldFlags>(4), &thisClass, offsetof(ChildClass, i));
			field = childClass.addField("t", 2732870937142592342u, rfk::Type::getType<typename T::Type>(), static_cast<rfk::EFieldFlags>(1), &thisClass, offsetof(ChildClass, t));

			__RFK_DISABLE_WARNING_POP
		}
			
		//Vector_T_U_V_GENERATED
	};
}

#include "Refureku/TypeInfo/Archetypes/ClassTemplateInstance.h"
#include "Refureku/TypeInfo/Properties/ParseAllNested.h"
#include "Refureku/TypeInfo/Archetypes/ClassTemplate.h"

template <typename T>
class RFKClass(ParseAllNested) TestSimpleClassTemplate
{
	RFKField()
	T testField;

	RFKMethod()
	T testMethod(T const& param) { return param; }

	friend rfk::Struct;
	friend rfk::CodeGenerationHelpers;
	friend implements_template1__rfk_registerChildClass<TestSimpleClassTemplate<T>, void, void(rfk::Struct&)>;

	public:
	static rfk::Class const& /*TestSimpleClassTemplate<T>::*/staticGetArchetype() noexcept
	{
		static bool initialized = false;
		static rfk::ClassTemplateInstance type("TestSimpleClassTemplate", 123456, sizeof(TestSimpleClassTemplate), true, *rfk::getArchetype<::TestSimpleClassTemplate>());
		//std::string("Path @ To @ TestSimpleClassTemplate @ T").replace()

		if (!initialized)
		{
			initialized = true;

			std::cout << "INSTANTIATION TestSimpleClassTemplate: " << rfk::getArchetype<T>()->name << std::endl;

			//Add template arguments for this instance
			type.templateArguments.emplace_back(type.instantiatedFrom.templateParameters[0], rfk::getArchetype<T>());

			type.setDefaultInstantiator(&rfk::defaultInstantiator<TestSimpleClassTemplate<T>>);

			TestSimpleClassTemplate<T>::_rfk_registerChildClass<TestSimpleClassTemplate<T>>(type);

			[[maybe_unused]] rfk::Method* method = nullptr; [[maybe_unused]] rfk::StaticMethod* staticMethod = nullptr;
			method = type.addMethod("testMethod", 5430318730629265774u, rfk::Type::getType<T>(), std::make_unique<rfk::MemberFunction<TestSimpleClassTemplate<T>, T (const T &)>>(static_cast<T (TestSimpleClassTemplate<T>::*)(const T &)>(& TestSimpleClassTemplate<T>::testMethod)), static_cast<rfk::EMethodFlags>(17));
			method->parameters.reserve(1); method->addParameter("param", rfk::Type::getType<const T &>());
		}

		return type;
	}

	static inline int r = []() -> int { staticGetArchetype(); return 0; }();

	//_RFK_UNPACK_IF_NOT_PARSING(private: static inline rfk::ArchetypeRegisterer _rfk_archetypeRegisterer = &staticGetArchetype();) //TODO: This should register by ID only, since it is already registered to the ClassTemplate

	private: template <typename ChildClass> static void _rfk_registerChildClass(rfk::Struct& childClass) noexcept
	{
		//rfk::CodeGenerationHelpers::registerChildClass<std::vector<T>, ChildClass>(childClass);
		rfk::Struct const& thisClass = staticGetArchetype();

		if constexpr (!std::is_same_v<ChildClass, TestSimpleClassTemplate<T>>) const_cast<rfk::Struct&>(thisClass).subclasses.insert(&childClass);

		[[maybe_unused]] rfk::Field* field = nullptr;
		[[maybe_unused]] rfk::StaticField* staticField = nullptr;

		__RFK_DISABLE_WARNING_PUSH
		__RFK_DISABLE_WARNING_OFFSETOF

		field = childClass.addField("testField", 2732867638607707709u, rfk::Type::getType<T>(), static_cast<rfk::EFieldFlags>(4), &thisClass, offsetof(ChildClass, testField));

		__RFK_DISABLE_WARNING_POP
	}

	//TestSimpleClassTemplate_T_GENERATED
};

class RFKClass() TestTemplateClass
{
	public:
		RFKField()
		TEST::Vector<TestClassA, std::vector, 0>	vectorF;

		RFKField()
		TEST::Vector<TestClassB, std::vector, 3>	vectorI;

	TestTemplateClass_GENERATED
};

///// GENERATE A METHOD TO DEFINE THE CLASS TEMPLATE
namespace rfk
{
	template <>
	rfk::Archetype const* getArchetype<TestSimpleClassTemplate>() noexcept;
}
/////////////////////////////////////////////////

File_TemplateClass_GENERATED

namespace rfk
{
	//template <> rfk::Archetype const* getArchetype<TEST::Vector<A, std::vector, 2>>() noexcept { return nullptr; }
	//template <> rfk::Archetype const* getArchetype<Vector<A, std::vector, 2>>() noexcept;
}

template class RFKClass() TEST::Vector<TestClassA, std::vector, 0>;
template class RFKClass() TestSimpleClassTemplate<TestClassA>;
