#pragma once

#include "TypeInfo/Fields/FieldBase.h"
#include "TypeInfo/Type.h"

namespace refureku
{
	class StaticField : public FieldBase
	{
		private:
			void*	ptrToData	= nullptr;

		public:
			StaticField()																	= delete;
			StaticField(std::string&&		name,
						uint64				id				= 0u,
						EAccessSpecifier	access			= EAccessSpecifier::Undefined,
						Struct const*		ownerStruct		= nullptr,
						Struct const*		introducedBy	= nullptr,
						void*				ptrToData		= nullptr)						noexcept;
			StaticField(StaticField const&)													= default;
			StaticField(StaticField&&)														= default;
			~StaticField()																	= default;

			StaticField& operator=(StaticField const&)	= default;
			StaticField& operator=(StaticField&&)		= default;
	};
}