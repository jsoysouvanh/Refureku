#pragma once

#include "ReflectedObject.h"

#include "Generated/ExampleClass.rfk.h"

namespace exnamespace
{
	/** Non reflected class */
	class ParentParentParentClass
	{
		double pppDouble = 0.21;

		public:
			ParentParentParentClass() noexcept {}
	};

	class RFKClass(rfk::ReflectedObject) OtherClass : public rfk::ReflectedObject
	{
		RFKOtherClass_GENERATED
	};

	class RFKClass(rfk::ReflectedObject) ParentParentClass : public ParentParentParentClass, public rfk::ReflectedObject
	{
		RFKField()
		float ppFloat = 123456.123456f;

		public:
			ParentParentClass() noexcept {}

		RFKParentParentClass_GENERATED
	};

	class RFKClass(rfk::ReflectedObject) ParentClass : public ParentParentClass
	{
		private:
			RFKMethod()
			void parentClassMethod1() noexcept { };

		public:
			RFKField()
			uint64_t pInt64 = 666;

			RFKMethod()
			virtual void method1() const { };

			ParentClass()					noexcept { }
			ParentClass(ParentClass const&)	= default;
			ParentClass(ParentClass&& o)	= default;

		RFKParentClass_GENERATED
	};
	
	std::ostream& operator<<(std::ostream& stream, ParentClass const& object) noexcept;

	class RFKClass() ParentClass2
	{
		RFKField()
		char p2Char = '*';

		public:
			ParentClass2() noexcept { }

		RFKParentClass2_GENERATED
	};

	class RFKClass(rfk::ReflectedObject) ExampleClass : public ParentClass, public ParentClass2
	{
		public:
			RFKField()
			static inline int	someStaticInt = 69;

			RFKField()
			static inline ParentClass	someStaticParentClass;

			RFKField()
			mutable int		someInt			= 42;

			RFKField()
			int				p2Char			= 2;

			RFKField()
			ParentClass		someParentClass;

			RFKField()
			int*			somePtrToInt	= nullptr;

			RFKField()
			float			someFloat		= 42.42f;

			RFKField()
			float const*	a;

			RFKField()
			float * const	b				= nullptr;

			RFKField()
			int const*		c[2][3];

			RFKMethod(CustomInstantiator)
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
			ExampleClass()						noexcept { }
			ExampleClass(ExampleClass const&)	= default;
			ExampleClass(ExampleClass&&)		= default;
			~ExampleClass()						= default;

		//GENERATED

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