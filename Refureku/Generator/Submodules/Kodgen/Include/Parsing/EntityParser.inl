
inline ParsingContext& EntityParser::getContext() noexcept
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