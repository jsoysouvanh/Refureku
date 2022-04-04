/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <Kodgen/CodeGen/Macro/MacroPropertyCodeGen.h>
#include <Kodgen/InfoStructures/MethodInfo.h>

namespace rfk
{
	class InstantiatorPropertyCodeGen : public kodgen::MacroPropertyCodeGen
	{
		protected:
			virtual bool generateClassFooterCodeForEntity(kodgen::EntityInfo const& entity, kodgen::Property const& /* property */,
														  kodgen::uint8 /* propertyIndex */, kodgen::MacroCodeGenEnv& env, std::string& inout_result) noexcept override
			{
				kodgen::MethodInfo const&	method		= static_cast<kodgen::MethodInfo const&>(entity);
				std::string					className	= method.outerEntity->getFullName();
				std::string					parameters	= method.getParameterTypes();
				std::string					methodPtr	= "&" + className + "::" + method.name;

				std::string					condition1;
				std::string					condition2;

				if (parameters.empty())
				{
					condition1	= "std::is_invocable_r_v<rfk::SharedPtr<" + className + ">, decltype(" + methodPtr + ")>";
					condition2	= "std::is_same_v<"
									"rfk::SharedPtr<" + className + ">, "
									"std::invoke_result_t<decltype(" + methodPtr + ")>> || "
								  "std::is_same_v<"
									"rfk::UniquePtr<" + className + ">, "
									"std::invoke_result_t<decltype(" + methodPtr + ")>>";
				}
				else
				{
					condition1	= "std::is_invocable_r_v<rfk::SharedPtr<" + className + ">, decltype(" + methodPtr + "), " + parameters + ">";
					condition2	= "std::is_same_v<"
									"rfk::SharedPtr<" + className + ">, "
									"std::invoke_result_t<decltype(" + methodPtr + "), " + parameters + ">> || "
								  "std::is_same_v<"
									"rfk::UniquePtr<" + className + ">, "
									"std::invoke_result_t<decltype(" + methodPtr + "), " + std::move(parameters) + ">>";
				}

				inout_result += "static_assert(" + std::move(condition1) +
					", \"[Refureku] Instantiator requires " + methodPtr + " to be a static method.\");" + env.getSeparator();

				inout_result += "static_assert(" + std::move(condition2) +
					", \"[Refureku] Instantiator requires the return type to be rfk::SharedPtr<" + className + "> or rfk::UniquePtr<" + className + ">.\");" + env.getSeparator();

				return true;
			}

		public:
			InstantiatorPropertyCodeGen() noexcept:
				kodgen::MacroPropertyCodeGen("rfk::Instantiator", kodgen::EEntityType::Method)
			{
			}

			/**
			*	@brief Generate code to add a custom instantiator to the generated class the method belongs to.
			* 
			*	@param method					The Instantiator tagged method.
			*	@param property					The Instantiator property.
			*	@param generatedClassVarName	The name of the rfk::Struct / rfk::Class variable in the generated code
			*										that needs the custom instantiator, followed by -> or .
			*	@param generatedMethodVarName	Name of the rfk::StaticMethod variable in the generated code (the variable must be a pointer).
			*	@param inout_result				String to append the generated code.
			*/
			void addInstantiatorToClass(kodgen::MethodInfo const& method, kodgen::Property const& /* property */,
										std::string const& generatedClassVarName, std::string const& generatedMethodVarName, std::string& inout_result) const noexcept
			{
				std::string returnedType = method.returnType.getName();

				//Check whether the method is a unique instantiator or a shared instantiator
				//We already know from the generated static asserts that at this point the return type is either rfk::UniquePtr<Class> or rfk::SharedPtr<Class>
				//So if we find the letter n (uNique) before the template param opening <, we know it is a UniquePtr (there's no 'n' in SharedPtr).
				//Don't use U to avoid case conflicts, it would still work if the user uses std::unique_ptr / std::shared_ptr
				//NOTE: it doesn't work if the pointer types are aliased.
				if (returnedType.find('n') < returnedType.find('<'))
				{
					//UniquePtr
					inout_result += generatedClassVarName + "addUniqueInstantiator(*" + generatedMethodVarName + "); ";
				}
				else
				{
					//SharedPtr
					inout_result += generatedClassVarName + "addSharedInstantiator(*" + generatedMethodVarName + "); ";
				}
			}
	};
}