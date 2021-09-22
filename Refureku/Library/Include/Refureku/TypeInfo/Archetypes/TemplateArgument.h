/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/Archetypes/TemplateParameter.h"

namespace rfk
{
	//Forward declaration
	class Archetype;

	class TemplateArgument
	{
		private:
			/** Template parameter this argument is a value of. */
			TemplateParameter const&	_boundParameter;

			/** Archetype used for a template argument. */
			Archetype const*			_archetype = nullptr;
			
		public:
			REFUREKU_API TemplateArgument(TemplateParameter const&	boundParameter,
										  Archetype const*			archetype)		noexcept;

			/**
			*	@brief Getter for the field _boundParameter.
			* 
			*	@return _boundParameter.
			*/
			REFUREKU_API TemplateParameter const&	getBoundParameter()	const	noexcept;

			/**
			*	@brief Getter for the field _archetype.
			* 
			*	@return _archetype.
			*/
			//TODO: This will change to a different return type to support non-type template and template template type arguments
			REFUREKU_API Archetype const*			getArchetype()		const	noexcept;
	};
}

//TODO: Add support for NonTypeTemplateArguments