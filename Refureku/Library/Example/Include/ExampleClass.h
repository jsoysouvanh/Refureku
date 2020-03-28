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
		RFKParentClass_GENERATED
	};

	class RFKClass() ExampleClass : public ParentClass
	{
		public:
			RFKField()
			static inline int	someStaticInt = 69;

			RFKField()
			int				someInt			= 42;

			RFKField()
			float			someFloat		= 42.42f;

			RFKMethod()
			int				method4(void* ptr);

			RFKMethod()
			void			method1();

		protected:
			RFKMethod()
			void			method2() const;

			RFKMethod()
			int				method3();

			RFKMethod()
			static	int		staticMethod3(char const* param);

			RFKMethod()
				static void	_hi() noexcept
			{};

			RFKMethod()
			static void aaa() noexcept {};

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