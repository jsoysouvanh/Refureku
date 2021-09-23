/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <cassert>
#include <vector>
#include <unordered_set>	//std::unordered_set, std::unordered_multiset
#include <algorithm>
#include <type_traits>	//std::enable_if_t, std::is_invocable_r_v

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/Archetypes/Archetype.h"
#include "Refureku/TypeInfo/Variables/Field.h"
#include "Refureku/TypeInfo/Variables/StaticField.h"
#include "Refureku/TypeInfo/Functions/Method.h"
#include "Refureku/TypeInfo/Functions/StaticMethod.h"
#include "Refureku/TypeInfo/Functions/MethodHelper.h"
#include "Refureku/TypeInfo/Archetypes/EClassKind.h"

namespace rfk
{
	//Forward declarations
	class Enum;
	class ClassTemplate;
	class ClassTemplateInstantiation;

	class Struct : public Archetype
	{
		public:
			using NestedArchetypes	= std::unordered_set<Archetype const*, Entity::PtrNameHasher, Entity::PtrEqualName>;
			using Fields			= std::unordered_multiset<Field, Entity::NameHasher, Entity::EqualName>;
			using StaticFields		= std::unordered_multiset<StaticField, Entity::NameHasher, Entity::EqualName>;

			class Parent
			{
				private:
					/** Parent struct archetype. */
					Struct const&		_archetype;

					/** Inheritance access specifier. */
					EAccessSpecifier	_inheritanceAccessSpecifier;

				public:
					Parent(EAccessSpecifier	inheritanceAccessSpecifier,
						   Struct const&	archetype)					noexcept;

					/**
					*	@brief Getter for the field _archetype.
					* 
					*	@return _archetype.
					*/
					REFUREKU_API Struct const&		getArchetype()						const	noexcept;

					/**
					*	@brief Getter for the field _access.
					* 
					*	@return _access.
					*/
					REFUREKU_API EAccessSpecifier	getInheritanceAccessSpecifier()		const	noexcept;
			};

		private:
			/** Pointer to the default method used to make an instance of this archetype. */
			void*								(*_defaultInstantiator)() = nullptr;

			/** List of all custom instantiators for this archetype. */
			std::vector<StaticMethod const*>	_customInstantiators;

			/** Kind of a rfk::Struct or rfk::Class instance. */
			EClassKind							_classKind;

			/** Structs this struct inherits directly in its declaration. This list includes ONLY reflected parents. */
			std::vector<Parent>					_directParents;

			/** Classes/Structs inheriting from this struct, regardless of their inheritance depth. This list includes ONLY reflected subclasses. */
			std::unordered_set<Struct const*>	_subclasses;

			/** All tagged nested structs/classes/enums contained in this struct. */
			NestedArchetypes					_nestedArchetypes;

			/** All tagged fields contained in this struct, may they be declared in this struct or one of its parents. */
			Fields								_fields;

			/** All tagged static fields contained in this struct, may they be declared in this struct or one of its parents. */
			StaticFields						_staticFields;

			template <typename ReturnType, typename... ArgTypes>
			ReturnType* makeInstanceFromCustomInstantiator(ArgTypes&&... args)	const;

		protected:
			Struct(std::string&&	name,
				   std::size_t		id,
				   std::size_t		memorySize,
				   bool				isClass,
				   EClassKind		classKind)		noexcept;

		public:
			/** All tagged methods declared in this struct. */
			std::unordered_multiset<Method, Entity::NameHasher, Entity::EqualName>				methods;

			/** All tagged static methods declared in this struct. */
			std::unordered_multiset<StaticMethod, Entity::NameHasher, Entity::EqualName>		staticMethods;

			REFUREKU_API Struct(std::string&&	name,
								std::size_t		id,
								std::size_t		memorySize,
								bool			isClass)		noexcept;
			Struct(Struct const&)								= delete;
			Struct(Struct&&)									= delete;

