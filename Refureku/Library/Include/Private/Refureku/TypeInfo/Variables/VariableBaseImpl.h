/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Variables/VariableBaseAPI.h"
#include "Refureku/TypeInfo/Entity/EntityImpl.h"
#include "Refureku/TypeInfo/Type.h"	//TODO: Replace by TypeAPI

namespace rfk
{
	class VariableBaseAPI::VariableBaseImpl : public EntityAPI::EntityImpl
	{
		private:
			/** Type of this variable. */
			Type const&	_type;	//TODO: Replace by TypeAPI

		public:
			VariableBaseImpl(char const*		name,
							 std::size_t		id,
							 EEntityKind		kind,
							 Type const&		type,	//TODO: Replace by TypeAPI
							 EntityAPI const*	outerEntity)	noexcept;
			VariableBaseImpl(VariableBaseImpl const&)			= delete;
			VariableBaseImpl(VariableBaseImpl&&)				= delete;

			/**
			*	@brief Getter for the field _type.
			* 
			*	@return _type.
			*/
			inline Type const& getType() const noexcept;	//TODO: Replace by TypeAPI

			VariableBaseImpl& operator=(VariableBaseImpl const&)	= delete;
			VariableBaseImpl& operator=(VariableBaseImpl&&)			= delete;
	};

	#include "Refureku/TypeInfo/Variables/VariableBaseImpl.inl"
}