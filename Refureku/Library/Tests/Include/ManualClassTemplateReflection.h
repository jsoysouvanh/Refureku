/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <vector>

#include "Generated/ManualClassTemplateReflection.rfkh.h"

template <typename T>
class CLASS() Vector : public std::vector<T>
{
	public:
		METHOD()
		void push_back(T const& elem)
		{
			std::vector<T>::push_back(elem);
		}

		METHOD()
		void push_back(T&& elem)
		{
			std::vector<T>::push_back(std::forward<T>(elem));
		}

		METHOD()
		void resize(std::size_t newSize)
		{
			std::vector<T>::resize(newSize);
		}

		METHOD()
		std::size_t size() const
		{
			return std::vector<T>::size();
		}

		METHOD()
		T& operator[](std::size_t index)
		{
			return std::vector<T>::operator[](index);
		}

	Vector_GENERATED
};

template <typename T>
class CLASS() VectorDerived : public Vector<T>
{
	VectorDerived_GENERATED
};

File_ManualClassTemplateReflection_GENERATED