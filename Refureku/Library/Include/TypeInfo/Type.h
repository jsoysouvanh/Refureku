#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "Misc/FundamentalTypes.h"
#include "TypeInfo/Field.h"
#include "TypeInfo/Method.h"
#include "TypeInfo/StaticMethod.h"
#include "TypeInfo/EAccessSpecifier.h"
#include "TypeInfo/GeneratedTraits.h"

namespace refureku
{
	class Type
	{
		protected:
			//TODO extend parent class

		public:
			enum class ECategory : uint8
			{
				Class	= 0,
				Struct,
				Enum,
				Fundamental,
				Undefined,

				Count
			};

			struct Parent
			{
				EAccessSpecifier	access;
				Type const&			type;
			};

			///**
			//*	The full name represents the type name, containing all its qualifiers
			//*	such as const, volatile or nested info (namespace, outer class)
			//*
			//*	i.e. const volatile ExampleNamespace::ExampleClass *const*&
			//*/
			//std::string												fullName;

			///**
			//*	The canonical full name is the full name simplified by unwinding
			//*	all aliases / typedefs
			//*/
			//std::string												canonicalFullName;

			/**
			*	Type name
			*/
			std::string													name;

			/**
			*	Unique id qualifying this type
			*/
			uint64														id;

			/**
			*	Category of this type
			*/
			ECategory													category;

			/**
			*	Parent types
			*	TODO: Move to Struct
			*/
			std::vector<Parent>											parents;

			/**
			*	All tagged methods contained in this type
			*	TODO: Move to Struct
			*/
			std::unordered_map<std::string, std::vector<Method>>		methodsLookupTable;

			/**
			*	All tagged static methods contained in this type
			*	TODO: Move to Struct
			*/
			std::unordered_map<std::string, std::vector<StaticMethod>>	staticMethodsLookupTable;

			Type()				= default;
			Type(Type const&)	= delete;
			Type(Type&&)		= delete;
			~Type()				= default;

			/**
			*	
			*/
			Method const*		getMethod(std::string methodName)		const	noexcept;

			//Method const*		getMethod(std::string methodName, )

			StaticMethod const*	getStaticMethod(std::string methodName)	const	noexcept;

			//TODO templated staticGetMethod with provided prototype
			//TODO not templated staticGetMethod with provided prototype

			/**
			*	Add the type T to this type's parents if possible
			*/
			template <typename T>
			void addToParentsIfPossible(EAccessSpecifier inheritanceAccess)		noexcept;

			Type& operator=(Type const&)	= default;
			Type& operator=(Type&&)			= default;
	};

	#include "TypeInfo/Type.inl"
}