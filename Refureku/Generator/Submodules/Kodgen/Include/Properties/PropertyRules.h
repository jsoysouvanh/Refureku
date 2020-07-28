/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <set>

#include "Properties/SimplePropertyRule.h"
#include "Properties/ComplexPropertyRule.h"
#include "Misc/Toml11.h"

namespace kodgen
{
	class PropertyRules
	{
		private:
			/** Set of all simple property rules. */
			std::set<SimplePropertyRule>	_simplePropertyRules;

			/** Set of all complex property rules. */
			std::set<ComplexPropertyRule>	_complexPropertyRules;

		public:
			/**
			*	Name of the macro to use in source code to add properties to an entity
			*	
			*	If this PropertyRules object is the classPropertyRules and _macroName = "MyCustomClassMacro", 
			*	We can add properties to a class like so:
			*		class MyCustomClassMacro() SomeClass {};
			*/
			std::string						macroName;

			PropertyRules()								= default;
			PropertyRules(std::string defaultMacroName)	noexcept;
			PropertyRules(PropertyRules const&)			= default;
			PropertyRules(PropertyRules&&)				= default;
			~PropertyRules()							= default;

			/**
			*	@brief Add a simple property rule to this PropertyRules object.
			*	
			*	@param propertyName Name of the simple property to make valid.
			*	
			*	@return true if the simple property was added successfully, else false.
			*/
			bool addSimplePropertyRule(std::string propertyName)											noexcept;

			/**
			*	@brief Remove a simple property rule from this PropertyRules object.
			*	
			*	@param propertyName Name of the simple property to make invalid.
			*	
			*	@return true if the simple property was removed successfully, else false.
			*/
			bool removeSimplePropertyRule(std::string propertyName)											noexcept;

			/**
			*	@brief Add a complex property rule to this PropertyRules object.
			*	
			*	@param mainPropertyName	Name of the main property to make valid.
			*	@param subPropPattern	Regex used to check validity of sub properties.
			*	
			*	@return true if the complex property was added successfully, else false.
			*/
			bool addComplexPropertyRule(std::string mainPropertyName, std::string subPropPattern)			noexcept;

			/**
			*	@brief Remove a complex property rule from this PropertyRules object.
			*	
			*	@param mainPropertyName	Name of the main property to make invalid.
			*	@param subPropPattern	Regex used to check validity of sub properties.
			*	
			*	@return true if the complex property was removed successfully, else false.
			*/
			bool removeComplexPropertyRule(std::string mainPropertyName, std::string subPropPattern)		noexcept;

			/**
			*	@brief Remove a complex property rule from this PropertyRules object.
			*	
			*	@param mainPropertyName	Name of the main property to make invalid.
			*	
			*	@return true if the complex property was removed successfully, else false.
			*/
			bool removeComplexPropertyRule(std::string const& mainPropertyName)								noexcept;

			/**
			*	@brief Remove all simple property rules from this PropertyRules object.
			*/
			void clearSimplePropertyRules()																	noexcept;

			/**
			*	@brief Remove all complex property rules from this PropertyRules object.
			*/
			void clearComplexPropertyRules()																noexcept;

			/**
			*	@brief Remove all property rules (simple & complex) from this PropertyRules object.
			*/
			void clearAllPropertyRules()																	noexcept;

			/**
			*	@brief Load settings from a toml file.
			*
			*	@param table TOML table to look into.
			*/
			void loadSettings(toml::value const& table)														noexcept;

			/**
			*	@brief Retrieve a simple property rule from this PropertyRules object.
			*	
			*	@param propertyName Name of the simple property rule to retrieve.
			*	
			*	@return The found simple property rule if found, else nullptr.
			*/
			SimplePropertyRule const*	getSimplePropertyRule(std::string const& propertyName)		const	noexcept;
			
			/**
			*	@brief Retrieve a complex property rule from this PropertyRules object.
			*	
			*	@param propertyName Name of the complex property rule to retrieve.
			*	
			*	@return The found complex property rule if found, else nullptr.
			*/
			ComplexPropertyRule const*	getComplexPropertyRule(std::string const& propertyName)		const	noexcept;
	};
}