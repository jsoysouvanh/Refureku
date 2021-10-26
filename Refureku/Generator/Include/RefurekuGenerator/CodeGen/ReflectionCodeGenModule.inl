/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline std::string ReflectionCodeGenModule::getEntityId(kodgen::EntityInfo const& entity) noexcept
{
	return std::to_string(ReflectionCodeGenModule::_stringHasher(entity.id)) + "u";
}