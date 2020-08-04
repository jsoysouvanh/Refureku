
inline EnumParsingResult* EnumParser::getParsingResult() noexcept
{
	return reinterpret_cast<EnumParsingResult*>(getContext().parsingResult);
}