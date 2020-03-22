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

		ExampleClass()						= default;
		ExampleClass(ExampleClass const&)	= default;
		ExampleClass(ExampleClass&&)		= default;
		~ExampleClass()						= default;

		//GENERATED CODE

		static refureku::Type const& staticGetType() noexcept
		{
			static refureku::Type type;

			return type;
		}

		refureku::Type const& getType()	const	noexcept
		{
			return ExampleClass::staticGetType();
		}
};