#pragma once

#include <vector>

#include "Dir1/Class1.h"

#include "Generated/Class2.rfk.h"

class RFKClass() Class2 : public test::Class1
{
	private:
		RFKField()
		double				someDouble	= 0.0;

		RFKField()
		std::vector<test::Class1>	vec;

	protected:
		RFKField()
		test::Class1*		class1		= nullptr;

	public:
		Class2() = default;

	Class2_GENERATED
};