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
	*	@brief Visitor function.
	* 
	*	@param value	The visited value.
	*	@param userData	Data received from the user.
	* 
	*	@return true to make the visitor continue to the next value, else false (abort).
	*/
	template <typename T>
	using Visitor = bool (*)(T const& value, void* userData);
}