			/**
			*	@brief Retrieve from this struct a nested archetype matching with a given predicate.
			*	
			*	@param predicate Predicate returning true for any matching archetype.
			*	
			*	@return The first matching archetype if any is found, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Archetype const&>>>
			Archetype const*					getNestedArchetype(Predicate predicate)												const;

			/**
			*	@brief Retrieve from this struct a nested struct matching with a given predicate.
			*	
			*	@param predicate Predicate returning true for any matching struct.
			*	
			*	@return The first matching struct if any is found, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Struct const&>>>
			Struct const*						getNestedStruct(Predicate predicate)												const;

			/**
			*	@brief Retrieve from this struct a nested class matching with a given predicate.
			*	
			*	@param predicate Predicate returning true for any matching class.
			*	
			*	@return The first matching class if any is found, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Struct const&>>>
			Struct const*						getNestedClass(Predicate predicate)													const;

			/**
			*	@brief Retrieve from this struct a nested enum matching with a given predicate.
			*	
			*	@param predicate Predicate returning true for any matching enum.
			*	
			*	@return The first matching enum if any is found, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Enum const&>>>
			Enum const*							getNestedEnum(Predicate predicate)													const;

			/**
			*	@brief Retrieve from this struct a field matching with a given predicate.
			*	
			*	@param predicate Predicate returning true for any matching field.
			*	@param shouldInspectInherited Should inherited fields be considered as well in the search process?
			*								  If false, only fields introduced by this struct will be considered.
			*	
			*	@return The first matching field if any is found, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Field const&>>>
			Field const*						getField(Predicate	predicate,
														 bool		shouldInspectInherited	= false)								const;

			/**
			*	@brief Retrieve from this struct all the fields matching with a given predicate.
			*	
			*	@param predicate Predicate returning true for any matching field.
			*	@param shouldInspectInherited Should inherited fields be considered as well in the search process?
			*								  If false, only fields introduced by this struct will be considered.
			*	
			*	@return A vector of all fields matching with the provided predicate.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Field const&>>>
			std::vector<Field const*>			getFields(Predicate	predicate,
														  bool		shouldInspectInherited	= false)								const;

			/**
			*	@brief Retrieve from this struct a static field matching with a given predicate.
			*	
			*	@param predicate Predicate returning true for any matching static field.
			*	@param shouldInspectInherited Should inherited fields be considered as well in the search process?
			*								  If false, only fields introduced by this struct will be considered.
			*	
			*	@return The first matching static field if any is found, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, StaticField const&>>>
			StaticField const*					getStaticField(Predicate	predicate,
															   bool			shouldInspectInherited	= false)						const;

			/**
			*	@brief Retrieve from this struct all static fields matching with a given predicate.
			*	
			*	@param predicate Predicate returning true for any matching static field.
			*	@param shouldInspectInherited Should inherited fields be considered as well in the search process?
			*								  If false, only fields introduced by this struct will be considered.
			*	
			*	@return A vector of all static fields matching with the provided predicate.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, StaticField const&>>>
			std::vector<StaticField const*>		getStaticFields(Predicate	predicate,
																bool		shouldInspectInherited	= false)						const;

			/**
			*	@brief Retrieve from this struct a method matching with a given predicate.
			*	
			*	@param predicate				Predicate returning true for any matching method.
			*	@param shouldInspectInherited	Should inherited methods be considered as well in the search process?
			*									If false, only methods introduced by this struct will be considered.
			*	
			*	@return The first matching method if any is found, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Method const*>>>
			Method const*						getMethod(Predicate predicate,
														  bool		shouldInspectInherited = false)									const;

			/**
			*	@tparam MethodSignature Signature (prototype) of the method to look for.
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
			*	@brief Retrieve from a struct all methods matching with a given predicate.
			*	
			*	@param predicate				Predicate defining the matching method.
			*	@param shouldInspectInherited	Should inherited methods be considered as well in the search process?
			*									If false, only methods introduced by this struct will be considered.
			*	
			*	@return The first method matching with the predicate, nullptr if none was found. 
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Method const*>>>
			std::vector<Method const*>			getMethods(Predicate	predicate,
														   bool			shouldInspectInherited = false)								const;

			/**
			*	@brief Retrieve from this struct a static method matching with a given predicate.
			*	
			*	@param predicate				Predicate returning true for any matching static method.
			*	@param shouldInspectInherited	Should inherited static methods be considered as well in the search process?
			*									If false, only static methods introduced by this struct will be considered.
			*	
			*	@return The first matching static method if any is found, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, StaticMethod const*>>>
			StaticMethod const*					getStaticMethod(Predicate	predicate,
																bool		shouldInspectInherited = false)							const;

			/**
			*	@tparam MethodSignature Signature (prototype) of the static method to look for.
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
																bool				shouldInspectInherited	= false)				const	noexcept;

			/**
			*	@brief Retrieve from this struct all static methods matching with a given predicate.
			*	
			*	@param predicate				Predicate returning true for any matching static method.
			*	@param shouldInspectInherited	Should inherited static methods be considered as well in the search process?
			*									If false, only static methods introduced by this struct will be considered.
			*	
			*	@return All static methods matching with the given predicate.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, StaticMethod const*>>>
			std::vector<StaticMethod const*>	getStaticMethods(Predicate	predicate,
																 bool		shouldInspectInherited = false)							const;

			/**
			*	@brief Make an instance of the class represented by this archetype.
			*
			*	If no argument is specified, the default constructor will be used.
			*	In case the class isn't default constructible, the matching user-specified custom instantiator will be used.
			*	If one or more arguments are provided, the matching user-specified custom instantiator will be used.
			*	
			*	For more information about custom instantiators, see https://github.com/jsoysouvanh/Refureku/wiki/Properties#custominstantiator-method.
			*
			*	@note Memory is not auto-managed and must be freed manually by the user.
			*
			*	@return an instance of this struct if a suitable constructor (no params only) / custom instantator was found,
			*			else nullptr.
			*/
			template <typename ReturnType = void, typename... ArgTypes>
			ReturnType*							makeInstance(ArgTypes&&... args)													const;

