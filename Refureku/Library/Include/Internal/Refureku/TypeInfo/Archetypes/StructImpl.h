/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <unordered_set>
#include <cassert>

#include "Refureku/TypeInfo/Archetypes/Struct.h"
#include "Refureku/TypeInfo/Archetypes/ParentStruct.h"
#include "Refureku/TypeInfo/Archetypes/ArchetypeImpl.h"
#include "Refureku/TypeInfo/Entity/EntityHash.h"
#include "Refureku/TypeInfo/Variables/Field.h"
#include "Refureku/TypeInfo/Variables/StaticField.h"
#include "Refureku/TypeInfo/Functions/Method.h"
#include "Refureku/TypeInfo/Functions/NonMemberFunction.h"
#include "Refureku/Misc/Algorithm.h"

namespace rfk
{
	class Struct::StructImpl : public Archetype::ArchetypeImpl
	{
		public:
			using ParentStructs		= std::vector<ParentStruct>;
			using Subclasses		= std::unordered_set<Struct const*>;
			using NestedArchetypes	= std::unordered_set<Archetype const*, EntityPtrNameHash, EntityPtrNameEqual>;
			using Fields			= std::unordered_multiset<Field, EntityNameHash, EntityNameEqual>;
			using StaticFields		= std::unordered_multiset<StaticField, EntityNameHash, EntityNameEqual>;
			using Methods			= std::unordered_multiset<Method, EntityNameHash, EntityNameEqual>;
			using StaticMethods		= std::unordered_multiset<StaticMethod, EntityNameHash, EntityNameEqual>;
			using Instantiators		= std::vector<StaticMethod const*>;
		
		private:
			/** Structs this struct inherits directly in its declaration. This list includes ONLY reflected parents. */
			ParentStructs		_directParents;

			/** Classes/Structs inheriting from this struct, regardless of their inheritance depth. This list includes ONLY reflected subclasses. */
			Subclasses			_subclasses;

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
			Instantiators		_instantiators;

			/** Kind of a rfk::Struct or rfk::Class instance. */
			EClassKind			_classKind;

		public:
			inline StructImpl(char const*	name,
							  std::size_t	id,
							  std::size_t	memorySize,
							  bool			isClass,
							  EClassKind	classKind)	noexcept;

			/**
			*	@brief	Set the number of direct parents for this struct.
			*			Useful to avoid reallocations and avoid having unused memory.
			*			If the number of direct parents is already >= to the provided count, this method has no effect.
			* 
			*	@param capacity The number of direct parents of this struct.
			*/
			inline void									setDirectParentsCapacity(std::size_t capacity)					noexcept;

			/**
			*	@brief	Internally pre-allocate enough memory for the provided number of nested archetypes.
			*			If the number of nested archetypes is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of nested archetypes to pre-allocate.
			*/
			inline void									setNestedArchetypesCapacity(std::size_t capacity)				noexcept;

			/**
			*	@brief	Internally pre-allocate enough memory for the provided number of fields.
			*			If the number of fields is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of fields to pre-allocate.
			*/
			inline void									setFieldsCapacity(std::size_t capacity)							noexcept;

			/**
			*	@brief	Internally pre-allocate enough memory for the provided number of static fields.
			*			If the number of static fields is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of static fields to pre-allocate.
			*/
			inline void									setStaticFieldsCapacity(std::size_t capacity)					noexcept;

			/**
			*	@brief	Internally pre-allocate enough memory for the provided number of methods.
			*			If the number of methods is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of methods to pre-allocate.
			*/
			inline void									setMethodsCapacity(std::size_t capacity)						noexcept;

			/**
			*	@brief	Internally pre-allocate enough memory for the provided number of static methods.
			*			If the number of static methods is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of static methods to pre-allocate.
			*/
			inline void									setStaticMethodsCapacity(std::size_t capacity)					noexcept;

			/**
			*	@brief Add a parent to this struct if the provided archetype is valid.
			* 
			*	@param archetype			Archetype of the parent struct/class.
			*	@param inheritanceAccess	The inheritance access for the provided parent.
			*/
			inline void									addDirectParent(Struct const& archetype,
																		EAccessSpecifier inheritanceAccess)				noexcept;

			/**
			*	@brief Add a subclass to this struct.
			* 
			*	@param subclass The subclass to add.
			*/
			inline void									addSubclass(Struct const& subclass)								noexcept;

