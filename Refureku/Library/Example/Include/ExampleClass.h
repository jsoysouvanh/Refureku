#pragma once

#include "Generated/ExampleClass.refureku.h"

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

		ExampleClass()						= default;
		ExampleClass(ExampleClass const&)	= default;
		ExampleClass(ExampleClass&&)		= default;
		~ExampleClass()						= default;

		RFRKExampleClass_GENERATED
};