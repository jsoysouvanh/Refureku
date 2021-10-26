/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <memory>	//std::unique_ptr
#include <utility>	//std::forward

namespace rfk
{
	//Use std implementation for now, might have a custom implementation someday if necessary
	template <typename T, class Deleter = std::default_delete<T>>
	using UniquePtr = std::unique_ptr<T, Deleter>;

	template<typename T, typename... Args>
	UniquePtr<T> makeUnique(Args&&... args);

	#include "Refureku/Misc/UniquePtr.inl"
}