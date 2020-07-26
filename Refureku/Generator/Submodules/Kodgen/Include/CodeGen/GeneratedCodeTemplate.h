/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

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
			GeneratedCodeTemplate(GeneratedCodeTemplate const&) = default;
			GeneratedCodeTemplate(GeneratedCodeTemplate&&)		= default;
			virtual ~GeneratedCodeTemplate()					= default;

			/**
			*	@brief Method in which we define what to write in the generated file for this entity.
			*
			*	@param generatedFile	Object used to write in the generated file
			*	@param entityInfo		Structure containing info about the entity. You may static cast this into the derived class you expect
			*/
			virtual void generateCode(GeneratedFile& generatedFile, EntityInfo const& entityInfo) noexcept = 0;
	};
}