			/**
			*	@brief Add the type T to this type's parents if T is a reflected class.
			* 
			*	@param inheritanceAccess The inheritance access for the provided parent.
			*/
			template <typename T>
			void								addParent(EAccessSpecifier inheritanceAccess)												noexcept;

			/**
			*	@brief	Add a new way to instantiate this struct through the makeInstance method.
			*			If the provided static method takes no parameter, it will override the default instantiator.
			*	
			*	@param instantiator Pointer to the static method.
			*/
			template <typename ReturnType>
			void								addCustomInstantiator(StaticMethod const* instantiator)										noexcept;

			/**
			*	@param structName	Name of the nested struct to look for.
			*	@param access		Access specifier of the nested struct in this struct. Use EAccessSpecifier::Undefined if it doesn't matter.
			*
			*	@return The found nested struct if any, else nullptr.
			*/
			REFUREKU_API Struct const*			getNestedStruct(std::string			structName,
																EAccessSpecifier	access = EAccessSpecifier::Undefined)			const	noexcept;

			/**
			*	@param className	Name of the nested class to look for.
			*	@param access		Access specifier of the nested class in this struct. Use EAccessSpecifier::Undefined if it doesn't matter.
			*
			*	@return The found nested class if any, else nullptr.
			*/
			REFUREKU_API Struct const*			getNestedClass(std::string		className,
															   EAccessSpecifier	access = EAccessSpecifier::Undefined)				const	noexcept;

			

