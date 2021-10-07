/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <cstddef>	//std::size_t

#include "Refureku/Config.h"
#include "Refureku/Utility/Pimpl.h"
#include "Refureku/TypeInfo/Entity/EEntityKind.h"
#include "Refureku/Containers/Vector.h"
#include "Refureku/Misc/Visitor.h"
#include "Refureku/Misc/Predicate.h"

namespace rfk
{
	class Struct;
	class Property;
	class EntityUtility;

	class Entity //TODO: Rename in Entity
	{
		public:
			Entity(Entity const&)	= delete;

			/**
			*	@brief	Retrieve the property at the given index.
			*			If propertyIndex is greater or equal to the properties count, the behaviour is undefined.
			* 
			*	@param propertyIndex Index of the property to retrieve in this entity.
			* 
			*	@return The property at the given index.
			*/
			RFK_NODISCARD REFUREKU_API Property const*			getPropertyAt(std::size_t propertyIndex)					const	noexcept;

			/**
			*	@brief	Retrieve a property of a given type from this entity.
			*	
			*	@tparam PropertyType Type of the property to retrieve. It must inherit from rfk::Property.
			*			If PropertyType uses multiple inheritance, its first inherited type must be rfk::Property or derived.
			* 
			*	@param isChildClassValid If true, consider properties inheriting from the provided property type valid.
			*	
			*	@return The first found property of type PropertyType if any, else nullptr.
			*/
			template <typename PropertyType>
			RFK_NODISCARD PropertyType const*					getProperty(bool isChildClassValid = true)					const	noexcept;

			/**
			*	@brief Retrieve the first property matching with the provided archetype.
			*	
			*	@param archetype			Archetype of the property to look for.
			*	@param isChildClassValid	If true, consider properties inheriting from the provided archetype valid.
			*	
			*	@return The first property matching the provided archetype in this entity, nullptr if none is found.
			*/
			RFK_NODISCARD REFUREKU_API Property const*			getProperty(Struct const& archetype,
																			bool			 isChildClassValid = true)		const	noexcept;

			/**
			*	@brief Retrieve a property matching with a predicate.
			*	
			*	@param predicate	Predicate returning true for any matching property.
			*	@param userData		Optional data forwarded to the predicate.
			*	
			*	@return The first found property fulfilling the provided predicate if any, else nullptr.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API Property const*			getPropertyByPredicate(Predicate<Property>	predicate,
																					   void*				userData)		const;

			/**
			*	@brief	Retrieve all properties matching with the provided archetype.
			*			If PropertyType uses multiple inheritance, its first inherited type must be rfk::Property or derived.
			*	
			*	@tparam PropertyType Type of the properties to retrieve. It must inherit from rfk::Property.
			* 
			*	@param isChildClassValid If true, consider properties inheriting from the provided property type valid.
			*	
			*	@return A collection of all properties matching the provided property type in this entity.
			*/
			template <typename PropertyType>
			RFK_NODISCARD Vector<PropertyType const*>			getProperties(bool isChildClassValid = true)				const	noexcept;

			/**
			*	@brief Retrieve all properties matching with the provided archetype.
			*	
			*	@param archetype			Archetype of the properties to look for.
			*	@param isChildClassValid	If true, all properties inheriting from the provided archetype will be included in the result.
			*	
			*	@return A collection of all properties matching the provided archetype in this entity.
			*/
			RFK_NODISCARD REFUREKU_API Vector<Property const*>	getProperties(Struct const&	archetype,
																			  bool				isChildClassValid = true)	const	noexcept;

			/**
			*	@brief Retrieve all properties matching with a predicate in this entity.
			*	
			*	@param predicate	Predicate returning true for any matching property.
			*	@param userData		Optional data forwarded to the predicate.
			*	
			*	@return A collection of all properties fulfilling the provided predicate contained in this entity.
			*/
			RFK_NODISCARD REFUREKU_API Vector<Property const*>	getPropertiesByPredicate(Predicate<Property>	predicate,
																						 void*					userData)	const;

			/**
			*	@brief Get the number of properties attached to this entity.
			* 
			*	@return The number of properties attached to this entity.
			*/
			RFK_NODISCARD REFUREKU_API std::size_t				getPropertiesCount()										const	noexcept;

			/**
			*	@brief Execute the given visitor on all properties attached to this entity.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool									foreachProperty(Visitor<Property>	visitor,
																				void*				userData)				const;

			/**
			*	@brief Getter for the field _name.
			* 
			*	@return _name.
			*/
			RFK_NODISCARD REFUREKU_API char const*				getName()													const	noexcept;

			/**
			*	@brief Getter for the field _id.
			* 
			*	@return _id.
			*/
			RFK_NODISCARD REFUREKU_API std::size_t				getId()														const	noexcept;

			/**
			*	@brief Getter for the field _kind.
			* 
			*	@return _kind.
			*/
			RFK_NODISCARD REFUREKU_API EEntityKind				getKind()													const	noexcept;

			/**
			*	@brief Getter for the field _outerEntity.
			* 
			*	@return _outerEntity.
			*/
			RFK_NODISCARD REFUREKU_API Entity const*			getOuterEntity()											const	noexcept;

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
			REFUREKU_API void									inheritProperties(Entity const& from)							noexcept;

			/**
			*	@brief Inherit all properties from another entity.
			* 
			*	@param from The entity this entity should inherit the properties from.
			*/
			REFUREKU_API void									inheritAllProperties(Entity const& from)							noexcept;

			/**
			*	@brief Setter for the field _outerEntity.
			* 
			*	@param outerEntity The outer entity to set.
			*/
			REFUREKU_API void									setOuterEntity(Entity const* outerEntity)						noexcept;

			/**
			*	@brief	Set the number of properties for this entity.
			*			Useful to avoid reallocations when adding a lot of properties.
			*			If the number of properties is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of properties of this entity.
			*/
			REFUREKU_API void									setPropertiesCapacity(std::size_t capacity)							noexcept;


			Entity&						operator=(Entity const&)			= delete;
			Entity&						operator=(Entity&&)				= delete;

			RFK_NODISCARD REFUREKU_API bool	operator==(Entity const& other)	const	 noexcept;
			RFK_NODISCARD REFUREKU_API bool	operator!=(Entity const& other)	const	 noexcept;

		protected:
			//Forward declaration
			class EntityImpl;

			REFUREKU_INTERNAL Entity(Entity&&)				noexcept;
			REFUREKU_INTERNAL Entity(EntityImpl* implementation)	noexcept;
			REFUREKU_INTERNAL ~Entity()							noexcept;

			/**
			*	@brief Get the _pimpl internal pointer.
			* 
			*	@return The _pimpl internal pointer.
			*/
			RFK_NODISCARD REFUREKU_INTERNAL EntityImpl*			getPimpl()			noexcept;
			RFK_NODISCARD REFUREKU_INTERNAL EntityImpl const*	getPimpl()	const	noexcept;

		private:
			/** Concrete implementation of the Entity class. */
			Pimpl<EntityImpl> _pimpl;

		friend EntityUtility;
	};

	#include "Refureku/TypeInfo/Entity/Entity.inl"
}