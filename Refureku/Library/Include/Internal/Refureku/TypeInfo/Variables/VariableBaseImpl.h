/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Variables/VariableBase.h"
#include "Refureku/TypeInfo/Entity/EntityImpl.h"

namespace rfk
{
	class VariableBase::VariableBaseImpl : public Entity::EntityImpl
	{
		private:
			/** Type of this variable. */
			Type const&	_type;

			/**
			 * Name of this variable's type simplified by unwinding all aliases, typedefs.
			 */
			std::string _canonicalTypeName;

		public:
			inline VariableBaseImpl(char const*			name,
									std::size_t			id,
									EEntityKind			kind,
									char const*         canonicalTypeName,
									Type const&		type,
									Entity const*	outerEntity)	noexcept;

			/**
			*	@brief Getter for the field _type.
			* 
			*	@return _type.
			*/
			inline Type const& getType()			  const noexcept;

			/**
			*	@brief Getter for the field _canonicalTypeName.
			* 
			*	@return _canonicalTypeName.
			*/
			inline char const* getCanonicalTypeName() const noexcept;
	};

	#include "Refureku/TypeInfo/Variables/VariableBaseImpl.inl"
}