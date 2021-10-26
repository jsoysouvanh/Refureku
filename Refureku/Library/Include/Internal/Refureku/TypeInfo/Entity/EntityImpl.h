/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cstddef>	//std::size_t
#include <string>
#include <vector>

#include "Refureku/TypeInfo/Entity/Entity.h"
#include "Refureku/TypeInfo/Entity/EEntityKind.h"
#include "Refureku/Properties/Property.h"

namespace rfk
{
	class Entity::EntityImpl
	{
		private:
			/** Name qualifying this entity. */
			std::string						_name;

			/** Properties attached to this entity. */
			std::vector<Property const*>	_properties;

			/** Program-unique ID given for this entity. The ID is persistent even after the program is recompiled / relaunched. */
			std::size_t						_id;

			/**
			*	The outer entity is the entity in which this entity has been declared.
			*	If this entity is declared at file level, outerEntity will be nullptr.
			*/
			Entity const*					_outerEntity;

			/** Kind of this entity. */
			EEntityKind						_kind;

		public:
			inline EntityImpl(char const*		name,
							  std::size_t		id,
							  EEntityKind		kind = EEntityKind::Undefined,
							  Entity const*	outerEntity = nullptr)			noexcept;
			virtual ~EntityImpl()												= default;

			/**
			*	@brief Add a property to this entity.
			*	
			*	@param property The property to add.
			*	
			*	@return	true if the property was added,
			*			false if it failed to be added (for example, AllowMultiple is false and a property of the same kind is already in the entity).
			*/
			inline bool									addProperty(Property const* property)					noexcept;

			/**
			*	@brief Inherit from another entity inheritable properties.
			*	
			*	@param from The entity this entity should inherit the properties from.
			*/
			inline void									inheritProperties(EntityImpl const& from)				noexcept;

			/**
			*	@brief Inherit all properties from another entity.
			* 
			*	@param from The entity this entity should inherit the properties from.
			*/
			inline void									inheritAllProperties(EntityImpl const& from)			noexcept;

			/**
			*	@brief Getter for the field _name.
			* 
			*	@return _name.
			*/
			inline std::string const&					getName()										const	noexcept;

			/**
			*	@brief Getter for the field _id.
			* 
			*	@return _id.
			*/
			inline std::size_t							getId()											const	noexcept;

			/**
			*	@brief Getter for the field _kind.
			* 
			*	@return _kind.
			*/
			inline EEntityKind							getKind()										const	noexcept;

			/**
			*	@brief Getter for the field _outerEntity.
			* 
			*	@return _outerEntity.
			*/
			inline Entity const*						getOuterEntity()								const	noexcept;

			/**
			*	@brief Getter for the field _properties.
			* 
			*	@return _properties.
			*/
			inline std::vector<Property const*> const&	getProperties()									const	noexcept;

			/**
			*	@brief Setter for the field _outerEntity.
			* 
			*	@param outerEntity The outer entity to set.
			*/
			inline void									setOuterEntity(Entity const* outerEntity)				noexcept;

			/**
			*	@brief	Set the number of properties for this entity.
			*			Useful to avoid reallocations when adding a lot of properties.
			*			If the number of properties is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of properties of this entity.
			*/
			inline void									setPropertiesCapacity(std::size_t capacity)				noexcept;
	};

	#include "Refureku/TypeInfo/Entity/EntityImpl.inl"
}