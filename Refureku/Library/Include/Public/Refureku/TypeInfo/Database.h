/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/Misc/Pimpl.h"
#include "Refureku/Misc/Visitor.h"
#include "Refureku/Misc/Predicate.h"
#include "Refureku/Containers/Vector.h"
#include "Refureku/TypeInfo/Variables/EVarFlags.h"
#include "Refureku/TypeInfo/Functions/EFunctionFlags.h"
#include "Refureku/TypeInfo/Functions/FunctionHelper.h"

namespace rfk
{
	//Forward declarations
	class Entity;
	class Namespace;
	class NamespaceFragment;
	class Archetype;
	class Struct;
	using Class = Struct;
	class Enum;
	class FundamentalArchetype;
	class Variable;
	class Function;
	class Method;
	class StaticMethod;
	class Field;
	class StaticField;
	class EnumValue;

	namespace internal
	{
		class DefaultEntityRegistererImpl;
		class ArchetypeRegistererImpl;
		class NamespaceFragmentRegistererImpl;
		class ClassTemplateInstantiationRegistererImpl;
	}

	class Database final
	{
		public:
			REFUREKU_INTERNAL Database()	noexcept;
			Database(Database const&)		= delete;
			Database(Database&&)			= delete;
			REFUREKU_INTERNAL ~Database()	noexcept;

			/**
			*	@brief Retrieve an entity by id.
			*
			*	@param id The id of the entity.
			*
			*	@return A constant pointer to the queried entity if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Entity const*				getEntityById(std::size_t id)													const	noexcept;

			/**
			*	@brief Retrieve a namespace by id.
			*
			*	@param id The id of the namespace.
			*
			*	@return A constant pointer to the queried namespace if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Namespace const*				getNamespaceById(std::size_t id)												const	noexcept;

			/**
			*	@brief	Retrieve a namespace by name.
			*			Can search nested namespaces directly using :: separator.
			*			Example: getNamespace("namespace1::namespace2") will get the namespace2 nested inside namespace1 if it exists.
			*
			*	@param name The name of the namespace.
			*
			*	@return A constant pointer to the queried namespace if it exists, else nullptr.
			*
			*	@exception BadNamespaceFormat if the provided namespace name has : instead of :: as a separator, or starts/ends with :.
			*/
			RFK_NODISCARD REFUREKU_API 
				Namespace const*				getNamespaceByName(char const* name)											const;

			/**
			*	@brief Retrieve the first file level namespace satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid namespace.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return The first file level namespace satisfying the predicate if any, else nullptr.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Namespace const*				getFileLevelNamespaceByPredicate(Predicate<Namespace>	predicate,
																									 void*					userData)				const;

			/**
			*	@brief Retrieve all file level namespaces satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid namespace.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return All file level namespaces satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Vector<Namespace const*>		getFileLevelNamespacesByPredicate(Predicate<Namespace>	predicate,
																									  void*					userData)				const;

			/**
			*	@brief Execute the given visitor on all file level namespaces.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool					foreachFileLevelNamespace(Visitor<Namespace>	visitor,
																		  void*					userData)						const;

			/**
			*	@brief Get the number of reflected file level namespaces in the database.
			* 
			*	@return The number of reflected file level namespaces in the database.
			*/
			REFUREKU_API std::size_t			getFileLevelNamespacesCount()													const	noexcept;

			/**
			*	@brief Retrieve an archetype by id.
			*
			*	@param id The id of the archetype.
			*
			*	@return A constant pointer to the queried archetype if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Archetype const*				getArchetypeById(std::size_t id)												const	noexcept;

			/**
			*	@brief	Retrieve a file level archetype by name.
			*			This method costs heavier performance as it will basically call getClassByName,
			*			getStructByName, getEnumByName and then getFundamentalArchetypeByName to find the queried archetype.
			*	
			*	@param archetypeName Name of the archetype.
			*
			*	@return A constant pointer to the queried archetype if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Archetype const*				getFileLevelArchetypeByName(char const* name)									const	noexcept;

			/**
			*	@brief Retrieve all file level archetypes satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid archetype.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return All file level archetypes satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Vector<Archetype const*>		getFileLevelArchetypesByPredicate(Predicate<Archetype>	predicate,
																				  void*					userData)				const;

			/**
			*	@brief Retrieve a struct by id.
			*
			*	@param id The id of the struct.
			*
			*	@return A constant pointer to the queried struct if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Struct const*					getStructById(std::size_t id)													const	noexcept;

			/**
			*	@brief Retrieve a file level struct by name.
			*
			*	@param name The name of the struct.
			*
			*	@return A constant pointer to the queried struct if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Struct const*					getFileLevelStructByName(char const* name)										const	noexcept;

			/**
			*	@brief Retrieve the first level struct satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid struct.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return The first file level struct satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Struct const*					getFileLevelStructByPredicate(Predicate<Struct>	predicate,
																			  void*				userData)						const;

			/**
			*	@brief Retrieve all file level structs satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid struct.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return All file level structs satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Vector<Struct const*>			getFileLevelStructsByPredicate(Predicate<Struct>	predicate,
																			   void*				userData)					const;

			/**
			*	@brief Execute the given visitor on all file level structs.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool					foreachFileLevelStruct(Visitor<Struct>	visitor,
																	   void*			userData)								const;

			/**
			*	@brief Get the number of reflected file level structs in the database.
			* 
			*	@return The number of reflected file level structs in the database.
			*/
			REFUREKU_API std::size_t			getFileLevelStructsCount()														const	noexcept;

