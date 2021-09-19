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
	class ClassTemplateInstance;	//Forward declaration

	class ClassTemplateInstanceRegisterer
	{
		private:
			/** Registered archetype. */
			ClassTemplateInstance const& _registeredClassTemplateInstance;

		public:
			REFUREKU_API ClassTemplateInstanceRegisterer(ClassTemplateInstance const& classTemplateInstance)	noexcept;
			REFUREKU_API ~ClassTemplateInstanceRegisterer()														noexcept;

			ClassTemplateInstanceRegisterer(ClassTemplateInstanceRegisterer const&)				= delete;
			ClassTemplateInstanceRegisterer(ClassTemplateInstanceRegisterer&&)					= delete;

			ClassTemplateInstanceRegisterer& operator=(ClassTemplateInstanceRegisterer const&)	= delete;
			ClassTemplateInstanceRegisterer& operator=(ClassTemplateInstanceRegisterer&&)		= delete;
	};
}