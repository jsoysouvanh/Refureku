/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Kodgen/Misc/ILogger.h"

namespace kodgen
{
	class DefaultLogger : public ILogger
	{
		protected:
			/** 
			*	@brief Log an info message.
			*	
			*	@param message Message to log.
			*/
			virtual void logInfo(std::string const& message)	noexcept;

			/** 
			*	@brief Log a warning message.
			*	
			*	@param message Message to log.
			*/
			virtual void logWarning(std::string const& message) noexcept;
			
			/** 
			*	@brief Log an error message.
			*	
			*	@param message Message to log.
			*/
			virtual void logError(std::string const& message)	noexcept;

		public:
			DefaultLogger()						= default;
			DefaultLogger(DefaultLogger const&)	= default;
			DefaultLogger(DefaultLogger&&)		= default;
			virtual ~DefaultLogger()			= default;

			virtual void log(std::string const&	message,
							 ELogSeverity		logSeverity = ELogSeverity::Info)	noexcept override;
	};
}