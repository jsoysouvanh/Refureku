/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Entity/Entity.h"
#include "Refureku/TypeInfo/TypeAPI.h"

namespace rfk
{
	class FunctionParameterAPI : public EntityAPI
	{
		public:
			REFUREKU_INTERNAL FunctionParameterAPI(char const*		name,
												   std::size_t		id,
												   TypeAPI const&	type,
												   EntityAPI const*	outerEntity = nullptr)	noexcept;
			FunctionParameterAPI(FunctionParameterAPI const&)								= delete;
			REFUREKU_INTERNAL FunctionParameterAPI(FunctionParameterAPI&&)					noexcept;
			REFUREKU_INTERNAL ~FunctionParameterAPI()										noexcept;

			/**
			*	@brief Get the
			* 
			*	@return _type;
			*/
			RFK_NODISCARD REFUREKU_API TypeAPI const& getType()	const	noexcept;

		protected:
			//Forward declaration
			class FunctionParameterImpl;
	};
}