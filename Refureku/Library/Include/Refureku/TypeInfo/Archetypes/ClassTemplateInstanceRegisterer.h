/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

namespace rfk
{
	class ClassTemplateInstance;	//Forward declaration

	class ClassTemplateInstanceRegisterer
	{
		private:
			/** Registered archetype. */
			ClassTemplateInstance const& _registeredClassTemplateInstance;

		public:
			ClassTemplateInstanceRegisterer()													= delete;
			ClassTemplateInstanceRegisterer(ClassTemplateInstance const& classTemplateInstance)	noexcept;
			ClassTemplateInstanceRegisterer(ClassTemplateInstanceRegisterer const&)				= delete;
			ClassTemplateInstanceRegisterer(ClassTemplateInstanceRegisterer&&)					= delete;
			~ClassTemplateInstanceRegisterer()													noexcept;

			ClassTemplateInstanceRegisterer& operator=(ClassTemplateInstanceRegisterer const&)	= delete;
			ClassTemplateInstanceRegisterer& operator=(ClassTemplateInstanceRegisterer&&)		= delete;
	};
}