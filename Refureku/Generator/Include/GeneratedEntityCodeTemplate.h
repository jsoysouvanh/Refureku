#pragma once

#include <CodeGen/GeneratedCodeTemplate.h>
#include <InfoStructures/EntityInfo.h>

namespace rfk
{
	class GeneratedEntityCodeTemplate : public kodgen::GeneratedCodeTemplate
	{
		protected:
			static constexpr char const*	_internalPrefix = "__RFK";
			static constexpr char const*	_externalPrefix = "RFK";
			static std::hash<std::string>	_stringHasher;

			std::string	fillEntityProperties(kodgen::EntityInfo const& info, std::string const& entityVarName)	const	noexcept;
	};
}
