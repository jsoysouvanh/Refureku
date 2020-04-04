#pragma once

#include "TypeInfo/Archetypes/Struct.h"

namespace rfk
{
	class Class : public Struct
	{
		public:
			Class(std::string&& newName, uint64 newId, ECategory newCategory, uint64 newMemorySize)	noexcept;
			Class(Class const&)																		= delete;
			Class(Class&&)																			= default;
			~Class()																				= default;

			Class& operator=(Class const&)	= delete;
			Class& operator=(Class&&)		= default;
	};

	#include "TypeInfo/Archetypes/Class.inl"
}