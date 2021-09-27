/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <type_traits>

#include "Refureku/TypeInfo/Properties/Property.h"
#include "Refureku/Utility/Pimpl.h"

namespace rfk
{
	class StructAPI;

	class EntityAPI //TODO: Rename in Entity
	{
		private:
			class Implementation;
			
			/** Concrete implementation of the entity class. */
			Pimpl<EntityAPI::Implementation> _pimpl;

		public:
			REFUREKU_API EntityAPI(char const*		name,
								   std::size_t		id,
								   EEntityKind		kind = EEntityKind::Undefined,
								   EntityAPI const*	outerEntity = nullptr)			noexcept;
			EntityAPI(EntityAPI const&)												= default;
			EntityAPI(EntityAPI&&)													= default;

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
			//TODO: Wrap std::vector to remove it from the API
			//template <typename PropertyType, typename = std::enable_if_t<std::is_base_of_v<Property, PropertyType>>>
			//std::vector<PropertyType const*>	getProperties(bool isChildClassValid = true)	const	noexcept;

			/**
			*	@brief Retrieve all properties matching with a predicate in this entity.
			*	
			*	@param predicate Predicate returning true for any matching property.
			*	
			*	@return A collection of all properties fulfilling the provided predicate contained in this entity.
			*/
			//TODO: Wrap std::vector to remove it from the API
			//template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Property const*>>>
			//std::vector<Property const*>		getProperties(Predicate predicate)				const;

			/**
			*	@brief Retrieve the property at the given index.
			* 
			*	@param propertyIndex Index of the property to retrieve in this entity.
			* 
			*	@return The property at the given index.
			* 
			*	@exception std::out_of_range if the provided index is greater or equal to the number of properties in this entity.
			*/
			REFUREKU_API Property const*						getProperty(std::size_t propertyIndex)						const;

			/**
			*	@brief Retrieve the first property matching with the provided archetype.
			*	
			*	@param archetype			Archetype of the property to look for.
			*	@param isChildClassValid	If true, all properties inheriting from the provided archetype are considered valid.
			*	
			*	@return The first property matching the provided archetype in this entity, nullptr if none is found.
			*/
			REFUREKU_API Property const*						getProperty(StructAPI const&	archetype,
																			bool				isChildClassValid = true)	const	noexcept;

			/**
			*	@brief Retrieve all properties matching with the provided archetype.
			*	
			*	@param archetype			Archetype of the properties to look for.
			*	@param isChildClassValid	If true, all properties inheriting from the provided archetype are considered valid.
			*	
			*	@return A collection of all properties matching the provided archetype in this entity.
			*/
			//TODO: Wrap std::vector to remove it from the API
			//REFUREKU_API std::vector<Property const*>			getProperties(StructAPI const&	archetype,
			//																  bool				isChildClassValid = true)	const	noexcept;

			/**
			*	@brief Get the number of properties attached to this entity.
			* 
			*	@return The number of properties attached to this entity.
			*/
			REFUREKU_API std::size_t							getPropertyCount()											const	noexcept;

			/**
			*	@brief Add a property to this entity.
			*	
			*	@param property The property to add.
			*	
			*	@return	true if the property was added,
			*			false if it failed to be added (allow multiple is false and the property is already in the entity for example).
			*/
			REFUREKU_API bool									addProperty(Property const* property)								noexcept;

			/**
			*	@brief Inherit from another entity inheritable properties.
			*	
			*	@param from The entity this entity should inherit the properties from.
			*/
			REFUREKU_API void									inheritProperties(EntityAPI const& from)							noexcept;

			/**
			*	@brief Inherit all properties from another entity.
			* 
			*	@param from The entity this entity should inherit the properties from.
			*/
			REFUREKU_API void									inheritAllProperties(EntityAPI const& from)							noexcept;

			/**
			*	@brief Getter for the field _name.
			* 
			*	@return _name.
			*/
			REFUREKU_API char const*							getName()													const	noexcept;

			/**
			*	@brief Getter for the field _id.
			* 
			*	@return _id.
			*/
			REFUREKU_API std::size_t							getId()														const	noexcept;

			/**
			*	@brief Getter for the field _kind.
			* 
			*	@return _kind.
			*/
			REFUREKU_API EEntityKind							getKind()													const	noexcept;

			/**
			*	@brief Getter for the field _outerEntity.
			* 
			*	@return _outerEntity.
			*/
			REFUREKU_API EntityAPI const*						getOuterEntity()											const	noexcept;

			/**
			*	@brief Setter for the field _outerEntity.
			* 
			*	@param The outer entity to set.
			*/
			REFUREKU_API void									setOuterEntity(EntityAPI const*)									noexcept;

			/**
			*	@brief	Set the number of properties for this entity.
			*			Useful to avoid reallocations when adding a lot of properties.
			*			If the number of properties is already >= to the provided capacity, this method has no effect.
			* 
			*	@param propertiesCapacity The number of properties of this entity.
			*/
			REFUREKU_API void									setPropertiesCapacity(std::size_t propertiesCapacity)				noexcept;


			inline bool operator==(EntityAPI const& other) const noexcept;
			inline bool operator!=(EntityAPI const& other) const noexcept;
	};
}