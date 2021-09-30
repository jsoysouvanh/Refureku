/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <unordered_set>
#include <cassert>

#include "Refureku/TypeInfo/Archetypes/StructAPI.h"
#include "Refureku/TypeInfo/Archetypes/ArchetypeImpl.h"
#include "Refureku/TypeInfo/Entity/EntityHash.h"
#include "Refureku/TypeInfo/Variables/FieldAPI.h"
#include "Refureku/TypeInfo/Variables/StaticFieldAPI.h"
#include "Refureku/TypeInfo/Functions/MethodAPI.h"
#include "Refureku/TypeInfo/Functions/StaticMethodAPI.h"
#include "Refureku/TypeInfo/Functions/NonMemberFunction.h"

namespace rfk
{
	class StructAPI::StructImpl : public ArchetypeAPI::ArchetypeImpl
	{
		private:
			using NestedArchetypes		= std::unordered_set<ArchetypeAPI const*, EntityPtrNameHash, EntityPtrNameEqual>;
			using Fields				= std::unordered_multiset<FieldAPI, EntityNameHash, EntityNameEqual>;
			using StaticFields			= std::unordered_multiset<StaticFieldAPI, EntityNameHash, EntityNameEqual>;
			using Methods				= std::unordered_multiset<MethodAPI, EntityNameHash, EntityNameEqual>;
			using StaticMethods			= std::unordered_multiset<StaticMethodAPI, EntityNameHash, EntityNameEqual>;
			using CustomInstantiators	= std::vector<StaticMethodAPI const*>;
			using CustomInstantiator	= void* (*)();

			//TODO: Order elements for memory efficiency =====================================

			/** All reflected nested structs/classes/enums contained in this struct. */
			NestedArchetypes	_nestedArchetypes;

			/** All reflected fields contained in this struct, may they be declared in this struct or one of its parents. */
			Fields				_fields;

			/** All reflected static fields contained in this struct, may they be declared in this struct or one of its parents. */
			StaticFields		_staticFields;
			
			/** All reflected methods declared in this struct. */
			Methods				_methods;

			/** All reflected static methods declared in this struct. */
			StaticMethods		_staticMethods;

			/** List of all custom instantiators for this archetype. */
			CustomInstantiators	_customInstantiators;

			/** Pointer to the default method used to make an instance of this archetype. */
			CustomInstantiator	_defaultInstantiator;

			/** Kind of a rfk::Struct or rfk::Class instance. */
			EClassKind			_classKind;

		public:
			StructImpl(char const*	name,
					   std::size_t	id,
					   std::size_t	memorySize,
					   bool			isClass,
					   EClassKind	classKind)	noexcept;

			/**
			*	@brief Add a nested archetype to the struct.
			*	
			*	@param nestedArchetype	Nested archetype.
			*	@param accessSpeficier	Access specifier of the nested archetype in the struct.
			*	@param outerEntity		Struct the archetype was first declared in.
			*	
			*	@param A pointer to the added archetype. The pointer is made from the iterator, so is unvalidated as soon as the iterator is unvalidated.
			*/
			RFK_NODISCARD ArchetypeAPI*					addNestedArchetype(ArchetypeAPI const*	nestedArchetype,
																		   EAccessSpecifier		accessSpecifier,
																		   StructAPI const*		outerEntity)		noexcept;

			/**
			*	@brief Add a field to the struct.
			*	
			*	@param name			Name of the field.
			*	@param id			Unique entity id of the field.
			*	@param type			Type of the field.
			*	@param flags		Field flags.
			*	@param owner		Struct the field is belonging to.
			*	@param memoryOffset	Offset in bytes of the field in the owner struct (obtained from offsetof).
			*	@param outerEntity	Struct the field was first declared in (in case of inherited field, outerEntity is the parent struct).
			*	
			*	@return A pointer to the added field. The pointer is made from the iterator, so is unvalidated as soon as the iterator is unvalidated.
			*			The name of the field **MUST NOT** be changed to avoid breaking the hash value, thus the whole underlying container.
			*/
			RFK_NODISCARD FieldAPI*						addField(char const*		name,
																 std::size_t		id,
																 TypeAPI const&		type,
																 EFieldFlags		flags,
																 StructAPI const*	owner,
																 std::size_t		memoryOffset,
																 StructAPI const*	outerEntity)					noexcept;

