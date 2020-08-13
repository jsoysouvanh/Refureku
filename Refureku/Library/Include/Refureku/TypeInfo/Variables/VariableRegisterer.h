/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

namespace rfk
{
	//Forward declaration
	class Variable;

	class VariableRegisterer
	{
		private:
			/** Registered variable. */
			Variable const* _registeredVariable = nullptr;

		public:
			VariableRegisterer()							= delete;
			VariableRegisterer(Variable const* variable)	noexcept;
			VariableRegisterer(VariableRegisterer const&)	= delete;
			VariableRegisterer(VariableRegisterer&&)		= delete;
			~VariableRegisterer()							noexcept;
	};
}