			/**
			*	@brief Retrieve a class by id.
			*
			*	@param id The id of the class.
			*
			*	@return A constant pointer to the queried class if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Class const*					getClassById(std::size_t id)													const	noexcept;

			/**
			*	@brief Retrieve a file level class by name.
			*
			*	@param name The name of the class.
			*
			*	@return A constant pointer to the queried class if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Class const*					getFileLevelClassByName(char const* name)										const	noexcept;

			/**
			*	@brief Retrieve the first level struct satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid struct.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return The first file level struct satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Class const*					getFileLevelClassByPredicate(Predicate<Class>	predicate,
																			 void*				userData)						const;

			/**
			*	@brief Retrieve all file level classes satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid class.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return All file level classes satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Vector<Class const*>			getFileLevelClassesByPredicate(Predicate<Class>	predicate,
																			   void*			userData)						const;

			/**
			*	@brief Execute the given visitor on all file level classes.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool					foreachFileLevelClass(Visitor<Class>	visitor,
																	  void*				userData)								const;

			/**
			*	@brief Get the number of reflected file level classes in the database.
			* 
			*	@return The number of reflected file level classes in the database.
			*/
			REFUREKU_API std::size_t			getFileLevelClassesCount()														const	noexcept;

			/**
			*	@brief Retrieve an enum by id.
			*
			*	@param id The id of the enum.
			*
			*	@return A constant pointer to the queried enum if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Enum const*						getEnumById(std::size_t id)														const	noexcept;

			/**
			*	@brief Retrieve a file level enum by name.
			*
			*	@param name The name of the enum.
			*
			*	@return A constant pointer to the queried enum if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Enum const*						getFileLevelEnumByName(char const* name)										const	noexcept;

			/**
			*	@brief Retrieve the first file level enum satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid enum.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return The first file level enum satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Enum const*						getFileLevelEnumByPredicate(Predicate<Enum>	predicate,
																			void*			userData)							const;

			/**
			*	@brief Retrieve all file level enums satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid enum.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return All file level enums satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Vector<Enum const*>				getFileLevelEnumsByPredicate(Predicate<Enum>	predicate,
																			 void*				userData)						const;

			/**
			*	@brief Execute the given visitor on all file level enums.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool					foreachFileLevelEnum(Visitor<Enum>	visitor,
																	 void*			userData)									const;

			/**
			*	@brief Get the number of reflected file level classes in the database.
			* 
			*	@return The number of reflected file level classes in the database.
			*/
			REFUREKU_API std::size_t			getFileLevelEnumsCount()														const	noexcept;

			/**
			*	@brief Retrieve a fundamental archetype by id.
			*
			*	@param id The id of the fundamental archetype.
			*
			*	@return A constant pointer to the queried fundamental archetype if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				FundamentalArchetype const*		getFundamentalArchetypeById(std::size_t id)										const	noexcept;

			/**
			*	@brief Retrieve a fundamental archetype by name.
			*
			*	@param name The name of the fundamental archetype.
			*
			*	@return A constant pointer to the queried fundamental archetype if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				FundamentalArchetype const*		getFundamentalArchetypeByName(char const* name)									const	noexcept;

			/**
			*	@brief Retrieve a variable by id.
			*
			*	@param id The id of the variable.
			*
			*	@return A constant pointer to the queried variable if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Variable const*					getVariableById(std::size_t id)													const	noexcept;

			/**
			*	@brief Retrieve a file level (non-member) variable by name.
			*	
			*	@param name		The name of the variable.
			*	@param flags	Flags describing the queried variable.
			*					The result variable will have at least the provided flags.
			*	
			*	@return A constant pointer to the queried variable if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Variable const*					getFileLevelVariableByName(char const*	name,
																		   EVarFlags	flags = EVarFlags::Default)				const	noexcept;

			/**
			*	@brief Retrieve the first file level variable satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid variable.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return The first file level variable satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Variable const*					getFileLevelVariableByPredicate(Predicate<Variable>	predicate,
																				void*				userData)					const;

			/**
			*	@brief Retrieve all file level variables satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid variable.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return All file level variables satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Vector<Variable const*>			getFileLevelVariablesByPredicate(Predicate<Variable>	predicate,
																				 void*					userData)				const;

			/**
			*	@brief Execute the given visitor on all file level variables.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool					foreachFileLevelVariable(Visitor<Variable>	visitor,
																		 void*				userData)							const;

			/**
			*	@brief Get the number of reflected file level variables in the database.
			* 
			*	@return The number of reflected file level variables in the database.
			*/
			REFUREKU_API std::size_t			getFileLevelVariablesCount()													const	noexcept;

