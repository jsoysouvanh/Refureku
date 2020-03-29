#pragma once

#include "TypeInfo/Struct.h"

namespace refureku
{
	class Class : public Struct
	{
		public:
			Class(std::string&& newName, uint64 newId, ECategory newCategory, uint64 newMemorySize)	noexcept;
			Class(Class const&)																		= delete;
			Class(Class&&)																			= default;
			~Class()																				= default;

			/**
			*	Add the type T to this type's parents if it is reflected.
			*	This is an overload of Struct::__RFKaddToParentsIfPossible(EAccessSpecifier inheritanceAccess) noexcept;
			*/
			template <typename T>
			void __RFKaddToParents(EAccessSpecifier inheritanceAccess) noexcept;

			Class& operator=(Class const&)	= delete;
			Class& operator=(Class&&)		= default;
	};

	#include "TypeInfo/Class.inl"
}