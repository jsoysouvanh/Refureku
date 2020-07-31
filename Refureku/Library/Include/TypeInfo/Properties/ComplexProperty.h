/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>

#include "TypeInfo/Properties/SimpleProperty.h"
#include "Exceptions/TypeMismatch.h"
#include "Exceptions/OutOfRange.h"
#include "Misc/FundamentalTypes.h"

namespace rfk
{
	class ComplexProperty : public SimpleProperty
	{
		public:
			/** Collection of all subproperties. */
			std::vector<std::string>	subProperties;

			ComplexProperty()											= default;
			ComplexProperty(std::string					mainProperty,
							std::vector<std::string>	subProperties)	noexcept;
			ComplexProperty(ComplexProperty const&)						= default;
			ComplexProperty(ComplexProperty&&)							= default;
			~ComplexProperty()											= default;

			/**
			*	@brief Check that this complex property contains a specific subproperty.
			*	
			*	@param name Name of the subproperty to check for.
			*
			*	@return true if this subproperty is contained in the complex property, else false.
			*/
			bool		containsSubproperty(std::string const& name)	const noexcept;

			/**
			*	@brief Try to get the subproperty at the provided index as an int32.
			*	
			*	@param index Index of the subproperty to retrieve (starts at 0).
			*
			*	@return The cast int32 on success. On failure, an exception is thrown.
			*	
			*	@exception OutOfRange is thrown if the provided index is out of the bounds of the subProperties vector.
			*	@exception TypeMismatch is thrown if the subproperties at the provided index could not be casted as an int32.
			*/
			int32		getInt32(size_t index)							const;

			/**
			*	@brief Try to get the subproperty at the provided index as an uint32.
			*	
			*	@param index Index of the subproperty to retrieve (starts at 0).
			*
			*	@return The cast uint32 on success. On failure, an exception is thrown.
			*	
			*	@exception OutOfRange is thrown if the provided index is out of the bounds of the subProperties vector.
			*	@exception TypeMismatch is thrown if the subproperties at the provided index could not be casted as an uint32.
			*/
			uint32		getUint32(size_t index)							const;

			/**
			*	@brief Try to get the subproperty at the provided index as a float.
			*	
			*	@param index Index of the subproperty to retrieve (starts at 0).
			*
			*	@return The cast float on success. On failure, an exception is thrown.
			*	
			*	@exception OutOfRange is thrown if the provided index is out of the bounds of the subProperties vector.
			*	@exception TypeMismatch is thrown if the subproperties at the provided index could not be casted as a float.
			*/
			float		getFloat(size_t index)							const;

			/**
			*	@brief Try to get the subproperty at the provided index as a string.
			*			This method actually strips the first and last " character.
			*	
			*	@param index Index of the subproperty to retrieve (starts at 0).
			*
			*	@return The cast string on success. On failure, an exception is thrown.
			*	
			*	@exception OutOfRange is thrown if the provided index is out of the bounds of the subProperties vector.
			*	@exception TypeMismatch is thrown if the subproperties at the provided index was not starting and/or finishing with ".
			*/
			std::string getString(size_t index)							const;
	};
}