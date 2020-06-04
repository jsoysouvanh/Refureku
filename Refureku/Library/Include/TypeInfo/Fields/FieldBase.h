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

			/** Struct which contains the declaration of this field */
			Struct const*		introducedBy;

			FieldBase()															= delete;
			FieldBase(std::string&&		name,
					  uint64			id				= 0u,
					  EFieldFlags		flags			= EFieldFlags::Default,
					  Struct const*		ownerStruct		= nullptr,
					  Struct const*		introducedBy	= nullptr)				noexcept;
			FieldBase(FieldBase const&)											= default;
			FieldBase(FieldBase&&)												= default;
			~FieldBase()														= default;

			/**
			*	\return The access specifier of this method in its owner struct/class.
			*/
			EAccessSpecifier	getAccess()		const	noexcept;

			FieldBase& operator=(FieldBase const&)	= default;
			FieldBase& operator=(FieldBase&&)		= default;
	};
}