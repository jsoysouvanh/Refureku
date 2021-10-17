/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Generated/ConstructionTrackedClass.rfkh.h"

class CLASS() ConstructionTrackedClass
{
	private:
		int		_value				= 0;
		bool	_defaultConstructed	= false;
		bool	_copyConstructed	= false;
		bool	_moveConstructed	= false;

	public:
		ConstructionTrackedClass():
			_defaultConstructed{true}
		{
		}

		ConstructionTrackedClass(int i) noexcept:
			_value{i},
			_defaultConstructed{true}
		{
		}

		ConstructionTrackedClass(ConstructionTrackedClass const& other):
			_copyConstructed{true},
			_value{other._value}
		{
		}

		ConstructionTrackedClass(ConstructionTrackedClass&& other):
			_moveConstructed{true},
			_value{std::move(other._value)}
		{
		}

		ConstructionTrackedClass& operator=(ConstructionTrackedClass const& other)
		{
			_defaultConstructed = false;
			_moveConstructed = false;

			_copyConstructed = true;
			_value = other._value;

			return *this;
		}

		ConstructionTrackedClass& operator=(ConstructionTrackedClass&& other)
		{
			_defaultConstructed = false;
			_copyConstructed = false;

			_moveConstructed = true;
			_value = std::move(other._value);

			return *this;
		}

		inline bool getDefaultConstructed() const noexcept { return _defaultConstructed; }
		inline bool getCopyConstructed() const noexcept { return _copyConstructed; }
		inline bool getMoveConstructed() const noexcept { return _moveConstructed; }
		inline int	getValue() const noexcept { return _value; }

	ConstructionTrackedClass_GENERATED
};

File_ConstructionTrackedClass_GENERATED