			/**
			*	@brief Add a nested archetype to the struct.
			*	
			*	@param nestedArchetype	Nested archetype.
			*	@param accessSpeficier	Access specifier of the nested archetype in the struct.
			*	@param outerEntity		Struct the archetype was first declared in.
			*	
			*	@param A pointer to the added archetype. The pointer is made from the iterator, so is unvalidated as soon as the iterator is unvalidated.
			*/
			RFK_NODISCARD inline Archetype*				addNestedArchetype(Archetype const*		nestedArchetype,
																		   EAccessSpecifier		accessSpecifier,
																		   Struct const*		outerEntity)			noexcept;

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
			RFK_NODISCARD inline Field*					addField(char const*	name,
																 std::size_t	id,
																 Type const&	type,
																 EFieldFlags	flags,
																 Struct const*	owner,
																 std::size_t	memoryOffset,
																 Struct const*	outerEntity)							noexcept;

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
			RFK_NODISCARD inline StaticField*			addStaticField(char const*		name,
																	   std::size_t		id,
																	   Type const&		type,
																	   EFieldFlags		flags,
																	   Struct const*	owner,
																	   void*			fieldPtr,
																	   Struct const*	outerEntity)					noexcept;
			RFK_NODISCARD inline StaticField*			addStaticField(char const*		name,
																	   std::size_t		id,
																	   Type const&		type,
																	   EFieldFlags		flags,
																	   Struct const*	owner,
																	   void const*		fieldPtr,
																	   Struct const*	outerEntity)					noexcept;

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
			RFK_NODISCARD inline Method*				addMethod(char const*	name,
																  std::size_t	id,
																  Type const&	returnType,
																  ICallable*	internalMethod,
																  EMethodFlags	flags,
																  Struct const*	outerEntity)							noexcept;

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
			RFK_NODISCARD inline StaticMethod*			addStaticMethod(char const*		name,
																		std::size_t		id,
																		Type const&		returnType,
																		ICallable*		internalMethod,
																		EMethodFlags	flags,
																		Struct const*	outerEntity)					noexcept;

			/**
			*	@brief	Add a new way to instantiate this struct through the makeInstance method.
			*			If the provided static method takes no parameter, it will override the default instantiator.
			*	
			*	@param instantiator Pointer to the static method.
			*/
			inline void									addInstantiator(StaticMethod const& instantiator)				noexcept;

			/**
			*	@brief Get a nested archetype by name / access specifier.
			* 
			*	@param name		Name of the searched nested archetype.
			*	@param access	Access specifier of the nested struct in this struct. Use EAccessSpecifier::Undefined if it doesn't matter.
			* 
			*	@return The found nested archetype if any, else nullptr.
			*/
			RFK_NODISCARD inline Archetype const*		getNestedArchetype(char const*		name,
																		   EAccessSpecifier	access)				const	noexcept;

			/**
			*	@brief Getter for the field _directParents.
			* 
			*	@return _directParents.
			*/
			RFK_NODISCARD inline ParentStructs const&		getDirectParents()									const	noexcept;

			/**
			*	@brief Getter for the field _subclasses.
			* 
			*	@return _subclasses.
			*/
			RFK_NODISCARD inline Subclasses const&			getSubclasses()										const	noexcept;

			/**
			*	@brief Getter for the field _nestedArchetypes.
			* 
			*	@return _nestedArchetypes.
			*/
			RFK_NODISCARD inline NestedArchetypes const&	getNestedArchetypes()								const	noexcept;

			/**
			*	@brief Getter for the field _fields.
			* 
			*	@return _fields.
			*/
			RFK_NODISCARD inline Fields const&				getFields()											const	noexcept;

			/**
			*	@brief Getter for the field _staticFields.
			* 
			*	@return _staticFields.
			*/
			RFK_NODISCARD inline StaticFields const&		getStaticFields()									const	noexcept;

			/**
			*	@brief Getter for the field _methods.
			* 
			*	@return _methods.
			*/
			RFK_NODISCARD inline Methods const&				getMethods()										const	noexcept;

			/**
			*	@brief Getter for the field _staticMethods.
			* 
			*	@return _staticMethods.
			*/
			RFK_NODISCARD inline StaticMethods const&		getStaticMethods()									const	noexcept;

			/**
			*	@brief Getter for the field _instantiators.
			* 
			*	@return _instantiators.
			*/
			RFK_NODISCARD inline Instantiators const&		getInstantiators()									const	noexcept;

			/**
			*	@brief Getter for the field _classKind.
			* 
			*	@return _classKind.
			*/
			RFK_NODISCARD inline EClassKind					getClassKind()										const	noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/StructImpl.inl"
}