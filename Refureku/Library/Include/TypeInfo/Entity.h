#pragma once

#include <string>

#include "Misc/FundamentalTypes.h"

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

			/** Name qualifying this entity */
			std::string		name;

			/** Program-unique ID given for this entity */
			uint64			id;

			/** */
			//TODO: Add properties

			Entity()									= delete;
			Entity(std::string&& newName, uint64 newId)	noexcept;
			Entity(Entity const&)						= default;
			Entity(Entity&&)							= default;
			~Entity()									= default;

			Entity& operator=(Entity const&)			= default;
			Entity& operator=(Entity&&)					= default;
	};
}