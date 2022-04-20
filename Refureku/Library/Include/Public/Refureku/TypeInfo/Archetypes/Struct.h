/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cstddef> //std::ptrdiff_t
#include <type_traits> //std::is_default_constructible_v, std::is_pointer_v, std::is_reference_v

#include "Refureku/TypeInfo/Cast.h"
#include "Refureku/TypeInfo/Archetypes/Archetype.h"
#include "Refureku/TypeInfo/Functions/StaticMethod.h"	//make[Unique/Shared]Instance<> uses StaticMethod wrapper so must include
#include "Refureku/TypeInfo/Archetypes/EClassKind.h"
#include "Refureku/TypeInfo/Variables/EFieldFlags.h"
#include "Refureku/TypeInfo/Functions/EMethodFlags.h"
#include "Refureku/TypeInfo/Functions/MethodHelper.h"
#include "Refureku/Containers/Vector.h"
#include "Refureku/Misc/SharedPtr.h"
#include "Refureku/Misc/UniquePtr.h"

namespace rfk
{
	//Forward declarations
	class ParentStruct;
	class Enum;
	class Field;
	class StaticField;
	class Method;
	class Type;
	class ICallable;
	class Struct;
	
	/* In C++, a struct and a class contain exactly the same data. Alias for convenience. */
	using Class = Struct;

	class Struct : public Archetype
	{
		public:
			REFUREKU_API Struct(char const*	name,
								std::size_t	id,
								std::size_t	memorySize,
								bool		isClass)	noexcept;
			REFUREKU_API ~Struct()						noexcept;

			/**
			*	@brief	Make an instance of the class represented by this archetype with the matching instantiator.
			*			One can add new instantiators to any class by using the Instantiator method property.
			*
			*	@return An instance of this struct if a suitable instantiator was found, else nullptr.
			*			This method can use both instantiators returning rfk::SharedPtr and rfk::UniquePtr.
			*			However, make a shared instance through a unique instantiator has a slightly higher performance impact
			*			since a unique ptr is created and then moved to construct the returned shared ptr.
			* 
			*	@exception Any exception potentially thrown by the used instantiator.
			*/
			template <typename ReturnType, typename... ArgTypes>
			RFK_NODISCARD 
				rfk::SharedPtr<ReturnType>			makeSharedInstance(ArgTypes&&... args)												const;

			/**
			*	@brief	Make an instance of the class represented by this archetype with the matching instantiator.
			*			One can add new instantiators to any class by using the Instantiator method property.
			*
			*	@return An instance of this struct if a suitable instantiator was found, else nullptr.
			*			This method can only use instantiators returning rfk::UniquePtr.
			* 
			*	@exception Any exception potentially thrown by the used instantiator.
			*/
			template <typename ReturnType, typename... ArgTypes>
			RFK_NODISCARD 
				rfk::UniquePtr<ReturnType>			makeUniqueInstance(ArgTypes&&... args)												const;

			/**
			*	@brief	Compute the list of all direct reflected subclasses of this struct.
			*			Direct subclasses are computed by iterating over all subclasses (direct or not), so this method
			*			might have a heavy performance cost on big class hierarchies.
			* 
			*	@return A list of all direct reflected subclasses of this struct.
			*/
			RFK_NODISCARD REFUREKU_API
				Vector<Struct const*>				getDirectSubclasses()																const	noexcept;

			/**
			*	@brief Check if this struct is a subclass of another struct/class.
			* 
			*	@param archetype Archetype of the tested parent struct/class.
			* 
			*	@return true if this struct is a subclass of the provided archetype, else false.
			*			Note that if the provided archetype is the same as this struct, false is returned.
			*/
			RFK_NODISCARD REFUREKU_API bool			isSubclassOf(Struct const& archetype)												const	noexcept;

			/**
			*	@brief Check if this struct is a base class of another struct/class.
			* 
			*	@param archetype Archetype of the tested child struct/class.
			* 
			*	@return true if this struct is a base class of the provided archetype, else false.
			*			Note that if the provided archetype is the same as this struct, true is returned.
			*/
			RFK_NODISCARD REFUREKU_API bool			isBaseOf(Struct const& archetype)													const	noexcept;

			/**
			*	@brief	Get the index'th direct parent of this struct.
			*			If index is greater or equal to getDirectParentsCount(), the behaviour is undefined.
			* 
			*	@return The index'th direct parent of this struct.
			*/
			RFK_NODISCARD REFUREKU_API 
				ParentStruct const&					getDirectParentAt(std::size_t index)												const	noexcept;

