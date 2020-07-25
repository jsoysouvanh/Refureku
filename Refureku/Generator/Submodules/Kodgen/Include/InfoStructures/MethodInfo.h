/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <iostream>
#include <vector>

#include <clang-c/Index.h>

#include "InfoStructures/EntityInfo.h"
#include "InfoStructures/TypeInfo.h"
#include "InfoStructures/MethodParamInfo.h"
#include "Misc/FundamentalTypes.h"
#include "Misc/EAccessSpecifier.h"

namespace kodgen
{
	class MethodInfo : public EntityInfo
	{
		public:
			struct MethodQualifiers
			{
				bool isDefault		: 1;
				bool isStatic		: 1;
				bool isVirtual		: 1;
				bool isPureVirtual	: 1;
				bool isInline		: 1;
				bool isOverride		: 1;
				bool isFinal		: 1;
				bool isConst		: 1;

			}								qualifiers;

			/** Access of this method in its outer struct/class. */
			EAccessSpecifier				accessSpecifier;

			/** Prototype of this method as a string */
			std::string						prototype;

			TypeInfo						returnType;
			std::vector<MethodParamInfo>	parameters;

			MethodInfo()														= default;
			MethodInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup)	noexcept;
			MethodInfo(MethodInfo const&)										= default;
			MethodInfo(MethodInfo&&)											= default;
			~MethodInfo()														= default;

			std::string getName()																const noexcept;
			std::string getPrototype(bool removeQualifiers = false, bool removeSpaces = false)	const noexcept;
	};

	std::ostream& operator<<(std::ostream& out_stream, MethodInfo const& methodInfo) noexcept;
}