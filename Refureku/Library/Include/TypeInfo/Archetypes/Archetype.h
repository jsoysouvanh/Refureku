#pragma once

#include "TypeInfo/Entity.h"

namespace rfk
{
	class Archetype : public Entity
	{
		protected:
			/** Pointer to the default method used to make an instance of this archetype */
			void* (*_defaultInstantiator)()	noexcept = nullptr;

		public:
			enum class ECategory : uint8
			{
				Class	= 0,
				Struct,
				Enum,
				Fundamental,
				Undefined,

				Count
			};

			/** Category of this type */
			ECategory	category	= ECategory::Undefined;

			/** Size in bytes an instance of this archetype takes in memory, basically what sizeof(Type) returns */
			uint64		memorySize	= 0;

			Archetype(std::string&& newName,
					  uint64		newId			= 0u,
					  ECategory		newCategory		= ECategory::Undefined,
					  uint64		newMemorySize	= 0u)					noexcept;
			Archetype(Archetype const&)										= delete;
			Archetype(Archetype&&)											= default;
			~Archetype()													= default;

			/** Make an instance of the class represented by this archetype. */
			template <typename ReturnType = void, typename... ArgTypes>
			ReturnType* makeInstance(ArgTypes&&... args)				const	noexcept;

			/** Internal use */
			template <typename T>
			void __RFKaddRequiredMethods()										noexcept;

			void __RFKsetDefaultInstantiationMethod(void*(*func)() noexcept)	noexcept;

			Archetype& operator=(Archetype const&)	= delete;
			Archetype& operator=(Archetype&&)		= default;
	};

	#include "TypeInfo/Archetypes/Archetype.inl"
}