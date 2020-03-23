#pragma once

#include "Generated/ExampleClass.refureku.h"

class RFKClass() ExampleClass
{
	private:

//	protected:

//	public:
		RFKField()
		int		someInt		= 42;
		
		RFKField()
		float	someFloat	= 42.42f;

		RFKMethod()
		void	method1();

		RFKMethod()
		void	method2() const;

		RFKMethod()
		int		method3();

		RFKMethod()
		int		method4(void* ptr);

		RFKMethod()
		static void	staticMethod1();

		RFKMethod()
		static	int	staticMethod2();

		RFKMethod()
		static	int	staticMethod3(char const* param);

	public:
		ExampleClass()						= default;
		ExampleClass(ExampleClass const&)	= default;
		ExampleClass(ExampleClass&&)		= default;
		~ExampleClass()						= default;

		//GENERATED

		//static refureku::Type const& staticGetType() noexcept	
		//{	
		//	static bool				initialized = false;	
		//	static refureku::Type	type;	
		//	
		//	if (!initialized)	
		//	{	
		//		//RFRKExampleClass_GenerateMethodsMetadata

		//		type.methodsLookupTable.emplace("method1", std::vector<refureku::Method>());
		//		type.methodsLookupTable["method1"].emplace_back(refureku::Method(new refureku::MemberFunction<ExampleClass, void ()>(& ExampleClass::method1)));

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

		RFRKExampleClass_GENERATED
};