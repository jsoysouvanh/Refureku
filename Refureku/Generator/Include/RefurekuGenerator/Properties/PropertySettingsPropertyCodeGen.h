/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <Kodgen/CodeGen/Macro/MacroPropertyCodeGen.h>

namespace rfk
{
	class PropertySettingsPropertyCodeGen : public kodgen::MacroPropertyCodeGen
	{
		protected:
			virtual bool	initialGenerateHeaderFileHeaderCode(kodgen::MacroCodeGenEnv&	env,
																std::string&				inout_result)	noexcept	override;

			virtual bool	generateClassFooterCodeForEntity(kodgen::EntityInfo const&	entity,
															 kodgen::Property const&	property,
															 kodgen::uint8				propertyIndex,
															 kodgen::MacroCodeGenEnv&	env,
															 std::string&				inout_result)		noexcept	override;

			virtual bool	initialGenerateSourceFileHeaderCode(kodgen::MacroCodeGenEnv&	env,
																std::string&				inout_result)	noexcept	override;

			virtual bool	generateSourceFileHeaderCodeForEntity(kodgen::EntityInfo const&	entity,
																  kodgen::Property const&	property,
																  kodgen::uint8				propertyIndex,
																  kodgen::MacroCodeGenEnv&	env,
																  std::string&				inout_result)	noexcept	override;

		public:
			PropertySettingsPropertyCodeGen() noexcept;
	};
}