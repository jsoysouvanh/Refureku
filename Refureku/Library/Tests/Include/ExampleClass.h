#pragma once

#include "ReflectedObject.h"

#include "Generated/ExampleClass.rfk.h"

namespace namespace1
{
	/** Non reflected class */
	class ParentParentParentClass
	{
		private:
			double pppDouble = 0.21;

		public:
			ParentParentParentClass() noexcept {}
	};
}

namespace namespace2 RFKNamespace()
{
	class RFKClass(DynamicGetArchetype) ParentParentClass : public namespace1::ParentParentParentClass, public rfk::ReflectedObject 
	{
		private:
			RFKField(Range[1, 2])
			float ppFloat = 123456.123456f;

		public:
			ParentParentClass() noexcept {} 

		ParentParentClass_GENERATED
	};
}

namespace namespace3 RFKNamespace()
{
	class RFKClass(DynamicGetArchetype) OtherClass : public rfk::ReflectedObject
	{

		OtherClass_GENERATED
	};

	class RFKClass(DynamicGetArchetype) ParentClass : public namespace2::ParentParentClass
	{
		private:
			RFKMethod()
			void parentClassMethod1() noexcept { };

		public:
			RFKField()
			uint64_t pInt64 = 666;

			RFKMethod()
			virtual int method1() const { return 1; };

			ParentClass()					noexcept { }
			ParentClass(ParentClass const&)	= default;
			ParentClass(ParentClass&& o)	= default;

		ParentClass_GENERATED
	};
	
	std::ostream& operator<<(std::ostream& stream, ParentClass const& object) noexcept;

	class RFKClass() ParentClass2
	{
		private:
			RFKField()
			char p2Char = '*';

		public:
			ParentClass2() noexcept { }

		ParentClass2_GENERATED
	};

	class RFKClass(DynamicGetArchetype) ExampleClass : public ParentClass, public ParentClass2
	{
		private:
			class RFKClass() NestedExampleClass
			{
				public:
					RFKField()
					int i = 0;

				NestedExampleClass_GENERATED 
			};
		
		protected:
			struct RFKStruct() NestedExampleStruct 
			{
				public:
					RFKMethod()
					void foo() { }

				NestedExampleStruct_GENERATED
			};

		public:
			enum class RFKEnum() NestedExampleEnum
			{
				Value1 = 0
			};

			RFKField()
			static inline int	someStaticInt = 314;

			RFKField()
			static inline ParentClass	someStaticParentClass;

			RFKField()
			mutable int		someInt				= 42;

			RFKField()
			int				p2Char				= 2;

			RFKField()
			ParentClass		someParentClass;

			RFKField()
			ParentClass*	ptrToParentClass	= nullptr;

			RFKField()
			int*			somePtrToInt		= nullptr;

			RFKField()
			float			someFloat			= 42.42f;

			RFKField()
			float const*	a					= nullptr;

			RFKField()
			float * const	b					= nullptr;

			RFKField()
			int const*		c[2][3];

			RFKMethod()
			unsigned long long	method4(void* ptr);

			RFKMethod()
			virtual int	method1() const noexcept override final;

			RFKMethod(CustomInstantiator)
			static void*	customInstantiator(int, float) noexcept { return new ExampleClass(); }

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

		public:
			ExampleClass()						noexcept { }
			ExampleClass(ExampleClass const&)	= default;
			ExampleClass(ExampleClass&&)		= default;
			~ExampleClass()						= default;

		ExampleClass_GENERATED
	};

	class RFKClass() ExampleClass2
	{
		RFKMethod(CustomInstantiator)
		static void* customInstantiator(int i) noexcept { return new ExampleClass2(i); }

		ExampleClass2() = delete;
		ExampleClass2(int i) noexcept:
			i{i}
		{};

		public:
			RFKField()
			int i = 0;

		ExampleClass2_GENERATED
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

struct RFKStruct(ParseAllNested) ExampleStruct
{
	RFKField()
	static int staticInt;

	RFKField()
	int i = 2;

	RFKMethod()
	static void staticMethod() { std::cout << "ExampleStruct::staticMethod()" << std::endl; } 

	RFKMethod()
	void method(int a, float b) { std::cout << "ExampleStruct::method(" << a << ", " << b << ")" << std::endl; }

	ExampleStruct_GENERATED
};

namespace parse_all_nested_namespace RFKNamespace(ParseAllNested)
{
	class NestedClass1
	{
		NestedClass1_GENERATED
	};

	struct NestedStruct1
	{
		NestedStruct1_GENERATED
	};

	enum class NestedEnum1
	{
	};

	namespace parse_all_nested_namespace
	{
	}
}

namespace namespace4 RFKNamespace(ParseAllNested)
{
	namespace namespace4_nested
	{
		namespace namespace4_nested_nested RFKNamespace()
		{

		}
	}
}

File_GENERATED