			/**
			*	@brief Retrieve a function by id.
			*
			*	@param id The id of the function.
			*
			*	@return A constant pointer to the queried function if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Function const*					getFunctionById(std::size_t id)													const	noexcept;

			/**
			*	@brief Retrieve a file level function by name and signature.
			*	
			*	@param name		The name of the function.
			*	@param flags	Flags describing the queried function.
			*					The result function will have at least the provided flags.
			*	
			*	@return A constant pointer to the first function matching the name and flags if it exists, else nullptr.
			*/
			template <typename FunctionSignature>
			RFK_NODISCARD Function const*		getFileLevelFunctionByName(char const*		name,
																		   EFunctionFlags	flags = EFunctionFlags::Default)	const	noexcept;

			/**
			*	@brief Retrieve a file level function by name.
			*	
			*	@param name		The name of the function.
			*	@param flags	Flags describing the queried function.
			*					The result function will have at least the provided flags.
			*	
			*	@return A constant pointer to the first function matching the name and flags if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Function const*					getFileLevelFunctionByName(char const*		name,
																		   EFunctionFlags	flags = EFunctionFlags::Default)	const	noexcept;

			/**
			*	@brief Retrieve all file level functions by name.
			*	
			*	@param name		The name of the function.
			*	@param flags	Flags describing the queried function.
			*					The result function will have at least the provided flags.
			*	
			*	@return All file level functions by name.
			*/
			RFK_NODISCARD REFUREKU_API 
				Vector<Function const*>			getFileLevelFunctionsByName(char const*		name,
																			EFunctionFlags	flags = EFunctionFlags::Default)	const	noexcept;

			/**
			*	@brief Retrieve the first file level function satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid function.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return The first file level function satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Function const*					getFileLevelFunctionByPredicate(Predicate<Function>	predicate,
																				void*				userData)					const;

			/**
			*	@brief Retrieve all file level functions satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid function.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return All file level functions satisfying the predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API 
				Vector<Function const*>			getFileLevelFunctionsByPredicate(Predicate<Function>	predicate,
																				 void*					userData)				const;

			/**
			*	@brief Execute the given visitor on all file level functions.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool					foreachFileLevelFunction(Visitor<Function>	visitor,
																		 void*				userData)							const;

			/**
			*	@brief Get the number of reflected file level functions in the database.
			* 
			*	@return The number of reflected file level functions in the database.
			*/
			REFUREKU_API std::size_t			getFileLevelFunctionsCount()													const	noexcept;

			/**
			*	@brief Retrieve a method by id.
			*
			*	@param id The id of the method.
			*
			*	@return A constant pointer to the queried method if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Method const*					getMethodById(std::size_t id)													const	noexcept;

			/**
			*	@brief Retrieve a static method by id.
			*
			*	@param id The id of the static method.
			*
			*	@return A constant pointer to the queried static method if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				StaticMethod const*				getStaticMethodById(std::size_t id)												const	noexcept;

			/**
			*	@brief Retrieve a field by id.
			*
			*	@param id The id of the field.
			*
			*	@return A constant pointer to the queried field if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				Field const*					getFieldById(std::size_t id)													const	noexcept;

			/**
			*	@brief Retrieve a static field by id.
			*
			*	@param id The id of the static field.
			*
			*	@return A constant pointer to the queried static field if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				StaticField const*				getStaticFieldById(std::size_t id)												const	noexcept;

			/**
			*	@brief Retrieve an enum value by id.
			*
			*	@param id The id of the enum value.
			*
			*	@return A constant pointer to the queried enum value if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API 
				EnumValue const*				getEnumValueById(std::size_t id)												const	noexcept;

		private:
			//Forward declaration
			class DatabaseImpl;

			/** Pointer to the concrete Database implementation. */
			Pimpl<DatabaseImpl>	_pimpl;

			/**
			*	@brief	Get the singleton database instance.
			*			The method must be exported since it contains the singleton.
			* 
			*	@return The database singleton.
			*/
			REFUREKU_API static Database& getInstance() noexcept;

		friend internal::DefaultEntityRegistererImpl;
		friend internal::ArchetypeRegistererImpl;
		friend internal::NamespaceFragmentRegistererImpl;
		friend NamespaceFragment;
		friend internal::ClassTemplateInstantiationRegistererImpl;
		friend REFUREKU_API Database const& getDatabase() noexcept;
	};

	/**
	*	@brief Get a reference to the database of this program.
	* 
	*	@return A reference to the database of this program.
	*/
	REFUREKU_API Database const& getDatabase() noexcept;

	#include "Refureku/TypeInfo/Database.inl"
}