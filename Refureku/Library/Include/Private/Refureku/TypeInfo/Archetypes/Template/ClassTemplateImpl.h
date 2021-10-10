/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>

#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplate.h"
#include "Refureku/TypeInfo/Archetypes/StructImpl.h"
#include "Refureku/TypeInfo/Archetypes/Template/TemplateParameter.h"
#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiation.h"

namespace rfk
{
	class ClassTemplate::ClassTemplateImpl final : public Struct::StructImpl
	{
		private:
			/** List of all template parameters of this class template. */
			std::vector<TemplateParameter const*>			_templateParameters;
			
			/** All different instantiations of this class template in the program (with different template parameters). */
			std::vector<ClassTemplateInstantiation const*>	_templateInstantiations;

		public:
			inline ClassTemplateImpl(char const*	name,
									 std::size_t	id,
									 bool			isClass)	noexcept;

			/**
			*	@brief Add an template instantiation to _instantiations.
			* 
			*	@param instantiation Template instantiation to add to _templateInstantiations.
			*/
			inline void																addTemplateInstantiation(ClassTemplateInstantiation const& instantiation)	noexcept;

			/**
			*	@brief Append a template parameter to _templateParameters.
			* 
			*	@param param Template parameter to add to _templateParameters.
			*/
			inline void																addTemplateParameter(TemplateParameter const& param)							noexcept;

			/**
			*	@brief Getter for the field _templateParameters.
			* 
			*	@return _templateParameters.
			*/
			RFK_NODISCARD inline std::vector<TemplateParameter const*> const&			getTemplateParameters()													const	noexcept;

			/**
			*	@brief Getter for the field _templateInstantiations.
			* 
			*	@return _templateInstantiations.
			*/
			RFK_NODISCARD inline std::vector<ClassTemplateInstantiation const*> const&	getTemplateInstantiations()												const	noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateImpl.inl"
}