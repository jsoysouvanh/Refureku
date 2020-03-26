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

			/**
			*	Type name
			*/
			std::string					name;

			/**
			*	Unique id qualifying this type
			*/
			uint64						id			= 0u;

			/**
			*	Category of this type
			*/
			ECategory					category	= ECategory::Undefined;

			/**
			*	Direct parent types. This list includes ONLY reflected parents
			*	TODO: Move to Struct
			*/
			std::vector<Parent>			directParents;

			/**
			*	All tagged methods contained in this type
			*	TODO: Move to Struct
			*/
			std::vector<Method>			methods;

			/**
			*	All tagged static methods contained in this type
			*	TODO: Move to Struct
			*/
			std::vector<StaticMethod>	staticMethods;

			Type(std::string&& newName, uint64 newId, ECategory newCategory)	noexcept;
			Type(Type const&)													= delete;
			Type(Type&&)														= delete;
			~Type()																= default;

			/**
			*	
			*/
			Method const*		getMethod(std::string const& methodName)		const	noexcept;

			//TODO
			//Method const*		getMethod(std::string methodName, )

			StaticMethod const*	getStaticMethod(std::string const& methodName)	const	noexcept;

			//TODO templated staticGetMethod with provided prototype
			//TODO not templated staticGetMethod with provided prototype

			/**
			*	Return true if this type inherits from the provided type, else false.
			*/
			bool inheritsFrom(Type const& otherType)																const	noexcept;

			/**
			*	Add the type T to this type's parents if possible
			*/
			template <typename T>
			void addToParentsIfPossible(EAccessSpecifier inheritanceAccess)													noexcept;

			template <typename T>
			void addRequiredMethods()																						noexcept
			{
				//Instantiate method, make sure it's static
				if constexpr (generated::implements___RFKinstantiate<T, T*()>::value)
				{
					if constexpr (!std::is_member_function_pointer<decltype(&T::__RFKinstantiate)>::value)
					{
						//std::cout << "Added default instantiate()" << std::endl;
						//TODO rework method container as a vector
						//TODO emplace &T::__RFKinstantiate
					}
				}
				else
				{
					//std::cout << "Failed to add default instantiate()" << std::endl;
				}
			}

			/*
			TODO:
			template <typename T>
			void addInstantiationMethod() noexcept
			{

			}
			*/

			/**  */
			template <typename ReturnType, typename... ArgTypes>
			ReturnType* makeInstance(ArgTypes&&... args) const noexcept
			{
				//TODO: replace by complicated name
				//Get right instantiate according to ReturnType & ArgTypes
				StaticMethod const* instantiator = getStaticMethod("instantiate");

				if (instantiator != nullptr)
					return instantiator->invoke<ReturnType*>(std::forward<ArgTypes>(args)...);
				else
					return nullptr;
			}

			Type& operator=(Type const&)	= default;
			Type& operator=(Type&&)			= default;
	};

	#include "TypeInfo/Type.inl"
}