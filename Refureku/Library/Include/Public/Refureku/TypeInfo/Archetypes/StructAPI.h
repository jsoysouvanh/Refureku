/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <type_traits>	//std::is_default_constructible_v

#include "Refureku/TypeInfo/Archetypes/ArchetypeAPI.h"
#include "Refureku/TypeInfo/Archetypes/EClassKind.h"
#include "Refureku/TypeInfo/Variables/EFieldFlags.h"
#include "Refureku/TypeInfo/Functions/EMethodFlags.h"

namespace rfk
{
	//Forward declarations
	class FieldAPI;
	class StaticFieldAPI;
	class MethodAPI;
	class StaticMethodAPI;
	class TypeAPI;
	class ICallable;
	class ClassTemplate;				//TODO: Rename these if rework ClassTemplate API
	class ClassTemplateInstantiation;	//TODO: Rename these if rework ClassTemplateInstantiation API

	class StructAPI : public ArchetypeAPI
	{
		public:
			REFUREKU_API StructAPI(char const*	name,
								   std::size_t	id,
								   std::size_t	memorySize,
								   bool			isClass)		noexcept;
			StructAPI(StructAPI&&)								= delete;	//TODO: Might change this later
			REFUREKU_API ~StructAPI()							noexcept;

			/**
			*	@brief Get the class kind of this instance.
			* 
			*	@return The class kind of this instance.
			*/
			RFK_NODISCARD REFUREKU_API EClassKind	getClassKind()										const	noexcept;

			/**
			*	@brief Add a nested archetype to the struct.
			*	
			*	@param nestedArchetype	Nested archetype.
			*	@param accessSpeficier	Access specifier of the nested archetype in the struct.
			*	
			*	@param A pointer to the added archetype. The pointer is made from the iterator, so is unvalidated as soon as the iterator is unvalidated.
			*/
			REFUREKU_API ArchetypeAPI*				addNestedArchetype(ArchetypeAPI const*	nestedArchetype,
																	   EAccessSpecifier		accessSpecifier)	noexcept;

			/**
			*	@brief Add a field to the struct.
			*	
			*	@param name			Name of the field.
			*	@param id			Unique entity id of the field.
			*	@param type			Type of the field.
			*	@param flags		Field flags.
			*	@param memoryOffset	Offset in bytes of the field in the owner struct (obtained from offsetof).
			*	@param outerEntity	Struct the field was first declared in (in case of inherited field, outerEntity is the parent struct).
			*	
			*	@return A pointer to the added field.
			*			The pointer is made from the iterator, so is unvalidated as soon as the iterator is unvalidated.
			*/
			REFUREKU_API FieldAPI*					addField(char const*		name,
															 std::size_t		id,
															 TypeAPI const&		type,
															 EFieldFlags		flags,
															 std::size_t		memoryOffset,
															 StructAPI const*	outerEntity)					noexcept;

			/**
			*	@brief Add a static field to the struct.
			*	
			*	@param name			Name of the static field.
			*	@param id			Unique entity id of the static field.
			*	@param type			Type of the static field.
			*	@param flags		Field flags.
			*	@param fieldPtr		Pointer to the static field.
			*	@param outerEntity	Struct the field was first declared in (in case of inherited field, outerEntity is the parent struct).
			*	
			*	@return A pointer to the added static field.
			*			The pointer is made from the iterator, so is unvalidated as soon as the iterator is unvalidated.
			*/
			REFUREKU_API StaticFieldAPI*			addStaticField(char const*		name,
																   std::size_t		id,
																   TypeAPI const&	type,
																   EFieldFlags		flags,
																   void*			fieldPtr,
																   StructAPI const*	outerEntity)				noexcept;
			REFUREKU_API StaticFieldAPI*			addStaticField(char const*		name,
																   std::size_t		id,
																   TypeAPI const&	type,
																   EFieldFlags		flags,
																   void const*		fieldPtr,
																   StructAPI const*	outerEntity)				noexcept;

			/**
			*	@brief Add a method to the struct.
			*	
			*	@param name				Name of the method.
			*	@param id				Unique entity id of the method.
			*	@param returnType		Return type of the method call.
			*	@param internalMethod	Dynamically allocated MemberFunction storing the underlying method.
			*	@param flags			Method flags.
			*
			*	@return A pointer to the added method. The pointer is made from the iterator, so is unvalidated as soon as the iterator is unvalidated.
			*/
			REFUREKU_API MethodAPI*					addMethod(char const*		name,
															  std::size_t		id,
															  TypeAPI const&	returnType,
															  ICallable*		internalMethod,
															  EMethodFlags		flags)							noexcept;

			/**
			*	@brief Add a static method to the struct.
			*	
			*	@param methodName		Name of the static method.
			*	@param id				Unique entity id of the static method.
			*	@param returnType		Return type of the static method call.
			*	@param internalMethod	Dynamically allocated NonMemberFunction storing the underlying static method.
			*	@param flags			Method flags.
			*
			*	@return A pointer to the added static method. The pointer is made from the iterator, so is unvalidated as soon as the iterator is unvalidated.
			*/
			REFUREKU_API StaticMethodAPI*			addStaticMethod(char const*		name,
																	std::size_t		id,
																	TypeAPI const&	returnType,
																	ICallable*		internalMethod,
																	EMethodFlags	flags)						noexcept;

			/**
			*	@brief Setup the default instantiator to use when Struct::makeInstance is called without parameters.
			*
			*	@param instantiator Pointer to the instantiator method.
			*/
			REFUREKU_API void						setDefaultInstantiator(void* (*instantiator)())				noexcept;

			/**
			*	@brief	Add a new way to instantiate this struct through the makeInstance method.
			*			If the provided static method takes no parameter, it will override the default instantiator.
			*	
			*	@param instantiator Pointer to the static method.
			*/
			REFUREKU_API void						addInstantiator(StaticMethodAPI const* instantiator)		noexcept;

			/**
			*	@brief Cast the struct to rfk::ClassTemplate const* if it is a template.
			* 
			*	@return A rfk::ClassTemplate const* if the struct is a struct template, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API ClassTemplate const*					asTemplate()				const	noexcept;

			/**
			*	@brief Cast the struct to rfk::ClassTemplateInstantiation const* if it is a template instantiation.
			* 
			*	@return A rfk::ClassTemplateInstantiation const* if the struct is a template instantiation, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API ClassTemplateInstantiation const*	asTemplateInstantiation()	const	noexcept;

		protected:
			//Forward declaration
			class StructImpl;

			REFUREKU_INTERNAL StructAPI(char const*	name,
										std::size_t	id,
										std::size_t	memorySize,
										bool		isClass,
										EClassKind	classKind)		noexcept;
			REFUREKU_INTERNAL StructAPI(StructImpl* implementation)	noexcept;
	};

	namespace internal
	{
		/**
		*	@brief	Instantiate a class if it is default constructible.
		*			This is the default method used to instantiate classes through Struct::makeInstance.
		*			This method is not noexcept as the provided type T constructor is not guaranteed to be noexcept.
		*	
		*	@return A pointer to a newly allocated instance of the class if the class is default constructible, else nullptr.
		* 
		*	@exception Potential exception thrown by T constructor.
		*/
		template <typename T>
		void* defaultInstantiator();
	}

	#include "Refureku/TypeInfo/Archetypes/StructAPI.inl"
}