
inline MethodParsingResult* MethodParser::getParsingResult() noexcept
{
	return reinterpret_cast<MethodParsingResult*>(getContext().parsingResult);
}