			/**
			*	@brief Add a static field to the struct.
			*	
			*	@param name			Name of the static field.
			*	@param id			Unique entity id of the static field.
			*	@param type			Type of the static field.
			*	@param flags		Field flags.
			*	@param owner		Struct the static field is belonging to.
			*	@param fieldPtr		Pointer to the static field.
			*	@param outerEntity	Struct the field was first declared in (in case of inherited field, outerEntity is the parent struct).
			*	
			*	@return A pointer to the added static field.
			*			The pointer is made from the iterator, so is unvalidated as soon as the iterator is unvalidated.
			*/
			RFK_NODISCARD StaticFieldAPI*				addStaticField(char const*		name,
																	   std::size_t		id,
																	   TypeAPI const&	type,
																	   EFieldFlags		flags,
																	   StructAPI const*	owner,
																	   void*			fieldPtr,
																	   StructAPI const*	outerEntity)				noexcept;
			RFK_NODISCARD StaticFieldAPI*				addStaticField(char const*		name,
																	   std::size_t		id,
																	   TypeAPI const&	type,
																	   EFieldFlags		flags,
																	   StructAPI const*	owner,
																	   void const*		fieldPtr,
																	   StructAPI const*	outerEntity)				noexcept;

			/**
			*	@brief Add a method to the struct.
			*	
			*	@param name				Name of the method.
			*	@param id				Unique entity id of the method.
			*	@param returnType		Return type of the method call.
			*	@param internalMethod	Pointer to the actual method.
			*	@param flags			Method flags.
			*	@param outerEntity		Struct containing the method declaration.
			*
			*	@return A pointer to the added method. The pointer is made from the iterator, so is unvalidated as soon as the iterator is unvalidated.
			*/
			RFK_NODISCARD MethodAPI*					addMethod(char const*		name,
																  std::size_t		id,
																  TypeAPI const&	returnType,
																  ICallable*		internalMethod,
																  EMethodFlags		flags,
																  StructAPI const*	outerEntity)					noexcept;

			/**
			*	@brief Add a static method to the struct.
			*	
			*	@param methodName		Name of the static method.
			*	@param id				Unique entity id of the static method.
			*	@param returnType		Return type of the static method call.
			*	@param internalMethod	Dynamically allocated NonMemberFunction storing the underlying static method.
			*	@param flags			Method flags.
			*	@param outerEntity		Struct containing the static method declaration.
			*
			*	@return A pointer to the added static method. The pointer is made from the iterator, so is unvalidated as soon as the iterator is unvalidated.
			*/
			RFK_NODISCARD StaticMethodAPI*				addStaticMethod(char const*			name,
																		std::size_t			id,
																		TypeAPI const&		returnType,
																		ICallable*			internalMethod,
																		EMethodFlags		flags,
																		StructAPI const*	outerEntity)			noexcept;

			/**
			*	@brief Setup the default instantiator to use when Struct::makeInstance is called without parameters.
			*
			*	@param instantiator Pointer to the instantiator method.
			*/
			void										setDefaultInstantiator(void* (*instantiator)())				noexcept;

			/**
			*	@brief	Add a new way to instantiate this struct through the makeInstance method.
			*			If the provided static method takes no parameter, it will override the default instantiator.
			*	
			*	@param instantiator Pointer to the static method.
			*/
			void										addInstantiator(StaticMethodAPI const* instantiator)		noexcept;

			/**
			*	@brief Getter for the field _nestedArchetypes.
			* 
			*	@return _nestedArchetypes.
			*/
			RFK_NODISCARD NestedArchetypes const&		getNestedArchetypes()								const	noexcept;

			/**
			*	@brief Getter for the field _fields.
			* 
			*	@return _fields.
			*/
			RFK_NODISCARD Fields const&					getFields()											const	noexcept;

			/**
			*	@brief Getter for the field _staticFields.
			* 
			*	@return _staticFields.
			*/
			RFK_NODISCARD StaticFields const&			getStaticFields()									const	noexcept;

			/**
			*	@brief Getter for the field _methods.
			* 
			*	@return _methods.
			*/
			RFK_NODISCARD Methods const&				getMethods()										const	noexcept;

			/**
			*	@brief Getter for the field _staticMethods.
			* 
			*	@return _staticMethods.
			*/
			RFK_NODISCARD StaticMethods const&			getStaticMethohds()									const	noexcept;

			/**
			*	@brief Getter for the field _customInstantiators.
			* 
			*	@return _customInstantiators.
			*/
			RFK_NODISCARD CustomInstantiators const&	getCustomInstantiators()							const	noexcept;

			/**
			*	@brief Getter for the field _defaultInstantiator.
			* 
			*	@return _defaultInstantiator.
			*/
			RFK_NODISCARD CustomInstantiator			getDefaultInstantiator()							const	noexcept;

			/**
			*	@brief Getter for the field _classKind.
			* 
			*	@return _classKind.
			*/
			RFK_NODISCARD EClassKind					getClassKind()										const	noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/StructImpl.inl"
}