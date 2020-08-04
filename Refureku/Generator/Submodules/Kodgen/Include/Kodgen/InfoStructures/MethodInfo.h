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

#include "Kodgen/InfoStructures/EntityInfo.h"
#include "Kodgen/InfoStructures/TypeInfo.h"
#include "Kodgen/InfoStructures/MethodParamInfo.h"
#include "Kodgen/Misc/FundamentalTypes.h"
#include "Kodgen/Misc/EAccessSpecifier.h"

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

			/** Prototype of this method as a string. */
			std::string						prototype;

			/** Return type of this method. */
			TypeInfo						returnType;

			/** Parameters of this method. */
			std::vector<MethodParamInfo>	parameters;

			MethodInfo()								= default;
			MethodInfo(CXCursor const& cursor,
					   PropertyGroup&& propertyGroup)	noexcept;
			MethodInfo(MethodInfo const&)				= default;
			MethodInfo(MethodInfo&&)					= default;
			~MethodInfo()								= default;

			/**
			*	@brief Get the name of this method.
			*	
			*	@return Return the name of this method.
			*/
			std::string getName()										const noexcept;

			/**
			*	@brief Get the prototype of this method.
			*	
			*	@param removeQualifiers	Should all method qualifiers be removed from the prototype?
			*	@param removeSpaces		Should all spaces be removed from the prototype?
			*	
			*	@return The prototype of the method.
			*/
			std::string getPrototype(bool removeQualifiers	= false,
									 bool removeSpaces		= false)	const noexcept;
	};
}