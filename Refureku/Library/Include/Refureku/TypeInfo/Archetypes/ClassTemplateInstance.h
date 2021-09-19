/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <vector>
#include <array>

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/Archetypes/Class.h"
#include "Refureku/TypeInfo/Archetypes/TemplateArgument.h"

namespace rfk
{
	//Forward declaration
	class ClassTemplate;

	class ClassTemplateInstance : public Class
	{
		public:
			/** Class template this instance comes from. */
			ClassTemplate const&			instantiatedFrom;

			/** List of all template arguments of this class template instance. */
			std::vector<TemplateArgument>	templateArguments;

			REFUREKU_API ClassTemplateInstance(std::string&&	name,
											   std::size_t		id,
											   std::size_t		memorySize,
											   bool				isClass,
											   Archetype const&	instantiatedFrom)	noexcept;

			/**
			*	@brief Check whether the instance arguments have the same types as the provided ones.
			* 
			*	@tparam The types to check.
			* 
			*	@return true if the provided types are the same as this instance's, else false.
			*/
			template <typename... Types>
			bool hasSameTemplateArguments()																const	noexcept;

			/**
			*	@brief Check whether the instance arguments have the same types as the provided ones.
			* 
			*	@tparam Size Number of provided archetypes.
			*	
			*	@param archetypes Archetypes to check.
			* 
			*	@return true if the provided types are the same as this instance's, else false.
			*/
			template <size_t ArraySize>
			bool hasSameTemplateArguments(std::array<Archetype const*, ArraySize> const& archetypes)	const	noexcept;	//TODO: prototype must change to be able to check with non-type parameters
	};

	#include "Refureku/TypeInfo/Archetypes/ClassTemplateInstance.inl"
}