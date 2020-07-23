
inline NamespaceParsingResult* NamespaceParser::getParsingResult() noexcept
{
	return reinterpret_cast<NamespaceParsingResult*>(getContext().parsingResult);
}