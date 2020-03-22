#pragma once

#include <string>
#include <vector>

#include "SomeClass.h"

#include "Generated/SomeOtherClass.myCustomExtension.h"

template <typename T>
class SomeTemplateClass
{
	T* someT = nullptr;
};

namespace SomeNamespace
{
	class KGClass() SomeOtherClass
	{
		private:
			KGField(Get[const, &], Get[&])
			float							_someFloat	= 42.42f; 

			KGField(Get[const, &])
			SomeClass						_someClass;

			KGField(Get[const, &])
			SomeTemplateClass<SomeClass>	_someTemplateClass;

			//RfrkField(Get[const, &])
			//std::vector<int>				_someVectorOfInt;
		
			//RfrkField(Get[const, &])
			//std::vector<SomeClass*>			_someVectorOfSomeClass;

			//RfrkField(Get[const, &])
			//std::unordered_map<int, SomeClass*>	_someVectorOfSomeClass2; 

		public:
			SomeOtherClass() = default;

		SomeOtherClass_GENERATED
	};
}