/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cstddef>	//std::size_t
#include <type_traits>

#include "Refureku/Config.h"
#include "Refureku/Misc/Pimpl.h"
#include "Refureku/Misc/GetPimplMacro.h"
#include "Refureku/TypeInfo/Entity/EEntityKind.h"
#include "Refureku/Properties/Property.h"
#include "Refureku/Misc/Visitor.h"
#include "Refureku/Misc/Predicate.h"
#include "Refureku/Containers/Vector.h"

namespace rfk
{
	//Forward declarations
	class Struct;
	class Algorithm;

	class Entity
	{
		public:
			Entity(Entity const&) = delete;

			/**
			*	@brief	Retrieve the property at the given index.
			*			If propertyIndex is greater or equal to the properties count, the behaviour is undefined.
			* 
			*	@param propertyIndex Index of the property to retrieve in this entity.
			* 
			*	@return The property at the given index.
			*/
			RFK_NODISCARD REFUREKU_API
				Property const*				getPropertyAt(std::size_t propertyIndex)					const	noexcept;

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
			template <typename PropertyType, typename = std::enable_if_t<std::is_base_of_v<Property, PropertyType> && !std::is_same_v<PropertyType, Property>>>
			RFK_NODISCARD
				PropertyType const*			getProperty(bool isChildClassValid = true)					const	noexcept;

			/**
			*	@brief Retrieve the first property matching with the provided archetype.
			*	
			*	@param archetype			Archetype of the property to look for.
			*	@param isChildClassValid	If true, consider properties inheriting from the provided archetype valid.
			*	
			*	@return The first property matching the provided archetype in this entity, nullptr if none is found.
			*/
			RFK_NODISCARD REFUREKU_API
				Property const*				getProperty(Struct const&	archetype,
														bool			isChildClassValid = true)		const	noexcept;

			/**
			*	@brief Retrieve the first property named with the provided name.
			* 
			*	@param name Name of the property to retrieve.
			* 
			*	@return The first property named with the provided name if any, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API
				Property const*				getPropertyByName(char const* name)							const	noexcept;

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
			RFK_NODISCARD REFUREKU_API
				Property const*				getPropertyByPredicate(Predicate<Property>	predicate,
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
			template <typename PropertyType, typename = std::enable_if_t<std::is_base_of_v<Property, PropertyType> && !std::is_same_v<PropertyType, Property>>>
			RFK_NODISCARD
				Vector<PropertyType const*>	getProperties(bool isChildClassValid = true)				const	noexcept;

			/**
			*	@brief Retrieve all properties matching with the provided archetype.
			*	
			*	@param archetype			Archetype of the properties to look for.
			*	@param isChildClassValid	If true, all properties inheriting from the provided archetype will be included in the result.
			*	
			*	@return A collection of all properties matching the provided archetype in this entity.
			*/
			RFK_NODISCARD REFUREKU_API
				Vector<Property const*>		getProperties(Struct const&	archetype,
														  bool			isChildClassValid = true)		const	noexcept;

			/**
			*	@brief Retrieve all properties named with the provided name.
			* 
			*	@param name Name of the properties to retrieve.
			* 
			*	@return A collection of all properties named with the provided name.
			*/
			RFK_NODISCARD REFUREKU_API
				Vector<Property const*>		getPropertiesByName(char const* name)						const	noexcept;

			/**
			*	@brief Retrieve all properties matching with a predicate in this entity.
			*	
			*	@param predicate	Predicate returning true for any matching property.
			*	@param userData		Optional data forwarded to the predicate.
			*	
			*	@return A collection of all properties fulfilling the provided predicate contained in this entity.
			*
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API
				Vector<Property const*>		getPropertiesByPredicate(Predicate<Property>	predicate,
																	 void*					userData)	const;

			/**
			*	@brief Get the number of properties attached to this entity.
			* 
			*	@return The number of properties attached to this entity.
			*/
			RFK_NODISCARD REFUREKU_API
				std::size_t					getPropertiesCount()										const	noexcept;

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
			REFUREKU_API bool				foreachProperty(Visitor<Property>	visitor,
															void*				userData)				const;

			/**
			*	@brief Get the name of the entity.
			* 
			*	@return The name of the entity.
			*/
			RFK_NODISCARD REFUREKU_API
				char const*					getName()													const	noexcept;

			/**
			*	@brief Check that this entity has the same name as the provided string.
			* 
			*	@return true if this entity has the same name as the provided string.
			*			If the provided name is nullptr, return false.
			*/
			RFK_NODISCARD REFUREKU_API
				bool						hasSameName(char const*	name)								const	noexcept;

			/**
			*	@brief Get the program-unique id of the entity.
			* 
			*	@return The program-unique id of the entity.
			*/
			RFK_NODISCARD REFUREKU_API
				std::size_t					getId()														const	noexcept;

			/**
			*	@brief	Get the kind of the entity.
			*			Knowing the kind allows to safely cast to child classes.
			*			Check the EEntityKind documentation for more information.
			* 
			*	@return The kind of the entity.
			*/
			RFK_NODISCARD REFUREKU_API
				EEntityKind					getKind()													const	noexcept;

			/**
			*	@brief	Get the outer entity of the entity.
			*			It basically corresponds to the entity this entity was declared in from a source-code point of view.
			*			A nullptr outer entity means the entity was declared at file level.
			* 
			*	@return The outer entity of the entity.
			*/
			RFK_NODISCARD REFUREKU_API
				Entity const*				getOuterEntity()											const	noexcept;

			/**
			*	@brief Add a property to this entity.
			*	
			*	@param property The property to add.
			*	
			*	@return	true if the property was added,
			*			false if it failed to be added (allow multiple is false and the property is already in the entity for example).
			*/
			REFUREKU_API bool				addProperty(Property const& property)								noexcept;

			/**
			*	@brief Setter for the field _outerEntity.
			* 
			*	@param outerEntity The outer entity to set.
			*/
			REFUREKU_API void				setOuterEntity(Entity const* outerEntity)							noexcept;

			/**
			*	@brief	Set the number of properties for this entity.
			*			Useful to avoid reallocations when adding a lot of properties.
			*			If the number of properties is already >= to the provided capacity, this method has no effect.
			* 
			*	@param capacity The number of properties of this entity.
			*/
			REFUREKU_API void				setPropertiesCapacity(std::size_t capacity)							noexcept;


			Entity&							operator=(Entity const&)		= delete;
			Entity&							operator=(Entity&&)				= delete;

			RFK_NODISCARD REFUREKU_API bool	operator==(Entity const& other)	const	 noexcept;
			RFK_NODISCARD REFUREKU_API bool	operator!=(Entity const& other)	const	 noexcept;

		protected:
			//Forward declaration
			class EntityImpl;

			REFUREKU_INTERNAL Entity(Entity&&)						noexcept;
			REFUREKU_INTERNAL Entity(EntityImpl* implementation)	noexcept;
			REFUREKU_INTERNAL ~Entity()								noexcept;

			RFK_GEN_GET_PIMPL(EntityImpl, _pimpl.get())

		private:
			/** Concrete implementation of the Entity class. */
			Pimpl<EntityImpl> _pimpl;

		friend Algorithm;
	};

	#include "Refureku/TypeInfo/Entity/Entity.inl"
}