			/**
			*	@param enumName	Name of the nested enum to look for.
			*	@param access	Access specifier of the nested enum in this struct. Use EAccessSpecifier::Undefined if it doesn't matter.
			*
			*	@return The found nested class if any, else nullptr.
			*/
			REFUREKU_API Enum const*			getNestedEnum(std::string		enumName,
															  EAccessSpecifier	access = EAccessSpecifier::Undefined)				const	noexcept;

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
			REFUREKU_API Field const*			getField(std::string	fieldName,
														 EFieldFlags	minFlags				= EFieldFlags::Default,
														 bool			shouldInspectInherited	= false)							const	noexcept;

			

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
			REFUREKU_API std::vector<Field const*>	getFields(std::string	fieldName,
															  EFieldFlags	minFlags				= EFieldFlags::Default,
															  bool			shouldInspectInherited	= false)						const	noexcept;

			

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
			REFUREKU_API StaticField const*					getStaticField(std::string	fieldName,
																		   EFieldFlags	minFlags				= EFieldFlags::Default,
																		   bool			shouldInspectInherited	= false)				const	noexcept;

			

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
			REFUREKU_API std::vector<StaticField const*>	getStaticFields(std::string	fieldName,
																			EFieldFlags	minFlags				= EFieldFlags::Default,
																			bool		shouldInspectInherited	= false)				const	noexcept;

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
			REFUREKU_API Method const*			getMethod(std::string const&	methodName,
														  EMethodFlags			minFlags				= EMethodFlags::Default,
														  bool					shouldInspectInherited	= false)					const	noexcept;

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
			REFUREKU_API std::vector<Method const*>	getMethods(std::string const&	methodName,
															   EMethodFlags			minFlags				= EMethodFlags::Default,
															   bool					shouldInspectInherited	= false)					const	noexcept;

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
			REFUREKU_API StaticMethod const*	getStaticMethod(std::string const&	methodName,
																EMethodFlags		minFlags				= EMethodFlags::Default,
																bool				shouldInspectInherited	= false)				const	noexcept;

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
			REFUREKU_API std::vector<StaticMethod const*>	getStaticMethods(std::string const&	methodName,
																			 EMethodFlags		minFlags				= EMethodFlags::Default,
																			 bool				shouldInspectInherited	= false)				const	noexcept;

			/**
			*	@brief	Compute the list of all direct reflected subclasses of this struct.
			*			Direct subclasses are computed by iterating over all subclasses (direct or not), so this method
			*			might have a heavy performance cost on big class hierarchies.
			* 
			*	@return A list of all direct reflected subclasses of this struct.
			*/
			REFUREKU_API std::vector<Struct const*>	getDirectSubclasses()															const	noexcept;

			/**
			*	@return true if this type is a subclass from the provided type, else false.
			*/
			REFUREKU_API bool		isSubclassOf(Struct const& otherType)					const	noexcept;
			
			/**
			*	@return true if this type is a parent (direct or not) of the provided type, else false.
			*/
			REFUREKU_API bool		isBaseOf(Struct const& otherType)						const	noexcept;

			

			/**
			*	@brief Add the parent to this type's parent if it is not nullptr.
			* 
			*	@param parent				The struct to add as parent.
			*	@param inheritanceAccess	The inheritance access for the provided parent.
			*/
			REFUREKU_API void		addParent(Struct const*		parent,
											  EAccessSpecifier	inheritanceAccess)					noexcept;
			
			/**
			*	@brief	Setup the default instantiator to use when a Struct::makeInstance is called without parameters.
			*			If a call to Struct::addCustomInstantiator is made with a static method taking no parameter, the previously set default instantiator will be overriden.
			*
			*	@param defaultInstantiator Pointer to the instantiator method.
			*/
			REFUREKU_API void		setDefaultInstantiator(void*(*defaultInstantiator)())			noexcept;

			/**
			*	@brief Add a field to the struct.
			*	
			*	@param fieldName	Name of the field.
			*	@param entityId		Unique entity if of the field.
			*	@param type			Type of the field.
			*	@param flags		Field flags.
			*	@param outerEntity_	Struct the field was first declared in (in case of inherited field, outerEntity is the parent struct).
			*	@param memoryOffset	Offset in bytes of the field in the struct (obtained from offsetof).
			*	
			*	@return A pointer to the added field. The pointer is made from the iterator, so is unvalidated as soon as the iterator is unvalidated.
			*			The name of the field **MUST NOT** be changed to avoid breaking the hash value, thus the whole underlying container.
			*/
			REFUREKU_API Field*			addField(std::string	fieldName,
												 std::size_t	entityId,
												 Type const&	type,
												 EFieldFlags	flags,
												 Struct const*	outerEntity_,
												 std::size_t	memoryOffset)						noexcept;

