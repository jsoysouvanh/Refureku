
inline EnumValueParsingResult* EnumValueParser::getParsingResult() noexcept
{
	return reinterpret_cast<EnumValueParsingResult*>(getContext().parsingResult);
}