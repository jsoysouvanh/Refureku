/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "Kodgen/InfoStructures/EntityInfo.h"
#include "Kodgen/Properties/PropertyGroup.h"
#include "Kodgen/Misc/FundamentalTypes.h"

namespace kodgen
{
	class SimplePropertyRule
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

		public:
			SimplePropertyRule()							= default;
			SimplePropertyRule(SimplePropertyRule const&)	= default;
			SimplePropertyRule(SimplePropertyRule&&)		= default;
			virtual ~SimplePropertyRule()					= default;

			/**
			*	@brief	Check that a main property has a valid syntax for a given type of entity.
			*			This check happens right after the main property has been parsed.
			*
			*	@param mainProperty The property we are checking the syntax of.
			*	@param entityType	Type of the attached entity.
			*	
			*	@return true if the property syntax is valid, else false.
			*/
			virtual bool		isMainPropSyntaxValid(std::string const&	mainProperty,
													  EEntityType			entityType)				const	noexcept = 0;

			/**
			*	@brief	Check that a property is valid inside a given property group.
			*			You could check for invalid double properties, properties order, or incompatible properties for example
			*			This check happens after the property group has been parsed, but before parsing the attached entity.
			*	
			*	@param propertyGroup		PropertyGroup containing the checked property.
			*	@param propertyIndex		Index of the property in the relevant propertyGroup array.
			*	@param out_errorDescription	Reason of non-validity if the property group is not valid.
			*
			*	@return true if the property group is valid, else false.
			*			If false is returned, out_errorDescription must be filled with an error description.
			*/
			virtual bool		isPropertyGroupValid(PropertyGroup const&	propertyGroup,
													 uint8					propertyIndex,
													 std::string&			out_errorDescription)	const	noexcept;

			/**
			*	@brief	Check that the attached entity of a given property is valid.
			*			You could check the type of a field, or the prototype of a method for example.
			*			This check happens after the attached entity has been fully parsed.
			*
			*	@param entity				The entity attached to the checked property.
			*	@param propertyIndex		Index of the property in the relevant propertyGroup array.
			*	@param out_errorDescription	Reason of non-validity if the entity is not valid.
			*
			*	@return true if the entity is valid for this property rule, else false.
			*			If false is returned, out_errorDescription must be filled with an error description.
			*/
			virtual bool		isEntityValid(EntityInfo const& entity,
											  uint8				propertyIndex,
											  std::string&		out_errorDescription)				const	noexcept;
			/**
			*	@brief Entry point to generate code for a given entity and property.
			*	
			*	@param entity	Entity the property is attached to.
			*	@param property	Property bound to this rule.
			*	@param userData	Any data the user might want to pass.
			*	
			*	@return Generated code as string.
			*/
			virtual std::string	generateCode(EntityInfo const&	entity,
											 Property const&	property,
											 void*				userData)							const	noexcept;
	};
}