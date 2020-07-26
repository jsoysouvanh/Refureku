/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <CodeGen/GeneratedCodeTemplate.h>
#include <InfoStructures/NamespaceInfo.h>

#include "GeneratedEntityCodeTemplate.h"

namespace rfk
{
	class GeneratedNamespaceCodeTemplate : public GeneratedEntityCodeTemplate
	{
		private:
			/**
			*	@brief Generate the macro which declares the getNamespaceFragment function for the provided namespace.
			*	
			*	@param generatedFile	File to write into.
			*	@param namespaceInfo	Structure containing namespace info.
			*
			*	@return The name of the generated macro.
			*/
			std::string generateGetNamespaceFragmentDeclarationMacro(kodgen::GeneratedFile&			generatedFile,
																	 kodgen::NamespaceInfo const&	namespaceInfo)		const	noexcept;

			/**
			*	@brief Generate the macro which defines the fillNamespace function for the provided namespace.
			*	
			*	@param generatedFile	File to write into.
			*	@param namespaceInfo	Structure containing namespace info.
			*
			*	@return The name of the generated macro.
			*/
			std::string generateGetNamespaceFragmentDefinitionMacro(kodgen::GeneratedFile&			generatedFile,
																	kodgen::NamespaceInfo const&	namespaceInfo)		const	noexcept;

			/**
			*	@brief Generate the macro which defines the NamespaceRegisterer
			*
			*	@param generatedFile	File to write into.
			*	@param namespaceInfo	Structure containing namespace info.
			*
			*	@return The name of the generated macro.
			*/
			std::string generateRegistrationMacro(kodgen::GeneratedFile&		generatedFile,
												  kodgen::NamespaceInfo const&	namespaceInfo)							const	noexcept;

			/**
			*	@brief Get the name of the generated getNamespaceFragment method for the currently processing namespace.
			*
			*	@param generatedFile	File to write into.
			*
			*	@return The name of the getNamespaceFragment function for the current namespace.
			*/
			std::string getGetNamespaceFragmentFunctionName(kodgen::GeneratedFile const& generatedFile)					const	noexcept;

			/**
			*	@brief Get the name of the NamespaceFragmentRegisterer variable generated for the provided namespace.
			*
			*	@param generatedFile	File to write into.
			*	@param namespaceInfo	Structure containing namespace info.
			*
			*	@return The name of the generated NamespaceRegisterer variable.
			*/
			std::string getNamespaceFragmentRegistererName(kodgen::GeneratedFile const& generatedFile,
														   kodgen::NamespaceInfo const&	namespaceInfo)					const	noexcept;

		protected:
			virtual void generateCode(kodgen::GeneratedFile&	generatedFile,
									  kodgen::EntityInfo const&	entityInfo)		noexcept override;

		public:
			GeneratedNamespaceCodeTemplate()										= default;
			GeneratedNamespaceCodeTemplate(GeneratedNamespaceCodeTemplate const&)	= default;
			GeneratedNamespaceCodeTemplate(GeneratedNamespaceCodeTemplate&&)		= default;
			virtual ~GeneratedNamespaceCodeTemplate()								= default;
	};
}
