#pragma once

#include <string>

#include "Misc/FundamentalTypes.h"

namespace kodgen
{
	class ILogger
	{
		public:
			enum class ELogSeverity : uint8
			{
				Info = 0,
				Warning,
				Error
			};

			ILogger()				= default;
			ILogger(ILogger const&)	= default;
			ILogger(ILogger&&)		= default;
			~ILogger()				= default;

			virtual void log(std::string const& message, ELogSeverity logSeverity) noexcept = 0;

			ILogger& operator=(ILogger const&)	= default;
			ILogger& operator=(ILogger&&)		= default;
	};
}