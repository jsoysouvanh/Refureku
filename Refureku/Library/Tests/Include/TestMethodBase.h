/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Generated/TestMethodBase.rfkh.h"

__RFK_DISABLE_WARNING_PUSH
__RFK_DISABLE_WARNING_MISSING_OVERRIDE
__RFK_DISABLE_WARNING_UNDEFINED_INLINE

class CLASS() TestMethodBaseClass
{
	private:
		METHOD()
		void constMethod() const noexcept;

	protected:
		METHOD()
		static void staticMethod() noexcept { }

		METHOD()
		virtual void virtualMethod() noexcept { staticMethod(); }

		METHOD()
		virtual void virtualMethod2() noexcept { }

		METHOD()
		virtual void pureVirtualMethod() noexcept = 0;

		METHOD()
		virtual void pureVirtualMethod2() noexcept = 0;

	public:
		METHOD()
		inline void inlineMethodInHeader() noexcept { }

		METHOD()
		inline void inlineMethodInSource() noexcept;

		METHOD()
		void funcWithParams1(int, int, int) const { constMethod(); }
		
		METHOD()
		void funcWithParams2(int, int, int) const { }
		
		METHOD()
		void funcWithParams3(int, int, int) { }

		METHOD()
		char funcWithParams4(int, int, int) const { return ' '; }

		METHOD()
		void funcWithParams5(int, int, float) const { }

	TestMethodBaseClass_GENERATED
};

class CLASS() TestMethodBaseClassChild : public TestMethodBaseClass
{
	public:
		METHOD()
		/* virtual */ void virtualMethod() noexcept override { TestMethodBaseClass::virtualMethod(); }

		METHOD()
		/* virtual */ void virtualMethod2() noexcept /* override */ { TestMethodBaseClass::virtualMethod2(); }

		METHOD()
		/* virtual */ void pureVirtualMethod() noexcept override final { };

		METHOD()
		/* virtual */ void pureVirtualMethod2() noexcept /* override */ { };

	TestMethodBaseClassChild_GENERATED
};

class CLASS() TestMethodBaseClassChild2 final : public TestMethodBaseClassChild
{
	private:
		METHOD()
		/* virtual */ void virtualMethod() noexcept override { TestMethodBaseClassChild::virtualMethod(); }

		METHOD()
		/* virtual */ void virtualMethod2() noexcept /* override */ { TestMethodBaseClassChild::virtualMethod2(); }

		METHOD()
		/* virtual */ void pureVirtualMethod2() noexcept /* override */ { TestMethodBaseClassChild::pureVirtualMethod2(); };

	TestMethodBaseClassChild2_GENERATED
};

__RFK_DISABLE_WARNING_POP

File_TestMethodBase_GENERATED