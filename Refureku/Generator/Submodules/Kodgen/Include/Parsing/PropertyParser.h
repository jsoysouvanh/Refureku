#pragma once

#include "Misc/Optional.h"
#include "Properties/PropertyGroup.h"
#include "Properties/PropertyParsingSettings.h"
#include "Parsing/EParsingError.h"

namespace kodgen
{
	class PropertyParser
	{
		private:
			PropertyParsingSettings const*			_propertyParsingSettings	= nullptr;

			EParsingError							_parsingError				= EParsingError::Count;
			std::vector<std::vector<std::string>>	_splitProps;
			std::string								_relevantCharsForPropParsing;
			std::string								_relevantCharsForSubPropParsing;

			/**
			*	Returns true on a successful split, else false
			*
			*	On success, _splitProps is updated
			*	On failure, _parsingError is updated
			*/
			bool splitProperties(std::string&& propertiesString) noexcept;

			/**
			*	Removes all ignored characters from the string
			*/
			void cleanString(std::string& toCleanString) const noexcept;

			/**
			*	Search the next property. inout_parsingProps will be updated to the current parsing state
			*	and out_isParsingSubProp is filled consequently
			*
			*	On success, returns true & add the prop to _splitProps (new vector).
			*	On failure, returns false
			*/
			bool lookForNextProp(std::string& inout_parsingProps, bool& out_isParsingSubProp);

			/**
			*	Search the next sub property. inout_parsingProps will be updated to the current parsing state
			*	and out_isParsingSubProp is filled consequently
			*
			*	On success, returns true & add the prop to _splitProps (last added vector)
			*	On failure, returns false
			*/
			bool lookForNextSubProp(std::string& inout_parsingProps, bool& out_isParsingSubProp);

			/**
			*	Check for each prop / subprop validity and fill a propertyGroup consequently
			*	On success, returns the filled propertyGroup object
			*	On failure, returns an empty empty optional object
			*/
			opt::optional<PropertyGroup> checkAndFillPropertyGroup(std::vector<std::vector<std::string>>& splitProps, PropertyRules const& rules) noexcept;

			/**
			*	Add a single property to the given property group using the provided data
			*	On success, returns true and update the PropertyGroup object
			*	On failure, returns false and update _parsingError value
			*/
			bool addSimpleProperty(std::vector<std::string>& propertyAsVector, PropertyRules const& rules, PropertyGroup& out_propertyGroup) noexcept;

			/**
			*	Add a complex property to the given property group using the provided data
			*	On success, returns true and update the PropertyGroup object
			*	On failure, returns false and update _parsingError value
			*/
			bool addComplexProperty(std::vector<std::string>& propertyAsVector, PropertyRules const& rules, PropertyGroup& out_propertyGroup) noexcept;

		public:
			/**
			*	Called by the parser to internally setup some acceleration data
			*/
			void setup(PropertyParsingSettings const& propertyParsingSettings) noexcept;

			/**
			*	Clear all collected data such as parsingErrors or split props.
			*	Called to have a clean state and prepare for a new parse
			*/
			void clean() noexcept;

			/**
			*	All get[...]Properties(std::string&& annotateMessage) below methods return an initialized optional
			*	if the annotate message is valid, else an uninitialized one.
			*/
			opt::optional<PropertyGroup>	getProperties(std::string&& annotateMessage, std::string const& annotationId, PropertyRules const& rules) noexcept;

			opt::optional<PropertyGroup>	getNamespaceProperties(std::string&& annotateMessage)	noexcept;
			opt::optional<PropertyGroup>	getClassProperties(std::string&& annotateMessage)		noexcept;
			opt::optional<PropertyGroup>	getStructProperties(std::string&& annotateMessage)		noexcept;
			opt::optional<PropertyGroup>	getFieldProperties(std::string&& annotateMessage)		noexcept;
			opt::optional<PropertyGroup>	getMethodProperties(std::string&& annotateMessage)		noexcept;
			opt::optional<PropertyGroup>	getEnumProperties(std::string&& annotateMessage)		noexcept;
			opt::optional<PropertyGroup>	getEnumValueProperties(std::string&& annotateMessage)	noexcept;

			EParsingError					getParsingError() const noexcept;
	};
}