			/**
			*	@brief Get the number of reflected direct parents this struct is inheriting from.
			* 
			*	@return The number of direct parents this struct is inheriting from.
			*/
			RFK_NODISCARD REFUREKU_API std::size_t	getDirectParentsCount()																const	noexcept;

			/**
			*	@brief Execute the given visitor on all direct parents of this struct.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool						foreachDirectParent(Visitor<ParentStruct>	visitor,
																		void*					userData)								const;

			/**
			*	@param structName	Name of the nested struct to look for.
			*	@param access		Access specifier of the nested struct in this struct. Use EAccessSpecifier::Undefined if it doesn't matter.
			*
			*	@return The found nested struct if any, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Struct const*						getNestedStructByName(char const*		name,
																		  EAccessSpecifier	access = EAccessSpecifier::Undefined)		const	noexcept;

			/**
			*	@brief Retrieve the first nested struct satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid nested struct.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return The first found nested struct satisfying the predicate if any, else nullptr.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Struct const*						getNestedStructByPredicate(Predicate<Struct>	predicate,
																			   void*				userData)							const;

			/**
			*	@brief Retrieve all nested structs satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid nested struct.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return All nested structs satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Vector<Struct const*>				getNestedStructsByPredicate(Predicate<Struct>	predicate,
																				void*				userData)							const;

			/**
			*	@param className	Name of the nested class to look for.
			*	@param access		Access specifier of the nested class in this struct. Use EAccessSpecifier::Undefined if it doesn't matter.
			*
			*	@return The found nested class if any, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Class const*						getNestedClassByName(char const*		name,
																		 EAccessSpecifier	access = EAccessSpecifier::Undefined)		const	noexcept;

			/**
			*	@brief Retrieve the first nested class satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid nested class.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return The first found nested class satisfying the predicate if any, else nullptr.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Class const*						getNestedClassByPredicate(Predicate<Class>	predicate,
																			  void*				userData)								const;

			/**
			*	@brief Retrieve all nested classes satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid nested class.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return All nested classes satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Vector<Class const*>				getNestedClassesByPredicate(Predicate<Class> predicate,
																				void*			 userData)								const;

			/**
			*	@param enumName	Name of the nested enum to look for.
			*	@param access	Access specifier of the nested enum in this struct. Use EAccessSpecifier::Undefined if it doesn't matter.
			*
			*	@return The found nested class if any, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Enum const*							getNestedEnumByName(char const*		 name,
																		EAccessSpecifier access = EAccessSpecifier::Undefined)			const	noexcept;

			/**
			*	@brief Retrieve the first nested enum satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid nested enum.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return The first found nested enum satisfying the predicate if any, else nullptr.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Enum const*							getNestedEnumByPredicate(Predicate<Enum>	predicate,
																			 void*				userData)								const;

			/**
			*	@brief Retrieve all nested enums satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid nested enum.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return All nested enums satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Vector<Enum const*>					getNestedEnumsByPredicate(Predicate<Enum>	predicate,
																			  void*				userData)								const;

			/**
			*	@brief Execute the given visitor on all archetypes nested in this struct.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool						foreachNestedArchetype(Visitor<Archetype>	visitor,
																		   void*				userData)								const;

			/**
			*	@brief Get the number of archetypes nested in this struct.
			* 
			*	@return The number of archetypes nested in this struct.
			*/
			REFUREKU_API std::size_t				getNestedArchetypesCount()															const	noexcept;

			/**
			*	@param name						Name of the field to retrieve.
			*	@param minFlags					Requirements the queried field should fulfill.
			*										Keep in mind that the returned field should contain all of the specified flags,
			*										so setting for example Public and Protected will always return nullptr.
			*										EFieldFlags::Default means no requirement, so the first field named fieldName will be returned.
			*	@param shouldInspectInherited	Should inherited fields be considered as well in the search process?
			*										If false, only fields introduced by this struct will be considered.
			*
			*	@return The first field named fieldName fulfilling all requirements.
			*			The method returns nullptr if none was found. 
			*/
			RFK_NODISCARD REFUREKU_API 
				Field const*						getFieldByName(char const* name,
																   EFieldFlags minFlags = EFieldFlags::Default,
																   bool		   shouldInspectInherited	= false)						const	noexcept;

