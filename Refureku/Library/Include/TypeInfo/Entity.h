#pragma once

#include <string>

#include "Misc/FundamentalTypes.h"

namespace refureku
{
	class Entity
	{
		public:
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