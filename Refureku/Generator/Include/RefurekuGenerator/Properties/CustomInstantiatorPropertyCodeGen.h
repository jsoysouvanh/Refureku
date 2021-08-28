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
	class CustomInstantiatorPropertyCodeGen : public kodgen::MacroPropertyCodeGen
	{
		protected:
			virtual bool	generateClassFooterCode(kodgen::EntityInfo const*	entity,
													kodgen::Property const*		property,
													kodgen::uint8				propertyIndex,
													kodgen::MacroCodeGenEnv&	env,
													std::string&				inout_result)			noexcept	override;

			/*virtual std::string generatePrePropertyAddCode(kodgen::EntityInfo const&		entity,
														   kodgen::Property const&			property,
														   PropertyCodeGenPropertyAddData&	data)		const noexcept override;

			virtual std::string generateClassFooterCode(kodgen::EntityInfo const&		entity,
														kodgen::Property const&			property,
														PropertyCodeGenClassFooterData&	data)			const noexcept override;*/

		public:
			CustomInstantiatorPropertyCodeGen() noexcept;
	};
}