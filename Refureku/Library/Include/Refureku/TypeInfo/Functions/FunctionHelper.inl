/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename T>
bool FunctionHelper<T>::hasSamePrototype(FunctionBase const&) noexcept
{
	//If the code asserts here, it means there's a call to getMethod or getStaticMethod with an invalid template.
	//The template must be a method signature.
	//Example1: void example1Method(int i, float j); -> getMethod<void(int, float)>("example1Method");
	//Example2: static int example2Method();		 -> getStaticMethod<int()>("example2Method");
	assert(false);

	return false;
}

template <typename ReturnType, typename... ArgTypes>
bool FunctionHelper<ReturnType(ArgTypes...)>::hasSamePrototype(FunctionBase const& function) noexcept
{
	return function.hasSamePrototype<ReturnType, ArgTypes...>();
}