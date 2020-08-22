/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline std::string GeneratedEntityCodeTemplate::getEntityId(kodgen::EntityInfo const& entity) noexcept
{
	return std::to_string(GeneratedEntityCodeTemplate::stringHasher(entity.id)) + "u";
}