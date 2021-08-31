#pragma once

#include <Refureku/NativeProperties.h>
#include <Refureku/Object.h>

#include "Vector3.h"

#include "Generated/ExampleClass.rfkh.h"

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
	class RFKClass() ParentParentClass : public namespace1::ParentParentParentClass, public rfk::Object 
	{
		private:
			RFKField()
			float ppFloat = 123456.123456f;

		public:
			ParentParentClass() noexcept {} 

		namespace2_ParentParentClass_GENERATED
	};
}

namespace namespace3 RFKNamespace(ParseAllNested)
{
	//Forward declaration
	//class AnotherClassInNamespace3;

	class RFKClass() OtherClass : public rfk::Object
	{
		namespace3_OtherClass_GENERATED
	};

	class RFKClass() ParentClass : public namespace2::ParentParentClass
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

		namespace3_ParentClass_GENERATED
	};
	
	std::ostream& operator<<(std::ostream& stream, ParentClass const& object) noexcept;

	class RFKClass() ParentClass2
	{
		private:
			RFKField()
			char p2Char = '*';

		public:
			ParentClass2() noexcept { }

		namespace3_ParentClass2_GENERATED
	};

	class RFKClass() ExampleClass : public ParentClass, public ParentClass2
	{
		private:
			class RFKClass() NestedExampleClass
			{
				public:
					RFKField()
					int i = 0;

				namespace3_ExampleClass_NestedExampleClass_GENERATED
			};
		
		protected:
			struct RFKStruct() NestedExampleStruct 
			{
				public:
					RFKMethod()
					void foo() { }

				namespace3_ExampleClass_NestedExampleStruct_GENERATED
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

			RFKField()
			Vector3f		vec3;

			RFKField()
			Vector3f const*	vec3ptr				= nullptr;

			RFKMethod()
			unsigned long long	method4(void* ptr);

			RFKMethod()
			virtual int	method1() const noexcept override final;

			RFKMethod(CustomInstantiator)
			static ExampleClass* customInstantiator(int, float) noexcept { return new ExampleClass(); }

			RFKMethod(CustomInstantiator)
			static ExampleClass* replaceDefaultInstantiator() noexcept
			{
				ExampleClass* result = new ExampleClass();

				result->someInt = 1;	//Change default value

				return result;
			}

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
			int				method3(int i)					noexcept;

			RFKMethod()
			int				method3(int i)			const	noexcept;

			RFKMethod()
			void			constMethod(int i)		const	noexcept;

		public:
			ExampleClass()						noexcept: c{nullptr} {}
			ExampleClass(ExampleClass const&)	= default;
			ExampleClass(ExampleClass&&)		= default;
			~ExampleClass()						= default;

			RFKMethod()
			void	methodWithClassParam(ParentClass pc) {}

			//RFKMethod()
			//void	methodWithForwardDeclaredParam(AnotherClassInNamespace3*) {}

		namespace3_ExampleClass_GENERATED
	};

	class RFKClass() ExampleClass2
	{
		RFKMethod(CustomInstantiator)
		static ExampleClass2* customInstantiator(int i) noexcept { return new ExampleClass2(i); }

		ExampleClass2() = delete;
		ExampleClass2(int i) noexcept:
			i{i}
		{};

		public:
			RFKField()
			int i = 0;

		namespace3_ExampleClass2_GENERATED
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
	static int staticInt;

	int i = 2;

	static void staticMethod() { std::cout << "ExampleStruct::staticMethod()" << std::endl; } 

	void method(int a, float b) { std::cout << "ExampleStruct::method(" << a << ", " << b << ")" << std::endl; }

	ExampleStruct_GENERATED
};

namespace parse_all_nested_namespace RFKNamespace(ParseAllNested) 
{
	class NestedClass1
	{
		parse_all_nested_namespace_NestedClass1_GENERATED
	};

	struct NestedStruct1
	{
		parse_all_nested_namespace_NestedStruct1_GENERATED
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

class RFKClass(ParseAllNested) ABC
{
	ABC_GENERATED
};

File_ExampleClass_GENERATED