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

namespace rfk
{
	class StructAPI;
	class Property;

	/**
	*	@brief Predicate defining if a property is valid or not.
	* 
	*	@param prop		The tested property.
	*	@param userData	Data received from the user.
	*/
	using PropertyPredicate = bool (*)(Property const& prop, void* userData);

	class EntityAPI //TODO: Rename in Entity
	{
		public:
			//TODO: Delete this since it will never be used in real situations (just for tests)
			REFUREKU_API EntityAPI(char const*		name,
								   std::size_t		id,
								   EEntityKind		kind = EEntityKind::Undefined,
								   EntityAPI const*	outerEntity = nullptr)			noexcept;
			EntityAPI(EntityAPI const&)												noexcept;
			EntityAPI(EntityAPI&&)													noexcept;
			REFUREKU_API ~EntityAPI()												noexcept;	//TODO: Maybe move this to protected as well

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
			*	@brief	Retrieve the property at the given index.
			*			If propertyIndex is greater or equal to the properties count, the behaviour is undefined.
			* 
			*	@param propertyIndex Index of the property to retrieve in this entity.
			* 
			*	@return The property at the given index.
			*/
			REFUREKU_API Property const*						getPropertyAt(std::size_t propertyIndex)					const	noexcept;

			/**
			*	@brief Retrieve the first property matching with the provided archetype.
			*	
			*	@param archetype			Archetype of the property to look for.
			*	@param isChildClassValid	If true, consider properties inheriting from the provided archetype valid.
			*	
			*	@return The first property matching the provided archetype in this entity, nullptr if none is found.
			*/
			REFUREKU_API Property const*						getProperty(StructAPI const&	archetype,
																			bool				isChildClassValid = true)	const	noexcept;

			/**
			*	@brief Retrieve a property matching with a predicate.
			*	
			*	@param predicate	Predicate returning true for any matching property.
			*	@param userData		Optional data forwarded to the predicate.
			*	
			*	@return The first found property fulfilling the provided predicate if any, else nullptr.
			*/
			REFUREKU_API Property const*						getProperty(PropertyPredicate	predicate,
																			void*				userData = nullptr)			const	noexcept;

			/**
			*	@brief Retrieve all properties matching with the provided archetype.
			*	
			*	@param archetype			Archetype of the properties to look for.
			*	@param isChildClassValid	If true, all properties inheriting from the provided archetype will be included in the result.
			*	
			*	@return A collection of all properties matching the provided archetype in this entity.
			*/
			REFUREKU_API Vector<Property const*>				getProperties(StructAPI const&	archetype,
																			  bool				isChildClassValid = true)	const	noexcept;

			/**
			*	@brief Retrieve all properties matching with a predicate in this entity.
			*	
			*	@param predicate	Predicate returning true for any matching property.
			*	@param userData		Optional data forwarded to the predicate.
			*	
			*	@return A collection of all properties fulfilling the provided predicate contained in this entity.
			*/
			REFUREKU_API Vector<Property const*>				getProperties(PropertyPredicate	predicate,
																			  void*				userData = nullptr)			const	noexcept;

			/**
			*	@brief Get the number of properties attached to this entity.
			* 
			*	@return The number of properties attached to this entity.
			*/
			REFUREKU_API std::size_t							getPropertyCount()											const	noexcept;

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
			*	@param outerEntity The outer entity to set.
			*/
			REFUREKU_API void									setOuterEntity(EntityAPI const* outerEntity)						noexcept;

			/**
			*	@brief	Set the number of properties for this entity.
			*			Useful to avoid reallocations when adding a lot of properties.
			*			If the number of properties is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of properties of this entity.
			*/
			REFUREKU_API void									setPropertiesCapacity(std::size_t capacity)							noexcept;


			REFUREKU_API bool	operator==(EntityAPI const& other)	const	 noexcept;
			REFUREKU_API bool	operator!=(EntityAPI const& other)	const	 noexcept;

		protected:
			//Forward declaration
			class EntityImpl;

			EntityAPI()	noexcept;

			/**
			*	@brief Set the underlying implementation to the provided implementation.
			*
			*	@param implementation The implementation pointer to use.
			*/
			void setImpl(EntityImpl* implementation) noexcept;

		private:
			/** Concrete implementation of the entity class. */
			Pimpl<EntityImpl> _pimpl;
	};
}