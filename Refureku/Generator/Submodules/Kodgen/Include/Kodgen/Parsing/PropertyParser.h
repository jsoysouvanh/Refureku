/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Kodgen/InfoStructures/EntityInfo.h"
#include "Kodgen/Properties/PropertyGroup.h"
#include "Kodgen/Properties/PropertyParsingSettings.h"
#include "Kodgen/Misc/Optional.h"

namespace kodgen
{
	class PropertyParser
	{
		private:
			/** Parsing settings to use. */
			PropertyParsingSettings const*			_propertyParsingSettings	= nullptr;

			/** Last parsing error which occured when parsing from this parser. */
			std::string								_parsingErrorDescription	= "";

			/** Collection of last parsed split properties. */
			std::vector<std::vector<std::string>>	_splitProps;

			/** Chars to take into consideration when parsing a property. */
			std::string								_relevantCharsForPropParsing;

			/** Chars to take into consideration when parsing a sub property. */
			std::string								_relevantCharsForSubPropParsing;

			/**
			*	@brief	Split properties and fill _splitProps on success.
			*			On failure, _parsingErrorDescription is updated.
			*
			*	@param propertiesString String containing the properties to split.
			*
			*	@return true on a successful split, else false.
			*/
			bool splitProperties(std::string&& propertiesString)															noexcept;

			/**
			*	@brief Remove all ignored characters from the string.
			*
			*	@param toCleanString The string we want to clean.
			*/
			void cleanString(std::string& toCleanString)															const	noexcept;

			/**
			*	@brief	Search the next property.
			*			inout_parsingProps will be updated to the current parsing state and out_isParsingSubProp is filled consequently
			*
			*	@param inout_parsingProps	The string we are looking the next prop in.
			*	@param out_isParsingSubProp	Filled by this function call to indicate either the processed prop has following subprops or not.
			*
			*	@return true & add the prop to _splitProps (new vector) on success, else return false.
			*/
			bool lookForNextProp(std::string&	inout_parsingProps,
								 bool&			out_isParsingSubProp)														noexcept;

			/**
			*	@brief	Search the next sub property.
			*			inout_parsingProps will be updated to the current parsing state and out_isParsingSubProp is filled consequently
			*
			*	@param inout_parsingProps	The string we are looking the next prop in.
			*	@param out_isParsingSubProp	Filled by this function call to indicate either the processed prop has following subprops or not.
			*
			*	@return true & add the prop to _splitProps (last added vector) on success, else return false.
			*/
			bool lookForNextSubProp(std::string&	inout_parsingProps,
									bool&			out_isParsingSubProp)													noexcept;

			/**
			*	@brief	Check for each prop / subprop validity and fill a propertyGroup consequently.
			*	
			*	@param splitProps	The collection of all parsed props / subprops.
			*	@param entityType	The type of the attached entity.
			*
			*	@return A valid optional object if all properties were valid, else an empty optional.
			*			On failure, _parsingErrorDescription is updated.
			*/
			opt::optional<PropertyGroup> checkAndFillPropertyGroup(std::vector<std::vector<std::string>>&	splitProps,
																   EEntityType								entityType)		noexcept;

			/**
			*	@brief Add a single property to the given property group using the provided data.
			*
			*	@param propertyAsVector		Vector of property (element 0 is the property to add).
			*	@param entityType			The type of the attached entity.
			*	@param out_propertyGroup	Group of property to update.
			*
			*	@return true and update the out_propertyGroup parameter on success, else return false and update _parsingErrorDescription value.
			*/
			bool addSimpleProperty(std::vector<std::string>&	propertyAsVector,
								   EEntityType					entityType,
								   PropertyGroup&				out_propertyGroup)											noexcept;

			/**
			*	@brief Add a complex property to the given property group using the provided data.
			*
			*	@param propertyAsVector		Vector of properties. Element 0 is the main prop, next elements are subprops.
			*	@param entityType			The type of the attached entity.
			*	@param out_propertyGroup	Group of property to update.
			*
			*	@return true and update the out_propertyGroup parameter on success, else return false and update _parsingErrorDescription value.
			*/
			bool addComplexProperty(std::vector<std::string>&	propertyAsVector,
									EEntityType					entityType,
									PropertyGroup&				out_propertyGroup)											noexcept;

