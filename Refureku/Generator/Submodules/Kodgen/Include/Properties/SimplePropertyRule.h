/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "Properties/IPropertyRule.h"

namespace kodgen
{
	class SimplePropertyRule : public IPropertyRule
	{
		protected:
			/**
			*	@brief Check that a property rule is used only once in a given property group.
			*	
			*	@param propertyGroup		The property group containing the checked property.
			*	@param propertyIndex		Index of the property that should appear only once.
			*	@param out_errorDescription	Error to fill in case the property rule is used more than once.
			*
			*	@return true if this property rule is used by a single property in the property group, else false.
			*			If false is returned, out_errorDescription must be filled with an error description.
			*/
			virtual bool		isUsedOnlyOnce(PropertyGroup const&	propertyGroup,
											   uint8				propertyIndex,
											   std::string&			out_errorDescription)	const noexcept;

			/**
			*	@return The documentation of the macro defined by this rule.
			*			Can return an empty string.
			*/
			virtual std::string	getMacroDocumentation()										const noexcept;

		public:
			SimplePropertyRule()							= default;
			SimplePropertyRule(SimplePropertyRule const&)	= default;
			SimplePropertyRule(SimplePropertyRule&&)		= default;
			virtual ~SimplePropertyRule()					= default;

			/**
			*	@return The macro definition for properties accepted by this rule.
			*			This macro is only used for auto completion and documentation and is therefore not mandatory.
			*			Can return an empty string.
			*/
			virtual std::string	getMacroDefinition()	const	noexcept;
	};
}