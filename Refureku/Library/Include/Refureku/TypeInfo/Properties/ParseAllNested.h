/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/Properties/Property.h"
#include "Refureku/TypeInfo/Properties/PropertySettings.h"

#include "Refureku/Generated/ParseAllNested.rfkh.h"

/**
*	@brief	Property used to automatically tag all directly nested entities as reflected.
*			This property can only be attached to namespaces, structs and classes.
*/
struct RFKStruct(PropertySettings(rfk::EEntityKind::Namespace | rfk::EEntityKind::Class | rfk::EEntityKind::Struct)) ParseAllNested : public rfk::Property
{
	public:
		REFUREKU_API virtual ~ParseAllNested() noexcept;

	ParseAllNested_GENERATED
};

File_ParseAllNested_GENERATED