/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

namespace rfk
{
	/**
	*	Enum describing where generated code will be inserted.
	*
	*	//Example.h
	*	#pragma once
	*
	*	#include "Example.rfk.h"	<- FileHeader value inserts code here
	*
	*	class RFKClass() Example
	*	{
	*		Example_GENERATED		<- ClassFooter value inserts code here
	*	};
	*
	*	File_GENERATED				<- FileFooter value inserts code here
	*/
	enum class ECodeGenLocation
	{
		/**
		*	Code will be inserted where the generated file is included,
		*	i.e. where #include "GeneratedFile.rfk.h" is included.
		*/
		FileHeader,

		/**
		*	Code will be inserted just before the property is added to the entity.
		*/
		PropertyAdd,

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