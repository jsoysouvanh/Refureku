#pragma once

#include <stack>
#include <cassert>
#include <clang-c/Index.h>

#include "Misc/FundamentalTypes.h"
#include "Parsing/ParsingContext.h"

namespace kodgen
{
	class EntityParser
	{
		protected:
			/** Stack of contexts of this parser. */
			std::stack<ParsingContext>	contextsStack;

			/**
			*	@brief Get the current in-use context.
			*
			*	@return The current context.
			*/
			inline ParsingContext&	getContext()	noexcept;

			/**
			*	@brief Pop the most recent context from the contexts stack.
			*/
			inline void				popContext()	noexcept;

		public:
			EntityParser()						= default;
			EntityParser(EntityParser const&)	= default;
			EntityParser(EntityParser&&)		= default;
			~EntityParser()						= default;
	};

	#include "Parsing/EntityParser.inl"
}