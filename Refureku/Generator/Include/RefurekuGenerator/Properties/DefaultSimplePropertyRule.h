/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <Kodgen/Properties/DefaultSimplePropertyRule.h>

#include "RefurekuGenerator/Properties/CodeGenData/PropertyCodeGenFileHeaderData.h"
#include "RefurekuGenerator/Properties/CodeGenData/PropertyCodeGenPropertyAddData.h"
#include "RefurekuGenerator/Properties/CodeGenData/PropertyCodeGenClassFooterData.h"
#include "RefurekuGenerator/Properties/CodeGenData/PropertyCodeGenFileFooterData.h"

namespace rfk
{
	class DefaultSimplePropertyRule : public kodgen::DefaultSimplePropertyRule
	{
		protected:
			/**
			*	@brief Generate code in the file header.
			*
			*	@param entity	Entity the property generating code is attached to.
			*	@param property	Property we are generating code for.
			*	@param data		Additional data relative to this code location.
			*
			*	@return The generated code to insert in the file header.
			*/
			virtual std::string generateFileHeaderCode(kodgen::EntityInfo const&		entity,
													   kodgen::Property const&			property,
													   PropertyCodeGenFileHeaderData&	data)			const noexcept;

			/**
			*	@brief Generate code before adding the property to the entity in the generated code.
			*
			*	@param entity	Entity the property generating code is attached to.
			*	@param property	Property we are generating code for.
			*	@param data		Additional data relative to this code location.
			*
			*	@return The generated code to insert before adding the property to the entity.
			*/
			virtual std::string generatePrePropertyAddCode(kodgen::EntityInfo const&		entity,
														   kodgen::Property const&			property,
														   PropertyCodeGenPropertyAddData&	data)		const noexcept;

			/**
			*	@brief Generate code after adding the property to the entity in the generated code.
			*
			*	@param entity	Entity the property generating code is attached to.
			*	@param property	Property we are generating code for.
			*	@param data		Additional data relative to this code location.
			*
			*	@return The generated code to insert after adding the property to the entity.
			*/
			virtual std::string generatePostPropertyAddCode(kodgen::EntityInfo const&		entity,
															kodgen::Property const&			property,
															PropertyCodeGenPropertyAddData&	data)		const noexcept;

			/**
			*	@brief	Generate code in the class footer in [ClassName]_GENERATED macro.
			*			It is called for structs, classes, fields and methods only.
			*
			*	@param entity	Entity the property generating code is attached to.
			*	@param property	Property we are generating code for.
			*	@param data		Additional data relative to this code location.
			*
			*	@return The generated code to insert in the class footer.
			*/
			virtual std::string generateClassFooterCode(kodgen::EntityInfo const&		entity,
														kodgen::Property const&			property,
														PropertyCodeGenClassFooterData&	data)			const noexcept;

			/**
			*	@brief Generate code in the file footer in File_GENERATED macro.
			*
			*	@param entity	Entity the property generating code is attached to.
			*	@param property	Property we are generating code for.
			*	@param data		Additional data relative to this code location.
			*
			*	@return The generated code to insert in the file footer.
			*/
			virtual std::string generateFileFooterCode(kodgen::EntityInfo const&		entity,
													   kodgen::Property const&			property,
													   PropertyCodeGenFileFooterData&	data)			const noexcept;

		public:
			DefaultSimplePropertyRule()											= delete;
			DefaultSimplePropertyRule(std::string			mainPropName,
									  kodgen::EEntityType	validEntityTypes)	noexcept;
			DefaultSimplePropertyRule(DefaultSimplePropertyRule const&)			= default;
			DefaultSimplePropertyRule(DefaultSimplePropertyRule&&)				= default;
			virtual ~DefaultSimplePropertyRule()								= default;

			virtual std::string	generateCode(kodgen::EntityInfo const&	entity,
											 kodgen::Property const&	property,
											 void*						userData)	const noexcept override final;
	};
}