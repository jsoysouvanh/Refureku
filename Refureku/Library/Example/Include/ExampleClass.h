#pragma once

#include "Generated/ExampleClass.refureku.h"

class RFKClass() ExampleClass
{
	RFRKExampleClass_GENERATED

	private:

	protected:

	public:
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
		static	int	staticMethod3(std::string param);

		ExampleClass()						= default;
		ExampleClass(ExampleClass const&)	= default;
		ExampleClass(ExampleClass&&)		= default;
		~ExampleClass()						= default;

		//GENERATED CODE

		//static refureku::Type const& staticGetType() noexcept
		//{
		//	static refureku::Type type;

		//	//Static methods
		//	type.staticMethodLookupTable.reserve(10);	//Replace 10 here by count of static methods

		//	type.staticMethodLookupTable.emplace("staticMethod1", refureku::StaticMethod(new refureku::NonMemberFunction<void()>(&ExampleClass::staticMethod1)));
		//	type.staticMethodLookupTable.emplace("staticMethod2", refureku::StaticMethod(new refureku::NonMemberFunction<int()>(&ExampleClass::staticMethod2)));
		//	type.staticMethodLookupTable.emplace("staticMethod3", refureku::StaticMethod(new refureku::NonMemberFunction<int(std::string)>(&ExampleClass::staticMethod3)));

		//	//Non-static methods
		//	type.methodLookupTable.reserve(10);	//Replace 10 here by count of non-methods

		//	type.methodLookupTable.emplace("method1", refureku::Method(new refureku::MemberFunction<ExampleClass, void()>(&ExampleClass::method1)));
		//	type.methodLookupTable.emplace("method2", refureku::Method(new refureku::MemberFunction<ExampleClass, void()>(&ExampleClass::method2)));
		//	type.methodLookupTable.emplace("method3", refureku::Method(new refureku::MemberFunction<ExampleClass, int()>(&ExampleClass::method3)));
		//	type.methodLookupTable.emplace("method4", refureku::Method(new refureku::MemberFunction<ExampleClass, int(void* ptr)>(&ExampleClass::method4)));

		//	return type;
		//}

		//refureku::Type const& getType()	const	noexcept
		//{
		//	return ExampleClass::staticGetType();
		//}
};