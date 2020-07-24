/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <cassert>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <type_traits>

#include "TypeInfo/Archetypes/Archetype.h"
#include "TypeInfo/Fields/Field.h"
#include "TypeInfo/Fields/StaticField.h"
#include "TypeInfo/Methods/Method.h"
#include "TypeInfo/Methods/StaticMethod.h"
#include "Utility/TypeTraits.h"

namespace rfk
{
	//Forward declaration
	class Class;

	//Forward declaration
	class Enum;

	class Struct : public Archetype
	{
		private:
			template <typename T>
			class GetMethodHelper
			{
				public:
					static bool hasSamePrototype(MethodBase const&)
					{
						//If the code asserts here, it means there's a call to getMethod or getStaticMethod with an invalid template.
						//The template must be a method signature.
						//Example1: void example1Method(int i, float j); -> getMethod<void(int, float)>("example1Method");
						//Example2: static int example2Method();		 -> getStaticMethod<int()>("example2Method");
						assert(false);

						return false;
					}
			};

			template <typename ReturnType, typename... ArgTypes>
			class GetMethodHelper<ReturnType(ArgTypes...)>
			{
				public:
					static bool hasSamePrototype(MethodBase const& method)
					{
						return method.hasSamePrototype<ReturnType, ArgTypes...>();
					}
			};

			/** Pointer to the default method used to make an instance of this archetype. */
			void*								(*_defaultInstantiator)()	noexcept = nullptr;

			/** List of all custom instantiators for this archetype. */
			std::vector<StaticMethod const*>	customInstantiators;

			template <typename ReturnType, typename... ArgTypes>
			ReturnType* makeInstanceFromCustomInstantiator(ArgTypes&&... args)	const noexcept;

		public:
			struct Parent
			{
				struct Hasher
				{
					size_t operator()(rfk::Struct::Parent const& parent) const
					{
						return std::hash<rfk::Struct const*>()(parent.type);
					}
				};

				struct Equal
				{
					bool operator()(rfk::Struct::Parent const& p1, rfk::Struct::Parent const& p2) const
					{
						return p1.type == p2.type;
					}
				};

				EAccessSpecifier	access;
				Struct const*		type;
			};

			/** Structs this struct inherits directly in its declaration. This list includes ONLY reflected parents. */
			//TODO: Update this container for better speed/memory (more likely few elements so unordered_set is overkill)
			std::unordered_set<Parent, Parent::Hasher, Parent::Equal>							directParents;

			/** Classes/Structs inheriting from this struct, regardless of their inheritance depth. This list includes ONLY reflected children. */
			std::unordered_set<Struct const*>													children;

			/** All tagged nested structs/classes/enums contained in this struct. */
			//TODO: Update this container for better speed/memory (more likely few elements so unordered_set is overkill)
			std::unordered_set<Archetype const*, Entity::PtrNameHasher, Entity::PtrEqualName>	nestedArchetypes;

			/** All tagged fields contained in this struct, may they be declared in this struct or one of its parents. */
			std::unordered_multiset<Field, Entity::NameHasher, Entity::EqualName>				fields;

			/** All tagged static fields contained in this struct, may they be declared in this struct or one of its parents. */
			std::unordered_multiset<StaticField, Entity::NameHasher, Entity::EqualName>			staticFields;

			/** All tagged methods declared in this struct. */
			std::unordered_multiset<Method, Entity::NameHasher, Entity::EqualName>				methods;

			/** All tagged static methods declared in this struct. */
			std::unordered_multiset<StaticMethod, Entity::NameHasher, Entity::EqualName>		staticMethods;

			Struct(std::string&& newName, uint64 newId, ECategory newCategory, uint64 newMemorySize)	noexcept;
			Struct(Struct const&)																		= delete;
			Struct(Struct&&)																			= default;
			~Struct()																					= default;

