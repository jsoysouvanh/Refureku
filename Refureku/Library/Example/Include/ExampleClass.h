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
			int		someInt		= 42;

			RFKField()
			float	someFloat	= 42.42f;

			RFKMethod()
			int		method4(void* ptr);

			RFKMethod()
			void	method1();

			RFKMethod()
			void	method2() const;

			RFKMethod()
			int		method3();

			RFKMethod()
			static	int	staticMethod3(char const* param);

			RFKMethod()
			static	int	staticMethod2();

			RFKMethod()
			static void	staticMethod1();

		public:
			RFKMethod()
			ExampleClass()						= default;
			ExampleClass(ExampleClass const&)	= default;
			ExampleClass(ExampleClass&&)		= default;
			~ExampleClass()						= default;

		//GENERATED

		//static refureku::Type const& staticGetType() noexcept	
		//{	
		//	static bool				initialized = false;	
		//	static refureku::Type	type("ExampleClass", 6613751926088865067, static_cast<refureku::Type::ECategory>(0));	
		//	
		//	if (!initialized)	
		//	{	
		//		//RFRKExampleClass_GenerateMethodsMetadata

		//		//type.methods.emplace_back(new refureku::Method("method1", 42, static_cast<refureku::EAccessSpecifier>(0), &type, new refureku::MemberFunction<ExampleClass, void ()>(& ExampleClass::method1)));
		//		//type.staticMethods.emplace_back(new refureku::StaticMethod("method1", 42, static_cast<refureku::EAccessSpecifier>(0), new refureku::MemberFunction<ExampleClass, void ()>(& ExampleClass::method1)));

		//		type.staticMethods.emplace_back(refureku::StaticMethod("staticMethod1", 16119251974439751062, static_cast<refureku::EAccessSpecifier>(2), std::make_shared<refureku::NonMemberFunction<void ()>>(& ExampleClass::staticMethod1)));

		//		type.methods.emplace_back(
		//			refureku::Method("method4",
		//								533724703896504614,
		//								static_cast<refureku::EAccessSpecifier>(2),
		//								&type,
		//			std::make_shared<refureku::MemberFunction<ExampleClass, int (void *)>>(& ExampleClass::method4)));

		//		initialized = true;	
		//	}	
		//		
		//	return type;	
		//}	
		//	
		//refureku::Type const& getType() const noexcept	
		//{	
		//	return ExampleClass::staticGetType();	
		//}

		//template <typename... ArgTypes>
		//static ExampleClass* instantiate(ArgTypes... args) noexcept
		//{
		//	return new ExampleClass(std::forward<ArgTypes>(args)...);
		//}
		static ExampleClass* __RFKinstantiate() noexcept
		{
			//std::cout << "Use this instantiate" << std::endl;
			return new ExampleClass();
		}

		RFKExampleClass_GENERATED
	};
}