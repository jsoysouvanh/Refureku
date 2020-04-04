#pragma once

namespace rfk
{
	class Archetype;	//Forward declaration

	class ArchetypeRegisterer
	{
		public:
			ArchetypeRegisterer()							= delete;
			ArchetypeRegisterer(Archetype const* archetype)	noexcept;
			ArchetypeRegisterer(ArchetypeRegisterer const&)	= delete;
			ArchetypeRegisterer(ArchetypeRegisterer&&)		= delete;
			~ArchetypeRegisterer()							= default;

			ArchetypeRegisterer& operator=(ArchetypeRegisterer const&)	= delete;
			ArchetypeRegisterer& operator=(ArchetypeRegisterer&&)		= delete;
	};
}