			/**
			*	@brief Retrieve the first field satisfying the provided predicate.
			*	
			*	@param predicate				Predicate defining a valid field.
			*	@param userData					User data forwarded to the predicate calls.
			*	@param shouldInspectInherited	Should inherited fields be considered as well in the search process?
			*										If false, only fields introduced by this struct will be considered.
			* 
			*	@return The first found field satisfying the predicate if any, else nullptr.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Field const*						getFieldByPredicate(Predicate<Field>	predicate,
																		void*				userData,
																		bool				shouldInspectInherited = false)				const;

			/**
			*	@brief Retrieve all fields satisfying the provided predicate.
			*	
			*	@param predicate				Predicate defining a valid field.
			*	@param userData					User data forwarded to the predicate calls.
			*	@param shouldInspectInherited	Should inherited fields be considered as well in the search process?
			*										If false, only fields introduced by this struct will be considered.
			*	@param orderedByDeclaration		Should fields be ordered by declaration order in the result collection?
			* 
			*	@return All fields satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Vector<Field const*>				getFieldsByPredicate(Predicate<Field>	predicate,
																		 void*				userData,
																		 bool				shouldInspectInherited = false,
																		 bool				orderedByDeclaration = false)				const;

			/**
			*	@brief Execute the given visitor on all fields in this struct.
			* 
			*	@param visitor					Visitor function to call. Return false to abort the foreach loop.
			*	@param userData					Optional user data forwarded to the visitor.
			*	@param shouldInspectInherited	Should inherited fields be considered as well in the search process?
			*										If false, only fields introduced by this struct will be considered.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool						foreachField(Visitor<Field>	visitor,
																 void*			userData,
																 bool			shouldInspectInherited = false)							const;

			/**
			*	@brief Get the number of fields (including inherited ones) in this struct.
			* 
			*	@return The number of fields in this struct.
			*/
			REFUREKU_API std::size_t				getFieldsCount()																	const	noexcept;

			/**
			*	@param name						Name of the static field to retrieve.
			*	@param minFlags					Requirements the queried static field should fulfill.
			*										Keep in mind that the returned static field should contain all of the specified flags,
			*										so setting for example Public and Protected will always return nullptr.
			*										EFieldFlags::Default means no requirement, so the first static field named fieldName will be returned.
			*										Note: It doesn't matter whether you set the Static flag or not as this method is designed to return static fields only.
			*	@param shouldInspectInherited	Should inherited static fields be considered as well in the search process?
			*										If false, only static fields introduced by this struct will be considered.
			*
			*	@return The first static field named fieldName fulfilling all requirements.
			*			The method returns nullptr if none was found. 
			*/
			RFK_NODISCARD REFUREKU_API 
				StaticField const*					getStaticFieldByName(char const* name,
																		 EFieldFlags minFlags = EFieldFlags::Default,
																		 bool		 shouldInspectInherited	= false)					const	noexcept;

			/**
			*	@brief Retrieve the first static field satisfying the provided predicate.
			*	
			*	@param predicate				Predicate defining a valid static field.
			*	@param userData					User data forwarded to the predicate calls.
			*	@param shouldInspectInherited	Should inherited static fields be considered as well in the search process?
			*										If false, only static fields introduced by this struct will be considered.
			* 
			*	@return The first found static field satisfying the predicate if any, else nullptr.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				StaticField const*					getStaticFieldByPredicate(Predicate<StaticField> predicate,
																			  void*					 userData,
																			  bool					 shouldInspectInherited	= false)	const;

			/**
			*	@brief Retrieve all static fields satisfying the provided predicate.
			*	
			*	@param predicate				Predicate defining a valid static field.
			*	@param userData					User data forwarded to the predicate calls.
			*	@param shouldInspectInherited	Should inherited static fields be considered as well in the search process?
			*										If false, only static fields introduced by this struct will be considered.
			* 
			*	@return All static fields satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Vector<StaticField const*>			getStaticFieldsByPredicate(Predicate<StaticField>	predicate,
																			   void*					userData,
																			   bool						shouldInspectInherited = false)	const;

			/**
			*	@brief Execute the given visitor on all static fields in this struct.
			* 
			*	@param visitor					Visitor function to call. Return false to abort the foreach loop.
			*	@param userData					Optional user data forwarded to the visitor.
			*	@param shouldInspectInherited	Should inherited static fields be considered as well in the search process?
			*										If false, only fields introduced by this struct will be considered.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool						foreachStaticField(Visitor<StaticField>	visitor,
																	   void*				userData,
																	   bool					shouldInspectInherited	= false)			const;

			/**
			*	@brief Get the number of static fields (including inherited ones) in this struct.
			* 
			*	@return The number of static fields in this struct.
			*/
			REFUREKU_API std::size_t				getStaticFieldsCount()																const	noexcept;

