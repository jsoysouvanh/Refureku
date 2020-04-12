#pragma once

#include <vector>
#include <unordered_set>
#include <algorithm>
#include <type_traits>

#include "TypeInfo/Archetypes/Archetype.h"
#include "TypeInfo/Fields/Field.h"
#include "TypeInfo/Fields/StaticField.h"
#include "TypeInfo/Methods/Method.h"
#include "TypeInfo/Methods/StaticMethod.h"
#include "TypeInfo/EAccessSpecifier.h"
#include "Utility/TypeTraits.h"

namespace rfk
{
	class Struct : public Archetype
	{
		private:
			/** Pointer to the default method used to make an instance of this archetype */
			void*								(*_defaultInstantiator)()	noexcept = nullptr;

			/** List of all custom instantiators for this archetype */
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

			/** Structs this struct inherits directly in its declaration. This list includes ONLY reflected parents */
			std::unordered_set<Parent, Parent::Hasher, Parent::Equal>						directParents;

			/** Structs inheriting from this struct, regardless of their inheritance depth. This list includes ONLY reflected children */
			std::unordered_set<Struct const*>												children;

			/** All tagged fields contained in this struct, may they be declared in this struct or one of its parents (direct or not) */
			std::unordered_multiset<Field, Entity::NameHasher, Entity::EqualName>			fields;

			/** All tagged static fields contained in this struct, may they be declared in this struct or one of its parents (direct or not)  */
			std::unordered_multiset<StaticField, Entity::NameHasher, Entity::EqualName>		staticFields;

			/** All tagged methods declared in this struct */
			std::unordered_multiset<Method, Entity::NameHasher, Entity::EqualName>			methods;

			/** All tagged static methods declared in this struct */
			std::unordered_multiset<StaticMethod, Entity::NameHasher, Entity::EqualName>	staticMethods;

			Struct(std::string&& newName, uint64 newId, ECategory newCategory, uint64 newMemorySize)	noexcept;
			Struct(Struct const&)																		= delete;
			Struct(Struct&&)																			= default;
			~Struct()																					= default;

			/**
			*	Get the first field named fieldName in this struct.
			*	The method returns nullptr if no field named fieldName was found. 
			*/
			Field const*						getField(std::string const& fieldName,
														 EFieldFlags minFlags = EFieldFlags::Default,
														 bool shouldInspectInherited = false)				const	noexcept;
			std::vector<Field const*>			getFields(std::string const& fieldName,
														 EFieldFlags minFlags = EFieldFlags::Default,
														 bool shouldInspectInherited = false)				const	noexcept;

			/**
			*	Get the static field named fieldName in this struct.
			*	The method returns nullptr if no static field named fieldName was found. 
			*/
			StaticField const*					getStaticField(std::string const& fieldName,
															   EFieldFlags minFlags = EFieldFlags::Default,
															   bool shouldInspectInherited = false)			const	noexcept;
			std::vector<StaticField const*>		getStaticFields(std::string const& fieldName,
															   EFieldFlags minFlags = EFieldFlags::Default,
															   bool shouldInspectInherited = false)			const	noexcept;

			template <typename ReturnType, typename... ArgTypes>
			Method const*						getMethod(std::string const& methodName,
														  EMethodFlags minFlags = EMethodFlags::Default,
														  bool shouldInspectParents = false)				const	noexcept;

			/**
			*	Get the first found method named methodName which has at least all the provided flags, nullptr if none if found.
			*	If shouldInspectParents is set to true, the search will be extended to parents structs recursively.
			*/
			Method const*						getMethod(std::string const& methodName,
														  EMethodFlags minFlags = EMethodFlags::Default,
														  bool shouldInspectParents = false)				const	noexcept;
			std::vector<Method const*>			getMethods(std::string const& methodName,
														   EMethodFlags minFlags = EMethodFlags::Default,
														   bool shouldInspectParents = false)				const	noexcept;

			template <typename ReturnType, typename... ArgTypes>
			StaticMethod const*					getStaticMethod(std::string const& methodName,
																EMethodFlags minFlags = EMethodFlags::Default,
																bool shouldInspectParents = false)			const	noexcept;

			/**
			*
			*/
			StaticMethod const*					getStaticMethod(std::string const& methodName,
																EMethodFlags minFlags = EMethodFlags::Default,
																bool shouldInspectParents = false)			const	noexcept;
			std::vector<StaticMethod const*>	getStaticMethods(std::string const& methodName,
																 EMethodFlags minFlags = EMethodFlags::Default,
																 bool shouldInspectParents = false)			const	noexcept;

			/** Make an instance of the class represented by this archetype. */
			template <typename ReturnType = void, typename... ArgTypes>
			ReturnType*	makeInstance(ArgTypes&&... args)													const	noexcept;

			/**
			*	Return true if this type inherits from the provided type, else false.
			*/
			bool		inheritsFrom(Struct const& otherType)												const	noexcept;
			
			/**
			*	Return true if this type is a parent (direct or not) of the provided type, else false.
			*/
			bool		isBaseOf(Struct const& otherType)													const	noexcept;

			/**
			*	Add the type T to this type's parents if possible
			*/
			template <typename T>
			void __RFKaddToParents(EAccessSpecifier inheritanceAccess)			noexcept;

			
			template <typename T>
			void __RFKaddRequiredMethods()										noexcept;

			template <typename ReturnType>
			void __RFKaddCustomInstantiator(StaticMethod const* instantiator)	noexcept;

			void __RFKsetDefaultInstantiationMethod(void*(*func)() noexcept)	noexcept;

			Struct& operator=(Struct const&)	= delete;
			Struct& operator=(Struct&&)			= default;
	};

	#include "TypeInfo/Archetypes/Struct.inl"
}