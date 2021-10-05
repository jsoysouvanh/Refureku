/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline std::string ReflectionCodeGenModule2::getEntityId(kodgen::EntityInfo const& entity) noexcept
{
	return std::to_string(ReflectionCodeGenModule2::_stringHasher(entity.id)) + "u";
}