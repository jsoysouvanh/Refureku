
inline ClassParsingResult* ClassParser::getParsingResult() noexcept
{
	return reinterpret_cast<ClassParsingResult*>(getContext().parsingResult);
}