/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

namespace rfk
{
	/**
	*	@brief Predicate defining if a value is valid or not.
	* 
	*	@param value	The tested value.
	*	@param userData	Data received from the user.
	* 
	*	@return true if the tested value is valid, else false.
	*/
	template <typename T>
	using Predicate = bool (*)(T const& value, void* userData);
}