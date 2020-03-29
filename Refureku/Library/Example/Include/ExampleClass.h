#pragma once

#include "Generated/ExampleClass.rfk.h"

namespace exnamespace
{
	/** Non reflected class */
	class ParentParentParentClass
	{
		double pppDouble;

		public:
			ParentParentParentClass() noexcept {}
	};

	class RFKClass() OtherClass
	{
		RFKOtherClass_GENERATED
	};

	class RFKClass() ParentParentClass : public ParentParentParentClass
	{
		RFKField()
		float ppFloat = 123456.123456f;

		public:
			ParentParentClass() noexcept {}

		RFKParentParentClass_GENERATED
	};

	class RFKClass() ParentClass : public ParentParentClass
	{
		private:
			RFKMethod()
			void parentClassMethod1() noexcept { };

		public:
			RFKField()
			uint64_t pInt64 = 666;

			RFKMethod()
			virtual void method1() const { };

			ParentClass()					noexcept {}
			ParentClass(ParentClass const&)	= default;
			ParentClass(ParentClass&& o)	= default;

			//	GENERATED

			//template <typename ChildType>
			//static void __RFKregisterChild(rfk::Struct* childArchetype) noexcept
			//{
			//	rfk::Struct const& thisArchetype = staticGetArchetype();

			//	//TODO: Recursive call to parents classes later here

			//	//Add to list of children
			//	if (childArchetype != &thisArchetype)
			//	{
			//		//TODO
			//	}

			//	//Add fields
			//	childArchetype->fields.emplace_back("pInt64", 12635385505303968848u, static_cast<rfk::EAccessSpecifier>(1), childArchetype, &thisArchetype, offsetof(ChildType, pInt64), 0);
			//}

		RFKParentClass_GENERATED
	};
	
	std::ostream& operator<<(std::ostream& stream, ParentClass const& object) noexcept;

	class RFKClass() ParentClass2
	{
		RFKField()
		char p2Char = '*';

		RFKParentClass2_GENERATED
	};

	class RFKClass() ExampleClass : public ParentClass, public ParentClass2
	{
		public:
			RFKField()
			static inline int	someStaticInt = 69;

			RFKField()
			static inline ParentClass	someStaticParentClass;

			RFKField()
			mutable int		someInt			= 42;

			RFKField()
			ParentClass		someParentClass;

			RFKField()
			int*			somePtrToInt	= nullptr;

			RFKField()
			float			someFloat		= 42.42f;

			RFKMethod()
			int				method4(void* ptr);

			RFKMethod()
			virtual void	method1() const noexcept override;

		protected:
			RFKMethod()
			void			method2() const;

			RFKMethod()
			int				method3();

			RFKMethod()
			static	int		staticMethod3(char const* param);

		private:
			RFKMethod()
			static	int		staticMethod2();

			RFKMethod()
			static void		staticMethod1();

			RFKMethod()
			static	float	staticMethod3(int param)	noexcept;

			RFKMethod()
			float			method3(int i)				noexcept;

		public:
			ExampleClass()						noexcept {}
			ExampleClass(ExampleClass const&)	= default;
			ExampleClass(ExampleClass&&)		= default;
			~ExampleClass()						= default;

		//GENERATED

		//template <typename ParentType, typename ChildType>
		//static constexpr void __RFKrecurseRegisterChild(rfk::Struct* childArchetype)
		//{
		//	if constexpr (rfk::generated::implements_staticGetArchetype<ParentType, rfk::Class const&()>::value)
		//	{
		//		ParentType::template __RFKregisterChild<ChildType>(childArchetype);
		//	}
		//}

		//template <typename ChildType>
		//static void __RFKregisterChild(rfk::Struct* childArchetype) noexcept
		//{
		//	rfk::Struct const& thisArchetype = staticGetArchetype();

		//	__RFKrecurseRegisterChild<exnamespace::ParentClass, ChildType>(childArchetype);

		//	if (childArchetype != &thisArchetype)
		//	{
		//		const_cast<rfk::Struct&>(thisArchetype).children.insert(childArchetype);
		//	}
		//	
		//	childArchetype->fields.emplace_back("someFloat", 6118336768142618682u, static_cast<rfk::EAccessSpecifier>(1), childArchetype, &thisArchetype, offsetof(ChildType, someFloat), 0);
		//	childArchetype->fields.emplace_back("someInt", 9550625445138060657u, static_cast<rfk::EAccessSpecifier>(1), childArchetype, &thisArchetype, offsetof(ChildType, someInt), 1);
		//	childArchetype->fields.emplace_back("someParentClass", 9281646899607215384u, static_cast<rfk::EAccessSpecifier>(1), childArchetype, &thisArchetype, offsetof(ChildType, someParentClass), 0);
		//	childArchetype->fields.emplace_back("somePtrToInt", 12635385505303968848u, static_cast<rfk::EAccessSpecifier>(1), childArchetype, &thisArchetype, offsetof(ChildType, somePtrToInt), 0);
		//}

		//static rfk::Class const& staticGetArchetype() noexcept	
		//{	
		//	static bool				initialized = false;	
		//	static rfk::Class	type("ExampleClass", 6613751926088865067, static_cast<rfk::Archetype::ECategory>(0), sizeof(ExampleClass));	
		//	
		//	if (!initialized)	
		//	{
		//		initialized = true;

		//		__RFKExampleClass_GenerateParentsMetadata

		//		//Get total fields count
		//		size_t fieldsCount = 0; std::vector<rfk::Struct::Parent> currParents; std::vector<rfk::Struct::Parent> nextParents = type.directParents; while (!nextParents.empty()) { std::swap(currParents, nextParents); nextParents.clear(); for (rfk::Struct::Parent const& parent : currParents) { nextParents.insert(nextParents.end(), parent.type->directParents.begin(), parent.type->directParents.end()); fieldsCount += parent.type->fields.size(); } }

		//		size_t fieldsCount = /* MYFIELDSCOUNT */0; for (rfk::Struct::Parent const& parent : type.directParents) fieldsCount += parent.type->fields.size();

		//		type.fields.reserve(fieldsCount);

		//		//Call self register child
		//		__RFKregisterChild<ExampleClass>(&type);
		//	}	
		//		
		//	return type;	
		//}	
		//	
		//rfk::Class const& getArchetype() const noexcept	
		//{	
		//	return ExampleClass::staticGetArchetype();
		//}

		RFKExampleClass_GENERATED
	};
}