			/**
			*	@param structName	Name of the nested struct to look for.
			*	@param access		Access specifier of the nested struct in this struct. Use EAccessSpecifier::Undefined if it doesn't matter.
			*
			*	@return The found nested struct if any, else nullptr.
			*/
			Struct const*						getNestedStruct(std::string const&	structName,
																EAccessSpecifier	access = EAccessSpecifier::Undefined)			const	noexcept;

			/**
			*	@param className	Name of the nested class to look for.
			*	@param access		Access specifier of the nested class in this struct. Use EAccessSpecifier::Undefined if it doesn't matter.
			*
			*	@return The found nested class if any, else nullptr.
			*/
			Class const*						getNestedClass(std::string const&	className,
																EAccessSpecifier	access = EAccessSpecifier::Undefined)			const	noexcept;

			/**
			*	@param enumName	Name of the nested enum to look for.
			*	@param access	Access specifier of the nested enum in this struct. Use EAccessSpecifier::Undefined if it doesn't matter.
			*
			*	@return The found nested class if any, else nullptr.
			*/
			Enum const*							getNestedEnum(std::string const&	enumName,
															  EAccessSpecifier		access = EAccessSpecifier::Undefined)			const	noexcept;

			/**
			*	@param fieldName Name of the field to retrieve.
			*	@param minFlags Requirements the queried field should fulfill.
			*					Keep in mind that the returned field should contain all of the specified flags,
			*					so setting for example Public and Protected will always return nullptr.
			*					EFieldFlags::Default means no requirement, so the first field named fieldName will be returned.
			*	@param shouldInspectInherited Should inherited fields be considered as well in the search process?
			*								  If false, only fields introduced by this struct will be considered.
			*
			*	@return The first field named fieldName fulfilling all requirements.
			*			The method returns nullptr if none was found. 
			*/
			Field const*						getField(std::string const&	fieldName,
														 EFieldFlags		minFlags				= EFieldFlags::Default,
														 bool				shouldInspectInherited	= false)						const	noexcept;

			/**
			*	@param fieldName Name of the fields to retrieve.
			*	@param minFlags Requirements the queried fields should fulfill.
			*					Keep in mind that the returned fields should contain all of the specified flags,
			*					so setting for example Public and Protected will always return an empty vector.
			*					EFieldFlags::Default means no requirement, so all fields named fieldName will be returned.
			*	@param shouldInspectInherited Should inherited fields be considered as well in the search process?
			*								  If false, only fields introduced by this struct will be considered.
			*
			*	@return A vector of all fields named fieldName fulfilling all requirements.
			*/
			std::vector<Field const*>			getFields(std::string const&	fieldName,
														 EFieldFlags			minFlags				= EFieldFlags::Default,
														 bool					shouldInspectInherited	= false)					const	noexcept;

			/**
			*	@param fieldName Name of the static field to retrieve.
			*	@param minFlags Requirements the queried static field should fulfill.
			*					Keep in mind that the returned static field should contain all of the specified flags,
			*					so setting for example Public and Protected will always return nullptr.
			*					EFieldFlags::Default means no requirement, so the first static field named fieldName will be returned.
			*					Note: It doesn't matter whether you set the Static flag or not as this method is designed to return static fields only.
			*	@param shouldInspectInherited Should inherited static fields be considered as well in the search process?
			*								  If false, only static fields introduced by this struct will be considered.
			*
			*	@return The first static field named fieldName fulfilling all requirements.
			*			The method returns nullptr if none was found. 
			*/
			StaticField const*					getStaticField(std::string const&	fieldName,
															   EFieldFlags			minFlags				= EFieldFlags::Default,
															   bool					shouldInspectInherited	= false)				const	noexcept;

