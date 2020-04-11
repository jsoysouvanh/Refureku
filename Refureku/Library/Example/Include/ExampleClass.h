#pragma once

#include <vector>

#include "ReflectedObject.h"

#include "Generated/ExampleClass.rfk.h"

namespace namespace1
{
	/** Non reflected class */
	class ParentParentParentClass
	{
		double pppDouble = 0.21;

		public:
		ParentParentParentClass() noexcept {}
	};
}

namespace namespace2
{
	class RFKClass(rfk::ReflectedObject) ParentParentClass : public namespace1::ParentParentParentClass, public rfk::ReflectedObject
	{
		RFKField()
		float ppFloat = 123456.123456f;

		RFKField()
		std::vector<ParentParentParentClass> vec; 

		public:
			ParentParentClass() noexcept {}

		RFKParentParentClass_GENERATED
	};
}

namespace namespace3
{
	class RFKClass(rfk::ReflectedObject) OtherClass : public rfk::ReflectedObject
	{
		RFKOtherClass_GENERATED
	};

	class RFKClass(rfk::ReflectedObject) ParentClass : public namespace2::ParentParentClass
	{
		private:
			RFKMethod()
			void parentClassMethod1() noexcept { };

		public:
			RFKField()
			uint64_t pInt64 = 666;

			RFKMethod()
			virtual void method1() const { };

			ParentClass()					noexcept { }
			ParentClass(ParentClass const&)	= default;
			ParentClass(ParentClass&& o)	= default;

		RFKParentClass_GENERATED
	};
	
	std::ostream& operator<<(std::ostream& stream, ParentClass const& object) noexcept;

	class RFKClass() ParentClass2
	{
		RFKField()
		char p2Char = '*';

		public:
			ParentClass2() noexcept { }

		RFKParentClass2_GENERATED
	};

	class RFKClass(rfk::ReflectedObject) ExampleClass : public ParentClass, public ParentClass2
	{
		public:
			RFKField()
			static inline int	someStaticInt = 69;

			RFKField()
			static inline ParentClass	someStaticParentClass;

			RFKField()
			mutable int		someInt			= 42;

			RFKField()
			int				p2Char			= 2;

			RFKField()
			ParentClass		someParentClass;

			RFKField()
			int*			somePtrToInt	= nullptr;

			RFKField()
			float			someFloat		= 42.42f;

			RFKField()
			float const*	a				= nullptr;

			RFKField()
			float * const	b				= nullptr;

			RFKField()
			int const* c[2][3]				= {{}};

			RFKMethod(CustomInstantiator)
			unsigned long long		method4(void* ptr);

			RFKMethod()
			virtual void	method1() const noexcept override;

		protected:
			RFKMethod()
			void			method2() const;

			RFKMethod()
			int				method3();

			RFKMethod()
			static	int		staticMethod3(char const* param);

			RFKMethod()
			static	ExampleClass const* staticMethod4(char const*) noexcept { return nullptr; };

		private:
			RFKMethod()
			static	int		staticMethod2();

			RFKMethod()
			static void		staticMethod1();

			RFKMethod()
			static	int		staticMethod3(int p1, int p2)	noexcept;

			RFKMethod()
			float			method3(int i)				noexcept;

			RFKMethod()
			float			methodWithDefaultArgs(int i = 0, float f = 3.14f, char const* s = "test");

		public:
			ExampleClass()						noexcept { }
			ExampleClass(ExampleClass const&)	= default;
			ExampleClass(ExampleClass&&)		= default;
			~ExampleClass()						= default;

		RFKExampleClass_GENERATED
	};

	enum class RFKEnum() ExampleEnum : uint8_t
	{
		ExampleValue1 = 1 << 0,
		ExampleValue2 = 1 << 1,
		ExampleValue3 = 1 << 2,
		ExampleValue4 = 1 << 3,
		ExampleValue5 = 1 << 3
	};
}

RFKExampleEnum_GENERATED