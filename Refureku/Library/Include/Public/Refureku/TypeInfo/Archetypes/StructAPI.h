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
	class ParentStruct;
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
			*	@brief	Compute the list of all direct reflected subclasses of this struct.
			*			Direct subclasses are computed by iterating over all subclasses (direct or not), so this method
			*			might have a heavy performance cost on big class hierarchies.
			* 
			*	@return A list of all direct reflected subclasses of this struct.
			*/
			RFK_NODISCARD REFUREKU_API rfk::Vector<StructAPI const*>		getDirectSubclasses()										const	noexcept;

			/**
			*	@brief Check if this struct is a subclass of another struct/class.
			* 
			*	@param archetype Archetype of the tested parent struct/class.
			* 
			*	@return true if this struct is a subclass of the provided archetype, else false.
			*			Note that if the provided archetype is the same as this struct, false is returned.
			*/
			RFK_NODISCARD REFUREKU_API bool									isSubclassOf(StructAPI const& archetype)					const	noexcept;

			/**
			*	@brief Check if this struct is a base class of another struct/class.
			* 
			*	@param archetype Archetype of the tested child struct/class.
			* 
			*	@return true if this struct is a base class of the provided archetype, else false.
			*			Note that if the provided archetype is the same as this struct, true is returned.
			*/
			RFK_NODISCARD REFUREKU_API bool									isBaseOf(StructAPI const& archetype)						const	noexcept;

			/**
			*	@brief	Get the index'th direct parent of this struct.
			*			If index is greater or equal to getDirectParentsCount(), the behaviour is undefined.
			* 
			*	@return The index'th direct parent of this struct.
			*/
			RFK_NODISCARD REFUREKU_API ParentStruct const&					getDirectParentAt(std::size_t index)						const	noexcept;

			/**
			*	@brief Get the number of direct parents this struct is inheriting from.
			* 
			*	@return The number of direct parents this struct is inheriting from.
			*/
			RFK_NODISCARD REFUREKU_API std::size_t							getDirectParentsCount()										const	noexcept;

			/**
			*	@brief Execute the given visitor on all archetypes nested in this struct.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			*/
			REFUREKU_API bool												foreachNestedArchetype(bool (*visitor)(ArchetypeAPI const&,
																												   void*),
																								   void* userData)						const	noexcept;

			/**
			*	@brief Execute the given visitor on all fields in this struct.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			*/
			REFUREKU_API bool												foreachField(bool (*visitor)(FieldAPI const&,
																										 void*),
																						 void* userData)								const	noexcept;

			/**
			*	@brief Execute the given visitor on all static fields in this struct.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			*/
			REFUREKU_API bool												foreachStaticField(bool (*visitor)(StaticFieldAPI const&,
																											   void*),
																							   void* userData)							const	noexcept;

			/**
			*	@brief Execute the given visitor on all methods in this struct.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			*/
			REFUREKU_API bool												foreachMethod(bool (*visitor)(MethodAPI const&,
																										  void*),
																						  void* userData)								const	noexcept;

			/**
			*	@brief Execute the given visitor on all static methods in this struct.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			*/
			REFUREKU_API bool												foreachStaticMethod(bool (*visitor)(StaticMethodAPI const&,
																												void*),
																								void* userData)							const	noexcept;

			/**
			*	@brief Get the class kind of this instance.
			* 
			*	@return The class kind of this instance.
			*/
			RFK_NODISCARD REFUREKU_API EClassKind							getClassKind()												const	noexcept;

			/**
			*	@brief Cast the struct to rfk::ClassTemplate const* if it is a template.
			* 
			*	@return A rfk::ClassTemplate const* if the struct is a struct template, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API ClassTemplate const*					asTemplate()												const	noexcept;

			/**
			*	@brief Cast the struct to rfk::ClassTemplateInstantiation const* if it is a template instantiation.
			* 
			*	@return A rfk::ClassTemplateInstantiation const* if the struct is a template instantiation, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API ClassTemplateInstantiation const*	asTemplateInstantiation()									const	noexcept;

			/**
			*	@brief Add a parent to this struct if the provided archetype is a valid struct/class.
			* 
			*	@param archetype			Archetype of the parent struct/class.
			*	@param inheritanceAccess	The inheritance access for the provided parent.
			*/
			REFUREKU_API void						addDirectParent(ArchetypeAPI const*	archetype,
																	EAccessSpecifier	inheritanceAccess)		noexcept;

			/**
			*	@brief	Set the number of direct parents for this struct.
			*			Useful to avoid reallocations and avoid having unused memory.
			*			If the number of direct parents is already >= to the provided count, this method has no effect.
			* 
			*	@param capacity The number of direct parents of this struct.
			*/
			REFUREKU_API void						setDirectParentsCapacity(std::size_t capacity)				noexcept;

			/**
			*	@brief Add a subclass to this struct.
			* 
			*	@param subclass The subclass to add.
			*/
			REFUREKU_API void						addSubclass(StructAPI const& subclass)						noexcept;

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
			*	@brief	Internally pre-allocate enough memory for the provided number of nested archetypes.
			*			If the number of nested archetypes is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of nested archetypes to pre-allocate.
			*/
			REFUREKU_API void						setNestedArchetypesCapacity(std::size_t capacity)			noexcept;

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
			*	@brief	Internally pre-allocate enough memory for the provided number of fields.
			*			If the number of fields is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of fields to pre-allocate.
			*/
			REFUREKU_API void						setFieldsCapacity(std::size_t capacity)						noexcept;

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
			*	@brief	Internally pre-allocate enough memory for the provided number of static fields.
			*			If the number of static fields is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of static fields to pre-allocate.
			*/
			REFUREKU_API void						setStaticFieldsCapacity(std::size_t capacity)				noexcept;

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
			*	@brief	Internally pre-allocate enough memory for the provided number of methods.
			*			If the number of methods is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of methods to pre-allocate.
			*/
			REFUREKU_API void						setMethodsCapacity(std::size_t capacity)					noexcept;

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
			*	@brief	Internally pre-allocate enough memory for the provided number of static methods.
			*			If the number of static methods is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of static methods to pre-allocate.
			*/
			REFUREKU_API void						setStaticMethodsCapacity(std::size_t capacity)				noexcept;

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