/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

namespace rfk
{
	class ICallable
	{
		public:
			//Must be virtual because MemberFunction and NonMemberFunction instances are stored and deleted as SharedPtr<ICallable>
			virtual	~ICallable() = default;

		protected:
			ICallable()					= default;
			ICallable(ICallable const&)	= default;
			ICallable(ICallable&&)		= default;
	};
}