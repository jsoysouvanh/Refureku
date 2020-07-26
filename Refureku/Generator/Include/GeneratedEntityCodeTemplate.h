/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <CodeGen/GeneratedCodeTemplate.h>
#include <InfoStructures/EntityInfo.h>

namespace rfk
{
	class GeneratedEntityCodeTemplate : public kodgen::GeneratedCodeTemplate
	{
		private:
			/** Id of the currently generating entity as an integer string (i.e. "42"). */
			std::string	_currentEntityId;

		protected:
			/** Prefix used to build internal macros. */
			static constexpr char const* const	internalPrefix = "__RFK";
			
			/** Prefix used to build user exposed macros. */
			static constexpr char const* const	externalPrefix = "";

			/** Class global string hasher. */
			static std::hash<std::string> const	stringHasher;

			virtual void generateCode(kodgen::GeneratedFile&	generatedFile,
									  kodgen::EntityInfo const&	entityInfo)		noexcept override;

			/**
			*	TODO
			*/
			std::string	fillEntityProperties(kodgen::EntityInfo const&	info,
											 std::string const&			entityVarName)	const	noexcept;

			inline std::string const& getCurrentEntityId() const noexcept { return _currentEntityId; }

		public:
			GeneratedEntityCodeTemplate()									= default;
			GeneratedEntityCodeTemplate(GeneratedEntityCodeTemplate const&)	= default;
			GeneratedEntityCodeTemplate(GeneratedEntityCodeTemplate&&)		= default;
			virtual ~GeneratedEntityCodeTemplate()							= default;
	};
}
