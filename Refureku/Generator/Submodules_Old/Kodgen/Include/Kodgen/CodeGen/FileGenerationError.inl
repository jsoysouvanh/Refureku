/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline std::string const& FileGenerationError::getFilename() const noexcept
{
	return _filename;
}

inline std::string const& FileGenerationError::getEntityName() const noexcept
{
	return _entityName;
}

inline std::string const& FileGenerationError::getDescription() const noexcept
{
	return _description;
}

inline std::string FileGenerationError::toString() const noexcept
{
	return "Error: " + _filename  + " -> " + _entityName + ": " + _description;
}