/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"

namespace rfk
{
	class ClassTemplateInstantiation;	//Forward declaration

	class ClassTemplateInstantiationRegisterer
	{
		private:
			/** Registered archetype. */
			ClassTemplateInstantiation const& _registeredClassTemplateInstantiation;

		public:
			REFUREKU_API ClassTemplateInstantiationRegisterer(ClassTemplateInstantiation const& classTemplateInstance)	noexcept;
			ClassTemplateInstantiationRegisterer(ClassTemplateInstantiationRegisterer const&)							= delete;
			ClassTemplateInstantiationRegisterer(ClassTemplateInstantiationRegisterer&&)								= delete;
			REFUREKU_API ~ClassTemplateInstantiationRegisterer()														noexcept;


			ClassTemplateInstantiationRegisterer& operator=(ClassTemplateInstantiationRegisterer const&)	= delete;
			ClassTemplateInstantiationRegisterer& operator=(ClassTemplateInstantiationRegisterer&&)			= delete;
	};
}