			/**
			*	@brief Add a static field to the struct.
			*	
			*	@param fieldName	Name of the static field.
			*	@param entityId		Unique entity if of the static field.
			*	@param type			Type of the static field.
			*	@param flags		Field flags.
			*	@param outerEntity_	Struct the field was first declared in (in case of inherited field, outerEntity is the parent struct).
			*	@param fieldPtr		Pointer to the static field memory.
			*	
			*	@return A pointer to the added static field. The pointer is made from the iterator, so is unvalidated as soon as the iterator is unvalidated.
			*			The name of the static field **MUST NOT** be changed to avoid breaking the hash value, thus the whole underlying container.
			*/
			REFUREKU_API StaticField*	addStaticField(std::string		fieldName,
													   std::size_t		entityId,
													   Type const&		type,
													   EFieldFlags		flags,
													   Struct const*	outerEntity_,
													   void*			fieldPtr)					noexcept;

			/**
			*	@brief	Add a static field to the struct..
			*			Overload with a const field pointer for the addStaticField method.
			* 
			*	@param fieldName	Name of the static field.
			*	@param entityId		Unique entity if of the static field.
			*	@param type			Type of the static field.
			*	@param flags		Field flags.
			*	@param outerEntity_	Struct the field was first declared in (in case of inherited field, outerEntity is the parent struct).
			*	@param fieldPtr		Const pointer to the static field memory.
			*	
			*	@return A pointer to the added static field. The pointer is made from the iterator, so is unvalidated as soon as the iterator is unvalidated.
			*			The name of the static field **MUST NOT** be changed to avoid breaking the hash value, thus the whole underlying container.
			*/
			REFUREKU_API StaticField*	addStaticField(std::string		fieldName,
													   std::size_t		entityId,
													   Type const&		type,
													   EFieldFlags		flags,
													   Struct const*	outerEntity_,
													   void const*		fieldPtr)					noexcept;

			/**
			*	@brief Add a method to the struct.
			*	
			*	@param methodName		Name of the method.
			*	@param entityId			Unique entity id of the method.
			*	@param returnType		Return type of the method call.
			*	@param internalMethod	Pointer to the actual method.
			*	@param flags			Method flags.
			*
			*	@return A pointer to the added method. The pointer is made from the iterator, so is unvalidated as soon as the iterator is unvalidated.
			*			The name of the method **MUST NOT** be changed to avoid breaking the hash value, thus the whole underlying container.
			*/
			REFUREKU_API Method*		addMethod(std::string					methodName,
												  std::size_t					entityId,
												  Type const&					returnType,
												  std::unique_ptr<ICallable>	internalMethod,
												  EMethodFlags					flags)				noexcept;

			/**
			*	@brief Add a static method to the struct.
			*	
			*	@param methodName		Name of the static method.
			*	@param entityId			Unique entity id of the static method.
			*	@param returnType		Return type of the static method call.
			*	@param internalMethod	Pointer to the actual static method.
			*	@param flags			Method flags.
			*
			*	@return A pointer to the added static method. The pointer is made from the iterator, so is unvalidated as soon as the iterator is unvalidated.
			*			The name of the static method **MUST NOT** be changed to avoid breaking the hash value, thus the whole underlying container.
			*/
			REFUREKU_API StaticMethod*	addStaticMethod(std::string					methodName,
														std::size_t					entityId,
														Type const&					returnType,
														std::unique_ptr<ICallable>	internalMethod,
														EMethodFlags				flags)			noexcept;

			/**
			*	@brief Add a nested archetype to the struct.
			*	
			*	@param nestedArchetype	Nested archetype.
			*	@param accessSpeficier	Access of the nested archetype in the struct.
			*	
			*	@param A pointer to the added archetype. The pointer is made from the iterator, so is unvalidated as soon as the iterator is unvalidated.
			*			The name of the archetype **MUST NOT** be changed to avoid breaking the hash value, thus the whole underlying container.
			*/
			REFUREKU_API Archetype*		addNestedArchetype(Archetype const* nestedArchetype,
														   EAccessSpecifier	accessSpecifier)		noexcept;

			/**
			*	@brief	Check if this class is a template or not.
			*			If the method returns true, the object is safely castable to rfk::ClassTemplate.
			* 
			*	@return true if the struct represents a template, else false.
			*/
			inline bool									isTemplate()			const	noexcept;

			/**
			*	@brief	Cast the struct to rfk::ClassTemplate const* if it is a template.
			* 
			*	@return A rfk::ClassTemplate const* if the struct is a template, else nullptr.
			*/
			inline ClassTemplate const*					asTemplate()			const	noexcept;

