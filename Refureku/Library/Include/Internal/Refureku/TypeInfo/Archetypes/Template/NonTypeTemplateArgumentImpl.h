/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateArgument.h"
#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgumentImpl.h"

namespace rfk
{
	class NonTypeTemplateArgument::NonTypeTemplateArgumentImpl : public TemplateArgument::TemplateArgumentImpl
	{
		private:
			/** Archetype of the argument value. */
			Archetype const*	_valueArchetype;
			
			/** Pointer to the argument value. */
			void const*			_valuePtr;

		public:
			inline NonTypeTemplateArgumentImpl(Archetype const*	valueArchetype,
											   void const*		valuePtr)		noexcept;

			/**
			*	@brief Getter for the field _valueArchetype.
			* 
			*	@return _valueArchetype.
			*/
			RFK_NODISCARD inline Archetype const*	getArchetype()	const	noexcept;

			/**
			*	@brief Getter for the field _valuePtr.
			* 
			*	@return _valuePtr.
			*/
			RFK_NODISCARD inline void const*		getValuePtr()	const	noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateArgumentImpl.inl"
}