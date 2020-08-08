/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <unordered_map>

#include "Refureku/Config.h"
#include "Refureku/Misc/FundamentalTypes.h"
#include "Refureku/TypeInfo/Properties/PropertyGroup.h"

namespace rfk
{
	class Entity
	{
		public:
			/**
			*	Describe the kind of an entity
			*/
			enum class EKind : uint8
			{
				/** This entity is... what? Should never happen... */
				Undefined	= 0u,

				/** The entity is a namespace, it can safely be cast to Namespace type. */
				Namespace	= 1 << 0,
				
				/**
				*	The entity is an archetype, it can safely be cast to Archetype type.
				*	More specific info can be retrieved from the entity by checking Archetype::category variable.
				*/
				Archetype	= 1 << 1,

				/**
				*	The entity is a field, it can safely be cast to FieldBase type.
				*	More specific info can be retrieved from the entity by checking FieldBase::flags.
				*/
				Field		= 1 << 2,

				/**
				*	The entity is a method, it can safely be cast to MethodBase type.
				*	More specific info can be retrieved from the entity by checking MethodBase::flags.
				*/
				Method		= 1 << 3,

				/** The entity is an enum value, it can safely be cast to EnumValue. */
				EnumValue	= 1 << 4
			};

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

			/** Name qualifying this entity */
			std::string		name		= "";

			/** Program-unique ID given for this entity */
			uint64			id			= 0u;

			/** Kind of this entity */
			EKind			kind		= EKind::Undefined;

			/**
			*	The outer entity is the entity in which this entity has been declared.
			*	If this entity is declared at file level, outerEntity will be nullptr.
			*/
			Entity const*	outerEntity	= nullptr;

			/** Properties contained by this entity */
			PropertyGroup	properties;

			Entity()																		= delete;
			Entity(std::string&& newName, uint64 newId, EKind newKind = EKind::Undefined)	noexcept;
			Entity(Entity const&)															= default;
			Entity(Entity&&)																= default;
			~Entity()																		= default;
	};
}