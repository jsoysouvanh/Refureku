/**
*	Copyright (c) 2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

namespace rfk
{
	/**
	*	@brief	Helper type traits class that copy the constness of a type to a target type.
	*			ex: CopyConstness<int, float>::Type			yields float
	*				CopyConstness<int const, float>::Type	yields float const
	*/
	template <typename Source, typename Target>
	struct CopyConstness
	{
		using Type = Target;
	};

	template <typename Source, typename Target>
	struct CopyConstness<Source const, Target>
	{
		using Type = Target const;
	};
}