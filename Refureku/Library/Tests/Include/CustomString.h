#pragma once

#include <string>

#include <Refureku/Object.h>

#include "Generated/CustomString.rfkh.h"

class RFKClass() String : protected std::string, public rfk::Object
{
	public:
		//Use parent class constructors
		using std::string::string;

		RFKMethod()
		inline size_t Size() const noexcept { return std::string::size(); } 

	String_GENERATED
};

File_CustomString_GENERATED