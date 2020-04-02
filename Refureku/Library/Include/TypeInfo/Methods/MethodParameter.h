#pragma once

#include <string>

#include "TypeInfo/Type.h"

namespace rfk
{
	class MethodParameter
	{
		public:
			/** Name of this parameter. Can be unspecified (empty). */
			std::string	name;

			/** Type of this parameter */
			Type		type;

			MethodParameter()									= default;
			MethodParameter(std::string&& name, Type&& type)	noexcept;
			MethodParameter(MethodParameter const&)				= default;
			MethodParameter(MethodParameter&&)					= default;
			~MethodParameter()									= default;

			MethodParameter& operator=(MethodParameter const&)	= default;
			MethodParameter& operator=(MethodParameter&&)		= default;
	};
}