			/**
			*	@brief	Get a method by name and signature. This template overload using signature comes handy when wanting to disambiguate
			*			2 method overloads with and without const qualifier for example.
			* 
			*	@param name						Name of the method to retrieve.
			*	@param minFlags					Requirements the queried method should fulfill.
			*										Keep in mind that the returned method should contain all of the specified flags,
			*										so setting for example Public and Protected will always return nullptr.
			*										EMethodFlags::Default means no requirement, so the first method named methodName will be returned.
			*	@param shouldInspectInherited	Should inherited methods be considered as well in the search process?
			*										If false, only methods introduced by this struct will be considered.
			*
			*	@return The first method named methodName fulfilling all requirements, nullptr if none was found. 
			*/
			template <typename MethodSignature>
			RFK_NODISCARD Method const*				getMethodByName(char const*  name,
																	EMethodFlags minFlags = EMethodFlags::Default,
																	bool		 shouldInspectInherited	= false)						const	noexcept;

			/**
			*	@param name						Name of the method to retrieve.
			*	@param minFlags					Requirements the queried method should fulfill.
			*										Keep in mind that the returned method should contain all of the specified flags,
			*										so setting for example Public and Protected will always return nullptr.
			*										EMethodFlags::Default means no requirement, so the first method named methodName will be returned.
			*	@param shouldInspectInherited	Should inherited methods be considered as well in the search process?
			*										If false, only methods introduced by this struct will be considered.
			*
			*	@return The first method named methodName fulfilling all requirements, nullptr if none was found. 
			*/
			RFK_NODISCARD REFUREKU_API
				Method const*						getMethodByName(char const*  name,
																	EMethodFlags minFlags = EMethodFlags::Default,
																	bool		 shouldInspectInherited	= false)						const	noexcept;

			/**
			*	@param name						Name of the methods to retrieve.
			*	@param minFlags					Requirements the queried methods should fulfill.
			*										Keep in mind that the returned methods should contain all of the specified flags,
			*										so setting for example Public and Protected will always return an empty vector.
			*										EMethodFlags::Default means no requirement, so all methods named methodName will be returned.
			*	@param shouldInspectInherited	Should inherited methods be considered as well in the search process?
			*										If false, only methods introduced by this struct will be considered.
			*
			*	@return A vector of all methods named methodName fulfilling all requirements. 
			*/
			RFK_NODISCARD REFUREKU_API 
				Vector<Method const*>				getMethodsByName(char const*  name,
																	 EMethodFlags minFlags = EMethodFlags::Default,
																	 bool		  shouldInspectInherited = false)						const	noexcept;

			/**
			*	@brief Retrieve the first method satisfying the provided predicate.
			*	
			*	@param predicate				Predicate defining a valid method.
			*	@param userData					User data forwarded to the predicate calls.
			*	@param shouldInspectInherited	Should inherited methods be considered as well in the search process?
			*										If false, only methods introduced by this struct will be considered.
			* 
			*	@return The first found method satisfying the predicate if any, else nullptr.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API
				Method const*						getMethodByPredicate(Predicate<Method>	predicate,
																		 void*				userData,
																		 bool				shouldInspectInherited = false)				const;

			/**
			*	@brief Retrieve all methods satisfying the provided predicate.
			*	
			*	@param predicate				Predicate defining a valid method.
			*	@param userData					User data forwarded to the predicate calls.
			*	@param shouldInspectInherited	Should inherited methods be considered as well in the search process?
			*										If false, only methods introduced by this struct will be considered.
			* 
			*	@return All methods satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Vector<Method const*>				getMethodsByPredicate(Predicate<Method> predicate,
																		  void*				userData,
																		  bool				shouldInspectInherited = false)				const;

			/**
			*	@brief Execute the given visitor on all methods in this struct.
			* 
			*	@param visitor					Visitor function to call. Return false to abort the foreach loop.
			*	@param userData					Optional user data forwarded to the visitor.
			*	@param shouldInspectInherited	Should iterate on inherited methods as well?
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool						foreachMethod(Visitor<Method>	visitor,
																  void*				userData,
																  bool				shouldInspectInherited = false)						const;

			/**
			*	@brief Get the number of methods (excluding inherited ones) in this struct.
			* 
			*	@return The number of methods in this struct.
			*/
			REFUREKU_API std::size_t				getMethodsCount()																	const	noexcept;

