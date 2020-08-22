/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "Kodgen/InfoStructures/EntityInfo.h"
#include "Kodgen/CodeGen/GeneratedFile.h"

namespace kodgen
{
	//Forward declaration
	class FileGenerationUnit;

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
			*	@param generatedFile		Object used to write in the generated file.
			*	@param entityInfo			Structure containing info about the entity. You may static cast this into the derived class you expect.
			*	@param generationUnit		FileGenerationUnit generating this entity.
			*	@param out_errorDescription	If any error occurs, out_errorMessage must be filled with the error description.
			*/
			virtual void generateCode(GeneratedFile&		generatedFile,
									  EntityInfo const&		entityInfo,
									  FileGenerationUnit&	generationUnit,
									  std::string&			out_errorDescription)	const noexcept = 0;
	};
}