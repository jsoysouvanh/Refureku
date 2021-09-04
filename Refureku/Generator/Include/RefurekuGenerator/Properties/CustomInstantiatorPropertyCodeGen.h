/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <Kodgen/CodeGen/Macro/MacroPropertyCodeGen.h>
#include <Kodgen/InfoStructures/MethodInfo.h>

namespace rfk
{
	class CustomInstantiatorPropertyCodeGen : public kodgen::MacroPropertyCodeGen
	{
		protected:
			virtual bool	generateClassFooterCodeForEntity(kodgen::EntityInfo const&	entity,
															 kodgen::Property const&	property,
															 kodgen::uint8				propertyIndex,
															 kodgen::MacroCodeGenEnv&	env,
															 std::string&				inout_result)	noexcept	override;

		public:
			CustomInstantiatorPropertyCodeGen() noexcept;

			/**
			*	@brief Generate code to add a custom instantiator to the generated class the method belongs to.
			* 
			*	@param method					The CustomInstantiator tagged method.
			*	@param generatedClassVarName	The name of the rfk::Struct / rfk::Class variable in the generated code
			*										that needs the custom instantiator, followed by -> or .
			*	@param generatedMethodVarName	Name of the rfk::StaticMethod variable in the generated code (the variable must be a pointer).
			*	@param inout_result				String to append the generated code.
			*/
			void	addCustomInstantiatorToClass(kodgen::MethodInfo const&	method,
												 std::string const&			generatedClassVarName,
												 std::string const&			generatedMethodVarName,
												 std::string&				inout_result)				const	noexcept;
	};
}