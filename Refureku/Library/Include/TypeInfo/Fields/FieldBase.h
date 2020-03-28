#pragma once

#include "TypeInfo/Entity.h"
#include "TypeInfo/EAccessSpecifier.h"
#include "TypeInfo/Type.h"

namespace refureku
{
	class Struct;	//Forward declaration

	class FieldBase : public Entity
	{
		public:
			/** Accessibility of this field in its owner struct */
			EAccessSpecifier	access = EAccessSpecifier::Undefined;

			/** Type of this field */
			Type				type;
			
			/** Struct this field belongs to */
			Struct const*		ownerStruct;

			/** Struct which declared this field */
			Struct const*		introducedBy;

			FieldBase()																	= delete;
			FieldBase(std::string&&		name,
					  uint64			id				= 0u,
					  EAccessSpecifier	access			= EAccessSpecifier::Undefined,
					  Struct const*		ownerStruct		= nullptr,
					  Struct const*		introducedBy	= nullptr)						noexcept;
			FieldBase(FieldBase const&)													= default;
			FieldBase(FieldBase&&)														= default;
			~FieldBase()																= default;

			FieldBase& operator=(FieldBase const&)	= default;
			FieldBase& operator=(FieldBase&&)		= default;
	};
}