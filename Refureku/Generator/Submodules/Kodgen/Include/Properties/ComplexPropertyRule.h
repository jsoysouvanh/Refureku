/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "Properties/SimplePropertyRule.h"

namespace kodgen
{
	class ComplexPropertyRule : public SimplePropertyRule
	{
		protected:
			/**
			*	@brief Check that a complex property has the right number of sub properties.
			*	
			*	@param propertyGroup		Property group containing the checked property.
			*	@param propertyIndex		Index of the complex property in the property group.
			*	@param validCount			Number of subproperties which would make this complex property valid.
			*	@param out_errorDescription	Error to fill in case the subprop count is not valid.
			*	
			*	@return true if the property has the correct number of subproperties, else false.
			*			If false is returned, out_errorDescription must be filled with an error description.
			*/
			bool			hasValidSubpropCount(PropertyGroup const&	propertyGroup,
												 uint8					propertyIndex,
												 uint8					validCount,
												 std::string&			out_errorDescription)	const noexcept;

			virtual bool	isUsedOnlyOnce(PropertyGroup const&	propertyGroup,
										   uint8					propertyIndex,
										   std::string&				out_errorDescription)		const noexcept override final;

		public:
			ComplexPropertyRule()								= default;
			ComplexPropertyRule(ComplexPropertyRule const&)	= default;
			ComplexPropertyRule(ComplexPropertyRule&&)		= default;
			virtual ~ComplexPropertyRule()						= default;

			/**
			*	@brief	Check that a sub property has a valid syntax for a given type of entity.
			*			This check happens right after the sub property has been parsed.
			*
			*	@param subProperty			The property we are checking the syntax of.
			*	@param subPropIndex			Index of the subproperty. First subproperty has index 0.
			*	@param out_errorDescription	Reason of non-validity if the sub property is not valid.
			*	
			*	@return true if the property syntax is valid, else false.
			*			If false is returned, out_errorDescription must be filled with an error description.
			*/
			virtual bool isSubPropSyntaxValid(std::string const&	subProperty,
											  uint8					subPropIndex,
											  std::string&			out_errorDescription)	const noexcept = 0;
	};
}