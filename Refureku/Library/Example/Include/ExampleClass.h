#pragma once

#include "Generated/ExampleClass.refureku.h"

namespace exnamespace
{
	class RFKClass() ParentParentParentClass
	{
		RFKParentParentParentClass_GENERATED
	};

	class RFKClass() ParentParentClass : private ParentParentParentClass
	{
		RFKParentParentClass_GENERATED
	};

	class RFKClass() ParentClass : protected ParentParentClass
	{
		private:
			RFKMethod()
			void parentClassMethod1() noexcept { };

		public:
			uint64_t someUint = 666;

			RFKMethod()
			virtual void method1() const { };

			ParentClass()					= default;
			ParentClass(ParentClass const&)	= default;
			ParentClass(ParentClass&& o)	= default;

		RFKParentClass_GENERATED
	};
	
	std::ostream& operator<<(std::ostream& stream, ParentClass const& object) noexcept;

	class RFKClass() ExampleClass : public ParentClass
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
			ExampleClass()						= default;
			ExampleClass(ExampleClass const&)	= default;
			ExampleClass(ExampleClass&&)		= default;
			~ExampleClass()						= default;

		//GENERATED

		//static refureku::Class const& staticGetType() noexcept	
		//{	
		//	static bool				initialized = false;	
		//	static refureku::Class	type("ExampleClass", 6613751926088865067, static_cast<refureku::Archetype::ECategory>(0), sizeof(ExampleClass));	
		//	
		//	if (!initialized)	
		//	{
		//		//type.fields.emplace_back("aField", 42u, offsetof(ExampleClass, someInt), refureku::EAccessSpecifier::Private);

		//		initialized = true;
		//	}	
		//		
		//	return type;	
		//}	
		//	
		//refureku::Class const& getType() const noexcept	
		//{	
		//	return ExampleClass::staticGetType();
		//}

		RFKExampleClass_GENERATED
	};
}