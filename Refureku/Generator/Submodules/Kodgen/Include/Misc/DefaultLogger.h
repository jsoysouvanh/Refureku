/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Misc/ILogger.h"

namespace kodgen
{
	class DefaultLogger : public ILogger
	{
		protected:
			virtual void logInfo(std::string const& message)	noexcept;
			virtual void logWarning(std::string const& message) noexcept;
			virtual void logError(std::string const& message)	noexcept;

		public:
			DefaultLogger()						= default;
			DefaultLogger(DefaultLogger const&)	= default;
			DefaultLogger(DefaultLogger&&)		= default;
			~DefaultLogger()					= default;

			virtual void log(std::string const&	message,
							 ELogSeverity		logSeverity)	noexcept override;

			DefaultLogger& operator=(DefaultLogger const&)	= default;
			DefaultLogger& operator=(DefaultLogger&&)		= default;
	};
}