			/**
			*	@param name						Name of the static method to retrieve.
			*	@param minFlags					Requirements the queried static method should fulfill.
			*										Keep in mind that the returned static method should contain all of the specified flags,
			*										so setting for example Public and Protected will always return nullptr.
			*										EMethodFlags::Default means no requirement, so the first static method named methodName will be returned.
			*										Note: It doesn't matter whether you set the Static flag or not as this method is designed to return static methods only.
			*	@param shouldInspectInherited	Should inherited static methods be considered as well in the search process?
			*										If false, only static methods introduced by this struct will be considered.
			*
			*	@return The first static method named methodName fulfilling all requirements, nullptr if none was found. 
			*/
			template <typename StaticMethodSignature>
			RFK_NODISCARD StaticMethod const*		getStaticMethodByName(char const*  name,
																		  EMethodFlags minFlags = EMethodFlags::Default,
																		  bool		   shouldInspectInherited = false)					const	noexcept;

			/**
			*	@param name						Name of the static method to retrieve.
			*	@param minFlags					Requirements the queried static method should fulfill.
			*										Keep in mind that the returned static method should contain all of the specified flags,
			*										so setting for example Public and Protected will always return nullptr.
			*										EMethodFlags::Default means no requirement, so the first static method named methodName will be returned.
			*										Note: It doesn't matter whether you set the Static flag or not as this method is designed to return static methods only.
			*	@param shouldInspectInherited	Should inherited static methods be considered as well in the search process?
			*										If false, only static methods introduced by this struct will be considered.
			*
			*	@return The first static method named methodName fulfilling all requirements, nullptr if none was found. 
			*/
			RFK_NODISCARD REFUREKU_API 
				StaticMethod const*					getStaticMethodByName(char const*  name,
																		  EMethodFlags minFlags = EMethodFlags::Default,
																		  bool		   shouldInspectInherited = false)					const	noexcept;

			/**
			*	@param methodName				Name of the static methods to retrieve.
			*	@param minFlags					Requirements the queried static methods should fulfill.
			*										Keep in mind that the returned static methods should contain all of the specified flags,
			*										so setting for example Public and Protected will always return an empty vector.
			*										EMethodFlags::Default means no requirement, so all static methods named methodName will be returned.
			*										Note: It doesn't matter whether you set the Static flag or not as this method is designed to return static methods only.
			*	@param shouldInspectInherited	Should inherited static methods be considered as well in the search process?
			*										If false, only static methods introduced by this struct will be considered.
			*
			*	@return All static methods named methodName fulfilling all requirements. 
			*/
			RFK_NODISCARD REFUREKU_API
				Vector<StaticMethod const*>			getStaticMethodsByName(char const*  name,
																		   EMethodFlags minFlags = EMethodFlags::Default,
																		   bool			shouldInspectInherited = false)					const	noexcept;

			/**
			*	@brief Retrieve the first static method satisfying the provided predicate.
			*	
			*	@param predicate				Predicate defining a valid static method.
			*	@param userData					User data forwarded to the predicate calls.
			*	@param shouldInspectInherited	Should inherited static methods be considered as well in the search process?
			*										If false, only static methods introduced by this struct will be considered.
			* 
			*	@return The first found static method satisfying the predicate if any, else nullptr.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API
				StaticMethod const*					getStaticMethodByPredicate(Predicate<StaticMethod>	predicate,
																			   void*					userData,
																			   bool						shouldInspectInherited = false)	const;

			/**
			*	@brief Retrieve all static methods satisfying the provided predicate.
			*	
			*	@param predicate				Predicate defining a valid static method.
			*	@param userData					User data forwarded to the predicate calls.
			*	@param shouldInspectInherited	Should inherited static methods be considered as well in the search process?
			*										If false, only static methods introduced by this struct will be considered.
			* 
			*	@return All static methods satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Vector<StaticMethod const*>			getStaticMethodsByPredicate(Predicate<StaticMethod> predicate,
																				void*					userData,
																				bool					shouldInspectInherited = false)	const;

			/**
			*	@brief Execute the given visitor on all static methods in this struct.
			* 
			*	@param visitor					Visitor function to call. Return false to abort the foreach loop.
			*	@param userData					Optional user data forwarded to the visitor.
			*	@param shouldInspectInherited	Should iterate on inherited static methods as well?
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool						foreachStaticMethod(Visitor<StaticMethod>	visitor,
																		void*					userData,
																		bool					shouldInspectInherited = false)			const;

			/**
			*	@brief Get the number of static methods (excluding inherited ones) in this struct.
			* 
			*	@return The number of static methods in this struct.
			*/
			REFUREKU_API std::size_t				getStaticMethodsCount()																const	noexcept;

