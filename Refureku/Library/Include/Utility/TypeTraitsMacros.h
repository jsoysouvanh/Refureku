#pragma once

#include <type_traits>

/**
*	This macro generates a traits which allows to know at compile-time if a class owns a method with a 
*	given prototype named MethodName.
*
*	/!\ It works only for public methods
*
*	For example, if you use GENERATE_IMPLEMENTS_METHOD_TRAITS(MyCustomMethod), you will be able to write:
*		if constexpr (implements_MyCustomMethod<MyCustomClass, void(int, float)>::value)
*		{
*			//Do something
*		}
*		
*		(replacing void(int, float) by the prototype you want)
*/
#define GENERATE_IMPLEMENTS_METHOD_TRAITS(MethodName)																					\
template<typename Class, typename T>	struct implements_##MethodName {};																\
template <typename Class, typename Ret, typename... Args>																				\
struct implements_##MethodName<Class, Ret(Args...)>																						\
{																																		\
	private:																															\
		template<typename T>																											\
		static constexpr auto check(T*) -> typename std::is_same<decltype(std::declval<T>().MethodName(std::declval<Args>()...)), Ret>;	\
																																		\
		template<typename>																												\
		static constexpr std::false_type check(...);																					\
																																		\
	public:																																\
		static constexpr bool value = decltype(check<Class>(nullptr))::value;															\
};

/**
*	This macro generates a traits which allows to know at compile-time if a class has a field with a given type named fieldName.
*
*	/!\ It works only for public fields
*
*	For example, if you use GENERATE_HAS_FIELD_TRAITS(someField), you will be able to write:
*		if constexpr (hasField_someField<MyCustomClass, int>::value)
*		{
*			//Do something
*		}
*		
*		(replacing int by the type you want)
*/
#define GENERATE_HAS_FIELD_TRAITS(fieldName)																		\
template <typename Class, typename FieldType>																		\
struct hasField_##fieldName																							\
{																													\
	private:																										\
		template <typename T>																						\
		static constexpr auto check(T*) -> typename std::is_same<decltype(std::declval<T>().fieldName), FieldType>;	\
																													\
		template <typename>																							\
		static constexpr std::false_type check(...);																\
																													\
	public:																											\
		static constexpr bool value = decltype(check<Class>(nullptr))::value;										\
};