			/**
			*	@param fieldName Name of the static fields to retrieve.
			*	@param minFlags Requirements the queried static fields should fulfill.
			*					Keep in mind that the returned static fields should contain all of the specified flags,
			*					so setting for example Public and Protected will always return an empty vector.
			*					EFieldFlags::Default means no requirement, so all static fields named fieldName will be returned.
			*					Note: It doesn't matter whether you set the Static flag or not as this method is designed to return static fields only.
			*	@param shouldInspectInherited Should inherited static fields be considered as well in the search process?
			*								  If false, only static fields introduced by this struct will be considered.
			*
			*	@return A vector of all static fields named fieldName fulfilling all requirements.
			*/
			std::vector<StaticField const*>		getStaticFields(std::string const&	fieldName,
															   EFieldFlags			minFlags				= EFieldFlags::Default,
															   bool					shouldInspectInherited	= false)				const	noexcept;

			/**
			*	\tparam MethodSignature Signature (prototype) of the method to look for.
			*			Example1: void example1Method(int i, float j);	-> getMethod<void(int, float)>("example1Method");
			*			Example2: int  example2Method() const;			-> getMethod<int()>("example2Method");
			*
			*	@param methodName Name of the method to retrieve.
			*	@param minFlags Requirements the queried method should fulfill.
			*					Keep in mind that the returned method should contain all of the specified flags,
			*					so setting for example Public and Protected will always return nullptr.
			*					EMethodFlags::Default means no requirement, so the first method named methodName will be returned.
			*	@param shouldInspectInherited Should inherited methods be considered as well in the search process?
			*								  If false, only methods introduced by this struct will be considered.
			*
			*	@return The first method named methodName fulfilling all requirements, nullptr if none was found. 
			*/
			template <typename MethodSignature>
			Method const*						getMethod(std::string const&	methodName,
														  EMethodFlags			minFlags				= EMethodFlags::Default,
														  bool					shouldInspectParents	= false)					const	noexcept;

			/**
			*	@param methodName Name of the method to retrieve.
			*	@param minFlags Requirements the queried method should fulfill.
			*					Keep in mind that the returned method should contain all of the specified flags,
			*					so setting for example Public and Protected will always return nullptr.
			*					EMethodFlags::Default means no requirement, so the first method named methodName will be returned.
			*	@param shouldInspectInherited Should inherited methods be considered as well in the search process?
			*								  If false, only methods introduced by this struct will be considered.
			*
			*	@return The first method named methodName fulfilling all requirements, nullptr if none was found. 
			*/
			Method const*						getMethod(std::string const&	methodName,
														  EMethodFlags			minFlags				= EMethodFlags::Default,
														  bool					shouldInspectParents	= false)					const	noexcept;

			/**
			*	@param methodName Name of the methods to retrieve.
			*	@param minFlags Requirements the queried methods should fulfill.
			*					Keep in mind that the returned methods should contain all of the specified flags,
			*					so setting for example Public and Protected will always return an empty vector.
			*					EMethodFlags::Default means no requirement, so all methods named methodName will be returned.
			*	@param shouldInspectInherited Should inherited methods be considered as well in the search process?
			*								  If false, only methods introduced by this struct will be considered.
			*
			*	@return A vector of all methods named methodName fulfilling all requirements. 
			*/
			std::vector<Method const*>			getMethods(std::string const&	methodName,
														   EMethodFlags			minFlags				= EMethodFlags::Default,
														   bool					shouldInspectParents	= false)					const	noexcept;

			/**
			*	\tparam MethodSignature Signature (prototype) of the static method to look for.
			*			Example1: static void example1Method(int i, float j);	-> getStaticMethod<void(int, float)>("example1Method");
			*			Example2: static int  example2Method() const;			-> getStaticMethod<int()>("example2Method");
			*
			*	@param methodName Name of the static method to retrieve.
			*	@param minFlags Requirements the queried static method should fulfill.
			*					Keep in mind that the returned static method should contain all of the specified flags,
			*					so setting for example Public and Protected will always return nullptr.
			*					EMethodFlags::Default means no requirement, so the first static method named methodName will be returned.
			*					Note: It doesn't matter whether you set the Static flag or not as this method is designed to return static methods only.
			*	@param shouldInspectInherited Should inherited static methods be considered as well in the search process?
			*								  If false, only static methods introduced by this struct will be considered.
			*
			*	@return The first static method named methodName fulfilling all requirements, nullptr if none was found. 
			*/
			template <typename MethodSignature>
			StaticMethod const*					getStaticMethod(std::string const&	methodName,
																EMethodFlags		minFlags				= EMethodFlags::Default,
																bool				shouldInspectParents	= false)				const	noexcept;

