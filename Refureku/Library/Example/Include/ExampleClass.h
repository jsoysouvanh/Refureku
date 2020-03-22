#pragma once

#include "Generated/ExampleClass.refureku.h"

class Class() ExampleClass
{
	private:

	protected:

	public:
		Field()
		int		someInt		= 42;
		
		Field()
		float	someFloat	= 42.42f;

		ExampleClass()						= default;
		ExampleClass(ExampleClass const&)	= default;
		ExampleClass(ExampleClass&&)		= default;
		~ExampleClass()						= default;

		
};