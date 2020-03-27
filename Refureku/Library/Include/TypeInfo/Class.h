#pragma once

#include "TypeInfo/Struct.h"

namespace refureku
{
	class Class : public Struct
	{
		public:
			Class(std::string&& newName, uint64 newId, ECategory newCategory)	noexcept;
			Class(Class const&)													= delete;
			Class(Class&&)														= default;
			~Class()															= default;

			Class& operator=(Class const&)	= delete;
			Class& operator=(Class&&)		= default;
	};
}