			/**
			*	@brief	Check if this struct is a template instantiation or not.
			*			If the method returns true, the object is safely castable to rfk::ClassTemplateInstantiation.
			* 
			*	@return true if the struct represents a template instantiation, else false.
			*/
			inline bool									isTemplateInstantiation()	const	noexcept;

			/**
			*	@brief	Cast the struct to rfk::ClassTemplateInstantiation const* if it is a template instantiation.
			* 
			*	@return A rfk::ClassTemplateInstantiation const* if the struct is a template instantiation, else nullptr.
			*/
			inline ClassTemplateInstantiation const*	asTemplateInstantiation()	const	noexcept;

			/*
			*	@brief Getter for the field _classKind.
			*
			*	@return _classKind.
			*/
			REFUREKU_API EClassKind						getClassKind()				const	noexcept;

			/**
			*	@brief Get the index'th direct parent of this struct.
			* 
			*	@return The index'th direct parent of this struct.
			* 
			*	@exception std::out_of_range if the provided index is greater or equal to the number of direct parents of this struct.
			*/
			REFUREKU_API Parent const&					getDirectParentAt(std::size_t index)	const;

			/**
			*	@brief Get the number of direct parents this struct is inheriting from.
			* 
			*	@return The number of direct parents this struct is inheriting from.
			*/
			REFUREKU_API std::size_t					getDirectParentsCount()					const	noexcept;

			/**
			*	@brief	Set the number of direct parents for this struct.
			*			Useful to avoid reallocations and avoid having unused memory.
			*			If the number of direct parents is already >= to the provided count, this method has no effect.
			* 
			*	@param capacity The number of direct parents of this struct.
			*/
			REFUREKU_API void							setDirectParentsCapacity(std::size_t capacity)	noexcept;

			/**
			*	@brief Add a subclass to this struct.
			* 
			*	@param subclass The subclass to add.
			*/
			REFUREKU_API void							addSubclass(Struct const& subclass)							noexcept;

			/**
			*	@brief Execute the given visitor on all archetypes nested in this struct.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			*/
			REFUREKU_API void							foreachNestedArchetype(bool (*visitor)(Archetype const&,
																							   void*),
																			   void* userData)					const	noexcept;

			/**
			*	@brief	Internally pre-allocate enough memory for the provided number of nested archetypes.
			*			If the number of nested archetypes is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of nested archetypes to pre-allocate.
			*/
			REFUREKU_API void							setNestedArchetypesCapacity(std::size_t capacity)				noexcept;

			/**
			*	@brief Execute the given visitor on all fields in this struct.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			*/
			REFUREKU_API void							foreachField(bool (*visitor)(Field const&,
																					 void*),
																	 void* userData)							const	noexcept;

			/**
			*	@brief	Internally pre-allocate enough memory for the provided number of fields.
			*			If the number of fields is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of fields to pre-allocate.
			*/
			REFUREKU_API void							setFieldsCapacity(std::size_t capacity)							noexcept;

			/**
			*	@brief Execute the given visitor on all static fields in this struct.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			*/
			REFUREKU_API void							foreachStaticField(bool (*visitor)(StaticField const&,
																						   void*),
																		   void* userData)						const	noexcept;

			/**
			*	@brief	Internally pre-allocate enough memory for the provided number of static fields.
			*			If the number of fields is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of static fields to pre-allocate.
			*/
			REFUREKU_API void							setStaticFieldsCapacity(std::size_t capacity)					noexcept;
	};

	/**
	*	@brief	Instantiate a class if it is default constructible.
	*			This is the default method used to instantiate classes through Struct::makeInstance.
	*			This method is not noexcept as the provided type T constructor is not guaranteed to be noexcept.
	*	
	*	@return A pointer to a newly allocated instance of the class if the class is default constructible, else nullptr.
	*/
	template <typename T>
	void* defaultInstantiator();

	/* In C++, a struct and a class contains exactly the same data. Alias for convenience. */
	using Class = Struct;

	#include "Refureku/TypeInfo/Archetypes/Struct.inl"
}