			/**
			*	@param methodName Name of the static method to retrieve.
			*	@param minFlags Requirements the queried static method should fulfill.
			*					Keep in mind that the returned static method should contain all of the specified flags,
			*					so setting for example Public and Protected will always return nullptr.
			*					EMethodFlags::Default means no requirement, so the first static method named methodName will be returned.
			*					Note: It doesn't matter whether you set the Static flag or not as this method is designed to return static methods only.
			*	@param shouldInspectInherited Should inherited static methods be considered as well in the search process?
			*								  If false, only static methods introduced by this struct will be considered.
			*
			*	@return The first static method named methodName fulfilling all requirements, nullptr if none was found. 
			*/
			StaticMethod const*					getStaticMethod(std::string const&	methodName,
																EMethodFlags		minFlags				= EMethodFlags::Default,
																bool				shouldInspectParents	= false)				const	noexcept;

			/**
			*	@param methodName Name of the static methods to retrieve.
			*	@param minFlags Requirements the queried static methods should fulfill.
			*					Keep in mind that the returned static methods should contain all of the specified flags,
			*					so setting for example Public and Protected will always return an empty vector.
			*					EMethodFlags::Default means no requirement, so all static methods named methodName will be returned.
			*					Note: It doesn't matter whether you set the Static flag or not as this method is designed to return static methods only.
			*	@param shouldInspectInherited Should inherited static methods be considered as well in the search process?
			*								  If false, only static methods introduced by this struct will be considered.
			*
			*	@return All static methods named methodName fulfilling all requirements. 
			*/
			std::vector<StaticMethod const*>	getStaticMethods(std::string const& methodName,
																 EMethodFlags		minFlags				= EMethodFlags::Default,
																 bool				shouldInspectParents	= false)				const	noexcept;

			/**
			*	@brief Make an instance of the class represented by this archetype.
			*
			*	If no argument is specified, the default constructor will be used.
			*	In case the class isn't default constructible, the matching user-specified custom instantiator will be used.
			*	If one or more arguments are provided, the matching user-specified custom instantiator will be used.
			*	
			*	For more information about custom instantiators, see https://github.com/jsoysouvanh/Refureku#custominstantiator-method.
			*
			*	@note Memory is not auto-managed and must be freed manually by the user.
			*
			*	@return an instance of this struct if a suitable constructor (no params only) / custom instantator was found,
			*			else nullptr.
			*/
			template <typename ReturnType = void, typename... ArgTypes>
			ReturnType*	makeInstance(ArgTypes&&... args)													const	noexcept;

			/**
			*	@return true if this type inherits from the provided type, else false.
			*/
			bool		inheritsFrom(Struct const& otherType)												const	noexcept;
			
			/**
			*	@return true if this type is a parent (direct or not) of the provided type, else false.
			*/
			bool		isBaseOf(Struct const& otherType)													const	noexcept;

			/**
			*	Add the type T to this type's parents if possible.
			*	Internal use only.
			*/
			template <typename T>
			void __RFKaddToParents(EAccessSpecifier inheritanceAccess)			noexcept;

			/**
			*	Internal use only.
			*/
			template <typename T>
			void __RFKaddRequiredMethods()										noexcept;

			/**
			*	Internal use only.
			*/
			template <typename ReturnType>
			void __RFKaddCustomInstantiator(StaticMethod const* instantiator)	noexcept;

			/**
			*	Internal use only.
			*/
			void __RFKsetDefaultInstantiationMethod(void*(*func)() noexcept)	noexcept;

			Struct& operator=(Struct const&)	= delete;
			Struct& operator=(Struct&&)			= default;
	};

	#include "TypeInfo/Archetypes/Struct.inl"
}