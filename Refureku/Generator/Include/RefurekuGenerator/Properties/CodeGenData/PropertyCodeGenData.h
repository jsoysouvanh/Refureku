/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "RefurekuGenerator/Properties/CodeGenData/ECodeGenLocation.h"

namespace rfk
{
	class PropertyCodeGenData
	{
		private:
			/** Location in which the property code is generated. */
			ECodeGenLocation _codeGenLocation;

		protected:
			PropertyCodeGenData(ECodeGenLocation codeGenLocation)	noexcept;
			PropertyCodeGenData(PropertyCodeGenData const&)			= default;
			PropertyCodeGenData(PropertyCodeGenData&&)				= default;
			~PropertyCodeGenData()									= default;

		public:
			/**
			*	@brief Getter for _codeGenLocation.
			*
			*	@return _codeGenLocation.
			*/
			ECodeGenLocation getCodeGenLocation() const noexcept;
	};
}