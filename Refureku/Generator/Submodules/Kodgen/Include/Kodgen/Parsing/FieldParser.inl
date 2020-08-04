
inline FieldParsingResult* FieldParser::getParsingResult() noexcept
{
	return reinterpret_cast<FieldParsingResult*>(getContext().parsingResult);
}