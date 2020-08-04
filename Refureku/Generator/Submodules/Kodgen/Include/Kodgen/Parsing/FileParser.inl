
inline FileParsingResult* FileParser::getParsingResult() noexcept
{
	return reinterpret_cast<FileParsingResult*>(getContext().parsingResult);
}