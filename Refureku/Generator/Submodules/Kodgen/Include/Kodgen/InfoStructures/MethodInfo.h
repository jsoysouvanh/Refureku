/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <clang-c/Index.h>

#include "Kodgen/InfoStructures/FunctionInfo.h"
#include "Kodgen/Misc/EAccessSpecifier.h"

namespace kodgen
{
	class MethodInfo final : public FunctionInfo
	{
		public:
			/** Access of this method in its outer struct/class. */
			EAccessSpecifier	accessSpecifier;

			/** Is this method defaulted or not. */
			bool				isDefault		: 1;

			/** Is this method virtual or not. */
			bool				isVirtual		: 1;

			/** Is this method virtual pure or not. */
			bool				isPureVirtual	: 1;

			/** Is this method overriden or not. */
			bool				isOverride		: 1;

			/** Is this method final or not. */
			bool				isFinal			: 1;

			/** Is this method const or not. */
			bool				isConst			: 1;

			MethodInfo()								= default;
			MethodInfo(CXCursor const& cursor,
					   PropertyGroup&& propertyGroup)	noexcept;
			MethodInfo(MethodInfo const&)				= default;
			MethodInfo(MethodInfo&&)					= default;
			~MethodInfo()								= default;
	};
}