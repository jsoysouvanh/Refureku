#pragma once

#include <fstream>

#include "Misc/Filesystem.h"
#include "InfoStructures/EntityInfo.h"
#include "CodeGen/GeneratedFile.h"

namespace kodgen
{
	class GeneratedCodeTemplate
	{
		public:
			GeneratedCodeTemplate()								= default;
			GeneratedCodeTemplate(GeneratedCodeTemplate const&) = delete;
			GeneratedCodeTemplate(GeneratedCodeTemplate&&)		= delete;
			virtual ~GeneratedCodeTemplate()					= default;

			/**
			*	@brief Method in which we define what to write in the generated file for this entity.
			*
			*	@param generatedFile Object used to write in the generated file
			*	@param entityInfo Structure containing info about the entity. You may static cast this into the derived class you expect
			*/
			virtual void generateCode(GeneratedFile& generatedFile, EntityInfo const& entityInfo) const noexcept = 0;
	};
}