			/**
			*	@brief Get the class kind of this instance.
			* 
			*	@return The class kind of this instance.
			*/
			RFK_NODISCARD REFUREKU_API EClassKind	getClassKind()																		const	noexcept;

			/**
			*	@brief	Get the pointer offset to transform an instance of this Struct pointer to a pointer of the provided Struct.
			*			Search in both directions (whether to is a parent class or a child class).
			* 
			*	@param to				 Struct metadata of the target struct.
			*	@param out_pointerOffset The resulting pointer offset if found.
			* 
			*	@return true if the pointer offset was found (out_pointerOffset contains the result), else false.
			*/
			RFK_NODISCARD REFUREKU_API bool			getPointerOffset(Struct const& to, std::ptrdiff_t& out_pointerOffset)				const	noexcept;

			/**
			*	@brief	Get the pointer offset to transform an instance of this Struct pointer to a pointer of the provided Struct.
			*			Only search the offset in this struct subclasses. If to is a parent of this struct, false will be returned.
			* 
			*	@param to				 Struct metadata of the target struct.
			*	@param out_pointerOffset The resulting pointer offset if found.
			* 
			*	@return true if the pointer offset was found (out_pointerOffset contains the result), else false.
			*/
			RFK_NODISCARD REFUREKU_API bool			getSubclassPointerOffset(Struct const& to, std::ptrdiff_t& out_pointerOffset)		const	noexcept;

			/**
			*	@brief Add a parent to this struct if the provided archetype is a valid struct/class.
			* 
			*	@param archetype			Archetype of the parent struct/class.
			*	@param inheritanceAccess	The inheritance access for the provided parent.
			*/
			REFUREKU_API void						addDirectParent(Archetype const*	archetype,
																	EAccessSpecifier	inheritanceAccess)										noexcept;

			/**
			*	@brief	Set the number of direct parents for this struct.
			*			Useful to avoid reallocations and avoid having unused memory.
			*			If the number of direct parents is already >= to the provided count, this method has no effect.
			* 
			*	@param capacity The number of direct parents of this struct.
			*/
			REFUREKU_API void						setDirectParentsCapacity(std::size_t capacity)												noexcept;

			/**
			*	@brief Add a subclass to this struct.
			* 
			*	@param subclass					The subclass to add.
			*	@param subclassPointerOffset	Memory offset to add to a subclass instance pointer to obtain a valid pointer to this base struct.
			*/
			REFUREKU_API void						addSubclass(Struct const&  subclass,
																std::ptrdiff_t subclassPointerOffset)											noexcept;

			/**
			*	@brief Add a nested archetype to the struct.
			*	
			*	@param nestedArchetype	Nested archetype.
			*	@param accessSpeficier	Access specifier of the nested archetype in the struct.
			*/
			REFUREKU_API void						addNestedArchetype(Archetype const*	nestedArchetype,
																	   EAccessSpecifier	accessSpecifier)										noexcept;

			/**
			*	@brief	Internally pre-allocate enough memory for the provided number of nested archetypes.
			*			If the number of nested archetypes is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of nested archetypes to pre-allocate.
			*/
			REFUREKU_API void						setNestedArchetypesCapacity(std::size_t capacity)											noexcept;

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
			*			If any of the parameters is unvalid, no field is added and nullptr is returned.
			*/
			REFUREKU_API Field*						addField(char const*	name,
															 std::size_t	id,
															 Type const&	type,
															 EFieldFlags	flags,
															 std::size_t	memoryOffset,
															 Struct const*	outerEntity)														noexcept;

