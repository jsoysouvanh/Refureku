/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "RefurekuGenerator/Properties/CodeGenData/PropertyCodeGenData.h"

namespace rfk
{
	/**
	*	Same class used for PrePropertyAdd and PostPropertyAdd
	*/
	class PropertyCodeGenPropertyAddData : public PropertyCodeGenData
	{
		private:
			/** Variable holding the entity in the generated code. The accessor (. or ->) is also appended at the end of the string. */
			std::string	_entityVariable;

			/** Variable holding the property in the generated code. The accessor (. or ->) is also appended at the end of the string. */
			std::string _propertyVariable;

			/**
			*	@brief Remove the trailing accessor from a variable.
			*	
			*	@param variable String containing the name and the accessor of a variable.
			*	
			*	@return The variable name.
			*/
			std::string removeTrailingAccessor(std::string const& variable)	const	noexcept;

		public:
			PropertyCodeGenPropertyAddData(bool isPreAdd, std::string entityVariable, std::string propertyVariable)	noexcept;
			PropertyCodeGenPropertyAddData(PropertyCodeGenPropertyAddData const&)									= default;
			PropertyCodeGenPropertyAddData(PropertyCodeGenPropertyAddData&&)										= default;
			~PropertyCodeGenPropertyAddData()																		= default;
		
			/**
			*	@brief Access the entity variable in the generated code.
			*	
			*	@return The string to access the entity variable in the generated code, that is the entity variable name + its accessor (. or ->).
			*/
			std::string const&	accessEntityVariable()		const	noexcept;
			
			/**
			*	@brief Access the property variable in the generated code.
			*	
			*	@return The string to access the property variable in the generated code, that is the property variable name + its accessor (. or ->).
			*/
			std::string const&	accessPropertyVariable()	const	noexcept;
			
			/**
			*	@brief	Get the entity variable name in the generated code.
			*			Actually removes the trailing . or -> from accessEntityVariable() when it is called, so you should consider caching the result if used multiple times.
			*	
			*	@return The name of the entity variable in the generated code.
			*/
			std::string			getEntityVariableName()		const	noexcept;
			
			/**
			*	@brief	Get the property variable name in the generated code.
			*			Actually removes the trailing . or -> from accessPropertyVariable() when it is called, so you should consider caching the result if used multiple times.
			*	
			*	@return The name of the property variable in the generated code.
			*/
			std::string			getPropertyVariableName()	const	noexcept;
	};
}