#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "TypeInfo/Field.h"
#include "TypeInfo/Method.h"
#include "TypeInfo/StaticMethod.h"

namespace refureku
{
	class Type
	{
		protected:
			//TODO extend parent class

		public:
			/**
			*	The full name represents the type name, containing all its qualifiers
			*	such as const, volatile or nested info (namespace, outer class)
			*
			*	i.e. const volatile ExampleNamespace::ExampleClass *const*&
			*/
			std::string													fullName;

			/**
			*	The canonical full name is the full name simplified by unwinding
			*	all aliases / typedefs
			*/
			std::string													canonicalFullName;

			/**
			*	All tagged methods contained in this type
			*/
			std::unordered_map<std::string, std::vector<Method>>		methodsLookupTable;

			/**
			*	All tagged static methods contained in this type
			*/
			std::unordered_map<std::string, std::vector<StaticMethod>>	staticMethodsLookupTable;

			Type()				= default;
			Type(Type const&)	= default;
			Type(Type&&)		= delete;
			~Type()				= default;

			/**
			*	
			*/
			Method const*		getMethod(std::string methodName)		const	noexcept;

			//TODO templated getMethod with provided prototype
			//TODO not templated getMethod with provided prototype

			StaticMethod const*	getStaticMethod(std::string methodName)	const	noexcept;

			//TODO templated staticGetMethod with provided prototype
			//TODO not templated staticGetMethod with provided prototype

			Type& operator=(Type const&)	= default;
			Type& operator=(Type&&)			= default;
	};
}