			/**
			*	@brief	Internally pre-allocate enough memory for the provided number of fields.
			*			If the number of fields is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of fields to pre-allocate.
			*/
			REFUREKU_API void						setFieldsCapacity(std::size_t capacity)														noexcept;
				
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
			*			If any of the parameters is unvalid, no static field is added and nullptr is returned.
			*/
			REFUREKU_API StaticField*				addStaticField(char const*		name,
																   std::size_t		id,
																   Type const&		type,
																   EFieldFlags		flags,
																   void*			fieldPtr,
																   Struct const*	outerEntity)												noexcept;
			REFUREKU_API StaticField*				addStaticField(char const*		name,
																   std::size_t		id,
																   Type const&		type,
																   EFieldFlags		flags,
																   void const*		fieldPtr,
																   Struct const*	outerEntity)												noexcept;

			/**
			*	@brief	Internally pre-allocate enough memory for the provided number of static fields.
			*			If the number of static fields is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of static fields to pre-allocate.
			*/
			REFUREKU_API void						setStaticFieldsCapacity(std::size_t capacity)												noexcept;

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
			*			If any of the parameters is unvalid, no method is added and nullptr is returned.
			*/
			REFUREKU_API Method*					addMethod(char const*	name,
															  std::size_t	id,
															  Type const&	returnType,
															  ICallable*	internalMethod,
															  EMethodFlags	flags)																noexcept;

			/**
			*	@brief	Internally pre-allocate enough memory for the provided number of methods.
			*			If the number of methods is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of methods to pre-allocate.
			*/
			REFUREKU_API void						setMethodsCapacity(std::size_t capacity)													noexcept;

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
			*			If any of the parameters is unvalid, no static method is added and nullptr is returned.
			*/
			REFUREKU_API StaticMethod*				addStaticMethod(char const*		name,
																	std::size_t		id,
																	Type const&		returnType,
																	ICallable*		internalMethod,
																	EMethodFlags	flags)														noexcept;

			/**
			*	@brief	Internally pre-allocate enough memory for the provided number of static methods.
			*			If the number of static methods is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of static methods to pre-allocate.
			*/
			REFUREKU_API void						setStaticMethodsCapacity(std::size_t capacity)												noexcept;

			/**
			*	@brief	Add a new way to instantiate this struct through the makeSharedInstance method.
			*			The passed static method MUST return a rfk::SharedPtr<StructType>. Otherwise, the behaviour is undefined
			*			when calling Struct::makeSharedInstance.
			*	
			*	@param instantiator Pointer to the static method.
			*/
			REFUREKU_API void						addSharedInstantiator(StaticMethod const& instantiator)										noexcept;

			/**
			*	@brief	Add a new way to instantiate this struct through the makeUniqueInstance method.
			*			The passed static method MUST return a rfk::UniquePtr<StructType>. Otherwise, the behaviour is undefined
			*			when calling Struct::makeUniqueInstance.
			*	
			*	@param instantiator Pointer to the static method.
			*/
			REFUREKU_API void						addUniqueInstantiator(StaticMethod const& instantiator)										noexcept;

		protected:
			//Forward declaration
			class StructImpl;

			REFUREKU_INTERNAL Struct(char const*	name,
									 std::size_t	id,
									 std::size_t	memorySize,
									 bool			isClass,
									 EClassKind		classKind)		noexcept;
			REFUREKU_INTERNAL Struct(StructImpl* implementation)	noexcept;

			RFK_GEN_GET_PIMPL(StructImpl, Entity::getPimpl())

		private:
			/**
			*	@brief Execute the given visitor on all shared instantiators taking a given number of parameters in this struct.
			* 
			*	@param argCount	Number of arguments the instantiator takes.
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool	foreachSharedInstantiator(std::size_t			argCount,
														  Visitor<StaticMethod>	visitor,
														  void*					userData)	const;

			/**
			*	@brief Execute the given visitor on all unique instantiators taking a given number of parameters in this struct.
			* 
			*	@param argCount	Number of arguments the instantiator takes.
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool	foreachUniqueInstantiator(std::size_t			argCount,
														  Visitor<StaticMethod>	visitor,
														  void*					userData)	const;
	};

	REFUREKU_TEMPLATE_API(rfk::Allocator<Struct const*>);
	REFUREKU_TEMPLATE_API(rfk::Vector<Struct const*, rfk::Allocator<Struct const*>>);

	#include "Refureku/TypeInfo/Archetypes/Struct.inl"
}