			/**
			*	@brief Retrieve properties from a string if possible.
			*
			*	@param annotateMessage	The raw string contained in the __attribute__(annotate()) preprocessor.
			*	@param annotationId		The annotation the annotate message should begin with to be considered as valid.
			*	@param entityType		The type of the attached entity.
			*
			*	@return A valid optional object if all properties were valid, else an empty optional.
			*			On failure, _parsingErrorDescription is updated.
			*/
			opt::optional<PropertyGroup>	getProperties(std::string&&			annotateMessage,
														  std::string const&	annotationId,
														  EEntityType			entityType)									noexcept;

		public:
			/**
			*	@brief Called by the parser to internally setup some acceleration data
			*
			*	@param propertyParsingSettings Parsing settings to be used by this parser.
			*/
			void setup(PropertyParsingSettings const& propertyParsingSettings)						noexcept;

			/**
			*	@brief	Clear all collected data such as parsingErrors or split props. Called to have a clean state and prepare to parse new properties.
			*/
			void clean()																			noexcept;

			/**
			*	@brief Retrieve the properties from a namespace annotate attribute.
			*
			*	@param annotateMessage The string we retrieve the properties from.
			*	
			*	@return A valid optional object if all properties were valid, else an empty optional.
			*			On failure, _parsingErrorDescription is updated.
			*/
			opt::optional<PropertyGroup>	getNamespaceProperties(std::string annotateMessage)		noexcept;
			
			/**
			*	@brief Retrieve the properties from a class annotate attribute.
			*
			*	@param annotateMessage The string we retrieve the properties from.
			*	
			*	@return A valid optional object if all properties were valid, else an empty optional.
			*			On failure, _parsingErrorDescription is updated.
			*/
			opt::optional<PropertyGroup>	getClassProperties(std::string annotateMessage)			noexcept;
			
			/**
			*	@brief Retrieve the properties from a struct annotate attribute.
			*
			*	@param annotateMessage The string we retrieve the properties from.
			*	
			*	@return A valid optional object if all properties were valid, else an empty optional.
			*			On failure, _parsingErrorDescription is updated.
			*/
			opt::optional<PropertyGroup>	getStructProperties(std::string annotateMessage)		noexcept;
			
			/**
			*	@brief Retrieve the properties from a variable annotate attribute.
			*
			*	@param annotateMessage The string we retrieve the properties from.
			*	
			*	@return A valid optional object if all properties were valid, else an empty optional.
			*			On failure, _parsingErrorDescription is updated.
			*/
			opt::optional<PropertyGroup>	getVariableProperties(std::string annotateMessage)		noexcept;

			/**
			*	@brief Retrieve the properties from a field annotate attribute.
			*
			*	@param annotateMessage The string we retrieve the properties from.
			*	
			*	@return A valid optional object if all properties were valid, else an empty optional.
			*			On failure, _parsingErrorDescription is updated.
			*/
			opt::optional<PropertyGroup>	getFieldProperties(std::string annotateMessage)			noexcept;

			/**
			*	@brief Retrieve the properties from a function annotate attribute.
			*
			*	@param The string we retrieve the properties from.
			*	
			*	@return A valid optional object if all properties were valid, else an empty optional.
			*			On failure, _parsingErrorDescription is updated.
			*/
			opt::optional<PropertyGroup>	getFunctionProperties(std::string annotateMessage)		noexcept;

			/**
			*	@brief Retrieve the properties from a method annotate attribute.
			*
			*	@param annotateMessage The string we retrieve the properties from.
			*	
			*	@return A valid optional object if all properties were valid, else an empty optional.
			*			On failure, _parsingErrorDescription is updated.
			*/
			opt::optional<PropertyGroup>	getMethodProperties(std::string annotateMessage)		noexcept;

			/**
			*	@brief Retrieve the properties from an enum annotate attribute.
			*
			*	@param annotateMessage The string we retrieve the properties from.
			*	
			*	@return A valid optional object if all properties were valid, else an empty optional.
			*			On failure, _parsingErrorDescription is updated.
			*/
			opt::optional<PropertyGroup>	getEnumProperties(std::string annotateMessage)			noexcept;

			/**
			*	@brief Retrieve the properties from an enum value annotate attribute.
			*
			*	@param annotateMessage The string we retrieve the properties from.
			*	
			*	@return A valid optional object if all properties were valid, else an empty optional.
			*			On failure, _parsingErrorDescription is updated.
			*/
			opt::optional<PropertyGroup>	getEnumValueProperties(std::string annotateMessage)		noexcept;

			/**
			*	@brief Getter for _parsingErrorDescription field.
			*	
			*	@return _parsingErrorDescription.
			*/
			std::string const&				getParsingErrorDescription()					const	noexcept;
	};
}