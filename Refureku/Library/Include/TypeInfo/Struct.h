#pragma once

#include <vector>
#include <algorithm>

#include "TypeInfo/Archetype.h"
#include "TypeInfo/Fields/Field.h"
#include "TypeInfo/Fields/StaticField.h"
#include "TypeInfo/Methods/Method.h"
#include "TypeInfo/Methods/StaticMethod.h"
#include "TypeInfo/EAccessSpecifier.h"
#include "TypeInfo/GeneratedTraits.h"

namespace refureku
{
	class Struct : public Archetype
	{
		public:
			struct Parent
			{
				EAccessSpecifier	access;
				Struct const&		type;
			};

			/** Direct parent types. This list includes ONLY reflected parents */
			std::vector<Parent>			directParents;

			/** All tagged fields contained in this struct */
			std::vector<Field>			fields;

			/** All tagged static fields contained in this struct */
			std::vector<StaticField>	staticFields;

			/** All tagged methods contained in this struct */
			std::vector<Method>			methods;

			/** All tagged static methods contained in this struct */
			std::vector<StaticMethod>	staticMethods;

			Struct(std::string&& newName, uint64 newId, ECategory newCategory, uint64 newMemorySize)	noexcept;
			Struct(Struct const&)																		= delete;
			Struct(Struct&&)																			= default;
			~Struct()																					= default;

			/**
			*	Get the field named fieldName in this struct.
			*	The method returns nullptr if no field named fieldName was found. 
			*/
			Field const*						getField(std::string const& fieldName)			const	noexcept;

			/**
			*	Get the static field named fieldName in this struct.
			*	The method returns nullptr if no static field named fieldName was found. 
			*/
			StaticField const*					getStaticField(std::string const& fieldName)	const	noexcept;

			/**
			*	
			*/
			Method const*						getMethod(std::string const& methodName)		const	noexcept;
			std::vector<Method const*>			getMethods(std::string const& methodName)		const	noexcept;

			/**
			*
			*/
			StaticMethod const*					getStaticMethod(std::string const& methodName)	const	noexcept;
			std::vector<StaticMethod const*>	getStaticMethods(std::string const& methodName)	const	noexcept;

			//TODO templated staticGetMethod with provided prototype
			//TODO not templated staticGetMethod with provided prototype

			/**
			*	Return true if this type inherits from the provided type, else false.
			*/
			bool inheritsFrom(Archetype const& otherType)										const	noexcept;

			template <typename ReturnType, typename... ArgTypes>
			ReturnType* makeInstance(ArgTypes&&... args)										const	noexcept;

			/**
			*	Add the type T to this type's parents if possible
			*/
			template <typename T>
			void __RFKaddToParentsIfPossible(EAccessSpecifier inheritanceAccess)						noexcept;

			template <typename T>
			void __RFKaddRequiredMethods(std::string&& instantiatePrototype)							noexcept;

			template <typename ReturnType, typename... ArgTypes>
			void __RFKaddInstantiationMethod(std::string&& methodName, uint64 methodId, refureku::EAccessSpecifier accessSpecifier, ReturnType*(*function)(ArgTypes...)) noexcept;

			Struct& operator=(Struct const&)	= delete;
			Struct& operator=(Struct&&)			= default;
	};

	#include "TypeInfo/Struct.inl"
}