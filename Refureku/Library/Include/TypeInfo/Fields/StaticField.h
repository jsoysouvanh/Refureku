#pragma once

#include <cassert>
#include <type_traits>
#include <cstring>	//std::memcpy
#include <utility>	//std::forward

#include "TypeInfo/Fields/FieldBase.h"
#include "TypeInfo/Type.h"

namespace rfk
{
	class StaticField : public FieldBase
	{
		private:
			void*	dataAddress	= nullptr;

		public:
			StaticField()																	= delete;
			StaticField(std::string&&		name,
						uint64				id				= 0u,
						EFieldFlags			flags			= EFieldFlags::Static,
						Struct const*		ownerStruct		= nullptr,
						Struct const*		introducedBy	= nullptr,
						void*				ptrToData		= nullptr)						noexcept;
			StaticField(StaticField const&)													= default;
			StaticField(StaticField&&)														= default;
			~StaticField()																	= default;

			/**
			*	Get the data corresponding to this field in the provided instance
			*/
			template <typename DataType>
			DataType		getData()									const noexcept;

			/**
			*	Set the data corresponding to this field in the provided instance
			*	This method is not safe if you provided a wrong typed data
			*/
			template <typename DataType>
			void			setData(DataType&& data)					const noexcept;

			/**
			*	Get the data address corresponding to this static field
			*/
			inline void*	getDataAddress()							const noexcept;

			/**
			*	Copy dataSize bytes starting from data into the field
			*/
			inline void		setData(void const* data, uint64 dataSize)	const noexcept;

			StaticField& operator=(StaticField const&)	= default;
			StaticField& operator=(StaticField&&)		= default;
	};

	#include "TypeInfo/Fields/StaticField.inl"
}