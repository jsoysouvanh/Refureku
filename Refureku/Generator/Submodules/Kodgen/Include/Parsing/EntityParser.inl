
inline bool EntityParser::shouldParseCurrentEntity() const noexcept
{
	ParsingContext const& context = getContext();

	return context.parsingSettings->shouldParseAllEntities || (context.parentContext != nullptr && context.parentContext->shouldParseAllNested);
}

inline ParsingContext& EntityParser::getContext() noexcept
{
	//Can't retrieve the context if there is none.
	assert(!contextsStack.empty());

	return contextsStack.top();
}

inline ParsingContext const& EntityParser::getContext() const noexcept
{
	//Can't retrieve the context if there is none.
	assert(!contextsStack.empty());

	return contextsStack.top();
}

inline void EntityParser::popContext() noexcept
{
	assert(!contextsStack.empty());

	contextsStack.pop();
}