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
		bool	_defaultConstructed	= false;
		bool	_copyConstructed	= false;
		bool	_moveConstructed	= false;

	public:
		ConstructionTrackedClass():
			_defaultConstructed{true}
		{
		}

		ConstructionTrackedClass(ConstructionTrackedClass const&):
			_copyConstructed{true}
		{
		}

		ConstructionTrackedClass(ConstructionTrackedClass&&):
			_moveConstructed{true}
		{
		}

		ConstructionTrackedClass& operator=(ConstructionTrackedClass const&)
		{
			_defaultConstructed = false;
			_moveConstructed = false;

			_copyConstructed = true;

			return *this;
		}

		ConstructionTrackedClass& operator=(ConstructionTrackedClass&&)
		{
			_defaultConstructed = false;
			_copyConstructed = false;

			_moveConstructed = true;

			return *this;
		}

		inline bool getDefaultConstructed() const noexcept { return _defaultConstructed; }
		inline bool getCopyConstructed() const noexcept { return _copyConstructed; }
		inline bool getMoveConstructed() const noexcept { return _moveConstructed; }

	ConstructionTrackedClass_GENERATED
};

File_ConstructionTrackedClass_GENERATED