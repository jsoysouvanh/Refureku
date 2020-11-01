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
			std::string				name		= "";

			/** Program-unique ID given for this entity. */
			uint64					id			= 0u;

			/** Kind of this entity. */
			EEntityKind				kind		= EEntityKind::Undefined;

			/**
			*	The outer entity is the entity in which this entity has been declared.
			*	If this entity is declared at file level, outerEntity will be nullptr.
			*/
			Entity const*			outerEntity	= nullptr;

			/** Properties contained by this entity. */
			std::vector<Property*>	properties;

			Entity()												= delete;
			Entity(std::string&&	name,
				   uint64			id,
				   EEntityKind		kind = EEntityKind::Undefined)	noexcept;
			Entity(Entity const&)									= default;
			Entity(Entity&&)										= default;
			~Entity()												= default;

			/**
			*	@brief	Retrieve a property of a given type from this entity.
			*	
			*	@tparam PropertyType					Type of the property to retrieve. rfk::Property must be a base class of T.
			*	@tparam ConsiderInheritingProperties	Should properties inheriting from PropertyType be considered as valid?
			*	
			*	@return The first found property matching the given PropertyType if any, else nullptr.
			*/
			template <typename PropertyType, typename = std::enable_if_t<std::is_base_of_v<Property, PropertyType>>>
			PropertyType const* getProperty() const noexcept
			{
				static_assert(!std::is_abstract_v<PropertyType>, "Can't get an abstract property.");

				Struct const* queriedPropertyArchetype = &PropertyType::staticGetArchetype();

				//Iterate over all props to find a matching property
				for (Property const* p : properties)
				{
					if (queriedPropertyArchetype == &p->getArchetype())
					{
						return reinterpret_cast<PropertyType const*>(p);
					}
				}

				return nullptr;
			}

			template <typename PropertyType, typename = std::enable_if_t<std::is_base_of_v<Property, PropertyType>>>
			std::vector<PropertyType const*> getProperties() const noexcept
			{
				static_assert(!std::is_abstract_v<PropertyType>, "Can't get an abstract property.");

				std::vector<PropertyType const*> result;

				Struct const* queriedPropertyArchetype = &PropertyType::staticGetArchetype();

				//Iterate over all props to find a matching property
				for (Property const* p : properties)
				{
					if (queriedPropertyArchetype == &p->getArchetype())
					{
						result.emplace_back(reinterpret_cast<PropertyType const*>(p));
					}
				}

				return result;
			}

			Property const* getProperty(bool (*predicate)(Property const*)) const noexcept
			{
				if (predicate != nullptr)
				{
					for (Property const* property : properties)
					{
						if (predicate(property))
						{
							return property;
						}
					}
				}

				return nullptr;
			}

			std::vector<Property const*> getProperties(bool (*predicate)(Property const*)) const noexcept
			{
				std::vector<Property const*> result;

				if (predicate != nullptr)
				{
					for (Property const* property : properties)
					{
						if (predicate(property))
						{
							result.emplace_back(property);
						}
					}
				}

				return result;
			}
	};
}