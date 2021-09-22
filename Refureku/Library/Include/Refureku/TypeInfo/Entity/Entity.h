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
	//Forward declaration
	class Struct;

	class Entity
	{
		private:
			/** Name qualifying this entity. */
			std::string						_name			= "";

			/** Program-unique ID given for this entity. The ID is persistent even after the program is recompiled / relaunched. */
			std::size_t						_id				= 0u;

			/** Kind of this entity. */
			EEntityKind						_kind			= EEntityKind::Undefined;

			/**
			*	The outer entity is the entity in which this entity has been declared.
			*	If this entity is declared at file level, outerEntity will be nullptr.
			*/
			Entity const*					_outerEntity	= nullptr;

			/** Properties attached to this entity. */
			std::vector<Property const*>	_properties;

		public:
			/** Helper structs for hashing / equal */
			struct NameHasher
			{
				size_t operator()(rfk::Entity const& entity) const
				{
					return std::hash<std::string>()(entity.getName());
				}
			};

			struct IdHasher
			{
				size_t operator()(rfk::Entity const& entity) const
				{
					return entity.getId();
				}
			};

			struct EqualName
			{
				bool operator()(rfk::Entity const& e1, rfk::Entity const& e2) const
				{
					return e1.getName() == e2.getName();
				}
			};

			struct EqualId
			{
				bool operator()(rfk::Entity const& e1, rfk::Entity const& e2) const
				{
					return e1.getId() == e2.getId();
				}
			};

			struct PtrNameHasher
			{
				size_t operator()(rfk::Entity const* entity) const
				{
					return std::hash<std::string>()(entity->getName());
				}
			};

			struct PtrIdHasher
			{
				size_t operator()(rfk::Entity const* entity) const
				{
					return entity->getId();
				}
			};

			struct PtrEqualName
			{
				bool operator()(rfk::Entity const* e1, rfk::Entity const* e2) const
				{
					return e1->getName() == e2->getName();
				}
			};

			struct PtrEqualId
			{
				bool operator()(rfk::Entity const* e1, rfk::Entity const* e2) const
				{
					return e1->getId() == e2->getId();
				}
			};

			REFUREKU_API Entity(std::string&&	name,
								std::size_t		id,
								EEntityKind		kind = EEntityKind::Undefined,
								Entity const*	outerEntity = nullptr)			noexcept;
			Entity(Entity const&)												= default;
			Entity(Entity&&)													= default;

			/**
			*	@brief	Retrieve a property of a given type from this entity.
			*			The provided property type must be non-abstract.
			*	
			*	@tparam PropertyType Type of the property to retrieve. It must be a child class of rfk::Property.
			* 
			*	@param isChildClassValid Whether types inheriting from the provided PropertyType are considered valid or not.
			*	
			*	@return The first found property of type PropertyType if any, else nullptr.
			*/
			template <typename PropertyType, typename = std::enable_if_t<std::is_base_of_v<Property, PropertyType>>>
			PropertyType const*					getProperty(bool isChildClassValid = true)		const	noexcept;

			/**
			*	@brief Retrieve a property matching with a predicate.
			*	
			*	@param predicate Predicate returning true for any matching property.
			*	
			*	@return The first found property fulfilling the provided predicate if any, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Property const*>>>
			Property const*						getProperty(Predicate predicate)				const;

			/**
			*	@brief	Retrieve properties of a given type from this entity.
			*			The provided property type must be non-abstract.
			*	
			*	@tparam PropertyType Type of the property to retrieve. It must be a child class of rfk::Property.
			*	
			*	@return A collection of all properties of type PropertyType contained in this entity.
			*/
			template <typename PropertyType, typename = std::enable_if_t<std::is_base_of_v<Property, PropertyType>>>
			std::vector<PropertyType const*>	getProperties(bool isChildClassValid = true)	const	noexcept;

			/**
			*	@brief Retrieve all properties matching with a predicate in this entity.
			*	
			*	@param predicate Predicate returning true for any matching property.
			*	
			*	@return A collection of all properties fulfilling the provided predicate contained in this entity.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Property const*>>>
			std::vector<Property const*>		getProperties(Predicate predicate)				const;

			/**
			*	@brief Retrieve the property at the given index.
			* 
			*	@param propertyIndex Index of the property to retrieve in this entity.
			* 
			*	@return The property at the given index.
			* 
			*	@exception std::out_of_range if the provided index is greater or equal to the number of properties in this entity.
			*/
			REFUREKU_API Property const*						getProperty(std::size_t propertyIndex)					const;

			/**
			*	@brief Retrieve the first property matching with the provided archetype.
			*	
			*	@param archetype			Archetype of the property to look for.
			*	@param isChildClassValid	If true, all properties inheriting from the provided archetype are considered valid.
			*	
			*	@return The first property matching the provided archetype in this entity, nullptr if none is found.
			*/
			REFUREKU_API Property const*						getProperty(Struct const&	archetype,
																			bool			isChildClassValid = true)	const	noexcept;

			/**
			*	@brief Retrieve all properties matching with the provided archetype.
			*	
			*	@param archetype			Archetype of the properties to look for.
			*	@param isChildClassValid	If true, all properties inheriting from the provided archetype are considered valid.
			*	
			*	@return A collection of all properties matching the provided archetype in this entity.
			*/
			REFUREKU_API std::vector<Property const*>			getProperties(Struct const&	archetype,
																			  bool			isChildClassValid = true)	const	noexcept;

			/**
			*	@brief Get the number of properties attached to this entity.
			* 
			*	@return The number of properties attached to this entity.
			*/
			REFUREKU_API std::size_t							getPropertyCount()										const	noexcept;

			/**
			*	@brief Add a property to this entity.
			*	
			*	@param property The property to add.
			*	
			*	@return	true if the property was added,
			*			false if it failed to be added (allow multiple is false and the property is already in the entity for example).
			*/
			REFUREKU_API bool									addProperty(Property const* property)							noexcept;

			/**
			*	@brief Inherit from another entity inheritable properties.
			*	
			*	@param from The entity this entity should inherit the properties from.
			*/
			REFUREKU_API void									inheritProperties(Entity const& from)							noexcept;

			/**
			*	@brief Inherit all properties from another entity.
			* 
			*	@param from The entity this entity should inherit the properties from.
			*/
			REFUREKU_API void									inheritAllProperties(Entity const& from)						noexcept;

			/**
			*	@brief Getter for the field _name.
			* 
			*	@return _name.
			*/
			REFUREKU_API std::string const&						getName()												const	noexcept;

			/**
			*	@brief Getter for the field _id.
			* 
			*	@return _id.
			*/
			REFUREKU_API std::size_t							getId()													const	noexcept;

			/**
			*	@brief Getter for the field _kind.
			* 
			*	@return _kind.
			*/
			REFUREKU_API EEntityKind							getKind()												const	noexcept;

			/**
			*	@brief Getter for the field _outerEntity.
			* 
			*	@return _outerEntity.
			*/
			REFUREKU_API Entity const*							getOuterEntity()										const	noexcept;

			/**
			*	@brief Setter for the field _outerEntity.
			* 
			*	@param The outer entity to set.
			*/
			REFUREKU_API void									setOuterEntity(Entity const*)									noexcept;

			/**
			*	@brief	Set the number of properties for this entity.
			*			Useful to avoid reallocations when adding a lot of properties.
			*			If the number of properties is already >= to the provided count, this method has no effect.
			* 
			*	@param propertiesCapacity The number of properties of this entity.
			*/
			REFUREKU_API void									setPropertiesCapacity(std::size_t propertiesCapacity)			noexcept;


			inline bool operator==(Entity const& other) const noexcept;
			inline bool operator!=(Entity const& other) const noexcept;
	};

	#include "Refureku/TypeInfo/Entity/Entity.inl"
}