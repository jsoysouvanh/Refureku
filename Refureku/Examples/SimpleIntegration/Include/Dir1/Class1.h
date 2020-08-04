#pragma once

#include <iostream>

#include "Generated/Class1.rfk.h"

namespace test RFKNamespace()
{
	class RFKClass() Class1
	{
		private:
			RFKField()
			int	someInt = 2;

			RFKMethod()
			void method1()	noexcept { std::cout << "Class1::method1();" << std::endl; }

		protected:
			RFKField() 
			float	someFloat = 0.0f;

		public:
			Class1()	= default;

		Class1_GENERATED
	};
}

File_GENERATED