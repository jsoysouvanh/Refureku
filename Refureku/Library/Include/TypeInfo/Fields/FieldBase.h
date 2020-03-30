#pragma once

#include "TypeInfo/Entity.h"
#include "TypeInfo/EAccessSpecifier.h"
#include "TypeInfo/Type.h"
#include "TypeInfo/Fields/EFieldFlags.h"

namespace rfk
{
	class Struct;	//Forward declaration

	class FieldBase : public Entity
	{
		public:
			/** Flags describing this field */
			EFieldFlags			flags	= EFieldFlags::Default;

			/** Type of this field */
			Type				type;
			
			/** Struct this field belongs to */
			Struct const*		ownerStruct;

			/** Struct which declared this field */
			Struct const*		introducedBy;

			FieldBase()																	= delete;
			FieldBase(std::string&&		name,
					  uint64			id				= 0u,
					  EFieldFlags		flags			= EFieldFlags::Default,
					  Struct const*		ownerStruct		= nullptr,
					  Struct const*		introducedBy	= nullptr)						noexcept;
			FieldBase(FieldBase const&)													= default;
			FieldBase(FieldBase&&)														= default;
			~FieldBase()																= default;

			/** Get access of this field */
			EAccessSpecifier	getAccess()		const	noexcept;

			FieldBase& operator=(FieldBase const&)	= default;
			FieldBase& operator=(FieldBase&&)		= default;
	};
}