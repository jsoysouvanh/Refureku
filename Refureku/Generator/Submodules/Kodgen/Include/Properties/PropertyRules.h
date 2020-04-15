#pragma once

#include <set>

#include "Misc/Toml11.h"
#include "Properties/SimplePropertyRule.h"
#include "Properties/ComplexPropertyRule.h"

namespace kodgen
{
	class PropertyRules
	{
		private:
			std::set<SimplePropertyRule>	_simplePropertyRules;
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
			PropertyRules(std::string defaultMacroName);
			PropertyRules(PropertyRules const&)			= default;
			PropertyRules(PropertyRules&&)				= default;
			~PropertyRules()							= default;

			bool addSimplePropertyRule(std::string&& propertyName)											noexcept;
			bool removeSimplePropertyRule(std::string&& propertyName)										noexcept;
			bool addComplexPropertyRule(std::string&& mainPropertyName, std::string&& subPropPattern)		noexcept;
			bool removeComplexPropertyRule(std::string&& mainPropertyName, std::string&& subPropPattern)	noexcept;
			bool removeComplexPropertyRule(std::string&& mainPropertyName)									noexcept;

			void clearSimplePropertyRules()																	noexcept;
			void clearComplexPropertyRules()																noexcept;
			void clearAllPropertyRules()																	noexcept;

			void loadSettings(toml::value const& table)														noexcept;

			SimplePropertyRule const*	getSimplePropertyRule(std::string const& propertyName)		const	noexcept;
			ComplexPropertyRule const*	getComplexPropertyRule(std::string const& propertyName)		const	noexcept;

			PropertyRules&	operator=(PropertyRules&)	= default;
			PropertyRules&	operator=(PropertyRules&&)	= default;
	};
}