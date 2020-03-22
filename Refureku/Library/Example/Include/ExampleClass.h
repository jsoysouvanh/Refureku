#pragma once

#include "Generated/ExampleClass.refureku.h"

#include "TypeInfo/Type.h"

class RFKClass() ExampleClass
{
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

		static refureku::Type const& staticGetType() noexcept
		{
			static refureku::Type type;

			type.staticMethodLookupTable.reserve(2);

			type.staticMethodLookupTable.emplace("staticMethod1", refureku::StaticMethod(new refureku::NonMemberFunction<void()>(&ExampleClass::staticMethod1)));
			type.staticMethodLookupTable.emplace("staticMethod2", refureku::StaticMethod(new refureku::NonMemberFunction<int()>(&ExampleClass::staticMethod2)));
			type.staticMethodLookupTable.emplace("staticMethod3", refureku::StaticMethod(new refureku::NonMemberFunction<int(std::string)>(&ExampleClass::staticMethod3)));

			return type;
		}

		refureku::Type const& getType()	const	noexcept
		{
			return ExampleClass::staticGetType();
		}
};