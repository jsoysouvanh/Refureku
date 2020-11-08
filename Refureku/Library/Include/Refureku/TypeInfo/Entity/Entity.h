/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <vector>
#include <type_traits>

#include "Refureku/Config.h"
#include "Refureku/Misc/FundamentalTypes.h"
#include "Refureku/TypeInfo/Entity/EEntityKind.h"
#include "Refureku/TypeInfo/Properties/Property.h"

namespace rfk
{
	class Entity
	{
		public:
			/** Helper structs for hashing / equal */
			struct NameHasher
			{
				size_t operator()(rfk::Entity const& entity) const
				{
					return std::hash<std::string>()(entity.name);
				}
			};

			struct IdHasher
			{
				size_t operator()(rfk::Entity const& entity) const
				{
					return entity.id;
				}
			};

			struct EqualName
			{
				bool operator()(rfk::Entity const& e1, rfk::Entity const& e2) const
				{
					return e1.name == e2.name;
				}
			};

			struct EqualId
			{
				bool operator()(rfk::Entity const& e1, rfk::Entity const& e2) const
				{
					return e1.id == e2.id;
				}
			};

			struct PtrNameHasher
			{
				size_t operator()(rfk::Entity const* entity) const
				{
					return std::hash<std::string>()(entity->name);
				}
			};

			struct PtrIdHasher
			{
				size_t operator()(rfk::Entity const* entity) const
				{
					return entity->id;
				}
			};

			struct PtrEqualName
			{
				bool operator()(rfk::Entity const* e1, rfk::Entity const* e2) const
				{
					return e1->name == e2->name;
				}
			};

			struct PtrEqualId
			{
				bool operator()(rfk::Entity const* e1, rfk::Entity const* e2) const
				{
					return e1->id == e2->id;
				}
			};

			/** Name qualifying this entity. */
			std::string						name		= "";

			/** Program-unique ID given for this entity. */
			uint64							id			= 0u;

			/** Kind of this entity. */
			EEntityKind						kind		= EEntityKind::Undefined;

			/**
			*	The outer entity is the entity in which this entity has been declared.
			*	If this entity is declared at file level, outerEntity will be nullptr.
			*/
			Entity const*					outerEntity	= nullptr;

			/** Properties contained by this entity. */
			std::vector<Property const*>	properties;

			Entity()												= delete;
			Entity(std::string&&	name,
				   uint64			id,
				   EEntityKind		kind = EEntityKind::Undefined)	noexcept;
			Entity(Entity const&)									= default;
			Entity(Entity&&)										= default;
			~Entity()												= default;

			/**
			*	@brief	Retrieve a property of a given type from this entity.
			*			The provided property type must be non-abstract.
			*	
			*	@tparam PropertyType Type of the property to retrieve. It must be a child class of rfk::Property.
			*	
			*	@return The first found property of type PropertyType if any, else nullptr.
			*/
			template <typename PropertyType, typename = std::enable_if_t<std::is_base_of_v<Property, PropertyType>>>
			PropertyType const*					getProperty()						const	noexcept;

			/**
			*	@brief Retrieve a property matching with a predicate.
			*	
			*	@param predicate Condition that the searched property must fulfill.
			*	
			*	@return The first found property fulfilling the provided predicate if any, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Property const*>>>
			Property const*						getProperty(Predicate predicate)	const;

			/**
			*	@brief	Retrieve properties of a given type from this entity.
			*			The provided property type must be non-abstract.
			*	
			*	@tparam PropertyType Type of the property to retrieve. It must be a child class of rfk::Property.
			*	
			*	@return A collection of all properties of type PropertyType contained in this entity.
			*/
			template <typename PropertyType, typename = std::enable_if_t<std::is_base_of_v<Property, PropertyType>>>
			std::vector<PropertyType const*>	getProperties()						const	noexcept;

			/**
			*	@brief Retrieve all properties matching with a predicate in this entity.
			*	
			*	@param predicate Condition that the searched properties must fulfill.
			*	
			*	@return A collection of all properties fulfilling the provided predicate contained in this entity.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Property const*>>>
			std::vector<Property const*>		getProperties(Predicate predicate)	const;

			/**
			*	@brief Add a property to this entity.
			*	
			*	@param property The property to add.
			*	
			*	@return	true if the property was added,
			*			false if it failed to be added (allow multiple is false and the property is already in the entity for example).
			*/
			bool								addProperty(Property const* property)		noexcept;

			/**
			*	@brief Inherit from another entity inheritable properties.
			*	
			*	@param from The entity this entity should inherit the properties from.
			*/
			void								inheritProperties(Entity const& from)		noexcept;

			inline bool operator==(Entity const& other) const noexcept;
			inline bool operator!=(Entity const& other) const noexcept;
	};

	#include "Refureku/TypeInfo/Entity/Entity.inl"
}