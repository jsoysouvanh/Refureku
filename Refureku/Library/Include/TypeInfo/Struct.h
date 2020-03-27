#pragma once

#include "TypeInfo/Type.h"

namespace refureku
{
	class Struct : public Type
	{
		public:
			struct Parent
			{
				EAccessSpecifier	access;
				Struct const&		type;
			};

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

			Struct(std::string&& newName, uint64 newId, ECategory newCategory)	noexcept;
			Struct(Struct const&)												= default;
			Struct(Struct&&)													= default;
			~Struct()															= default;

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
			bool inheritsFrom(Type const& otherType)											const	noexcept;

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

			Struct& operator=(Struct const&)	= default;
			Struct& operator=(Struct&&)			= default;
	};

	#include "TypeInfo/Struct.inl"
}