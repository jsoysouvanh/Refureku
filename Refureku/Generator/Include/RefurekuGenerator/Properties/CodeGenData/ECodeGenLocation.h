/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

namespace rfk
{
	enum class ECodeGenLocation
	{
		/**
		*	Code will be generated in the generated file (without macro),
		*	so it will be injected as soon as the generated file is included.
		*/
		FileHeader = 0,

		/**
		*	Code will be inserted just before the property is added to the entity.
		*/
		PrePropertyAdd,

		/**
		*	Code will be inserted just after the property is added to the entity.
		*/
		PostPropertyAdd,

		/**
		*	Code will be inserted in the ClassName_GENERATED macro (also works for structs).
		*/
		ClassFooter,

		/**
		*	Code will be inserted in the File_GENERATED macro (at the very end of a file).
		*/
		FileFooter
	};
}