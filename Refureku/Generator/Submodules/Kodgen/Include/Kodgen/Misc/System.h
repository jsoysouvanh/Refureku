/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

namespace kodgen
{
	class System
	{
		public:
			System()				= delete;
			System(System const&)	= delete;
			System(System&&)		= delete;
			~System()				= delete;

			/**
			*	@brief Execute a command on the system.
			*	
			*	@param cmd The command to run.
			*	
			*	@return The result of the given command.
			*/
			static std::string executeCommand(std::string const& cmd);
	};
}