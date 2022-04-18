/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <array>
#include <cstddef>	//std::size_t, std::ptrdiff_t

#include "Refureku/Config.h"
#include "Refureku/Misc/TypeTraitsMacros.h"
#include "Refureku/TypeInfo/Archetypes/GetArchetype.h"
#include "Refureku/TypeInfo/Archetypes/Struct.h"
#include "Refureku/Misc/SharedPtr.h"

#ifndef _RFK_UNPACK_IF_NOT_PARSING

//This macro "KODGEN_PARSING" must match the name defined by the kodgen parser when parsing source files
//It is used by the generated code to hide some portions of code to the parser
#ifdef KODGEN_PARSING
#define RFK_UNPACK_IF_NOT_PARSING(...)
#else
#define RFK_UNPACK_IF_NOT_PARSING(...) __VA_ARGS__
#endif

#endif

namespace rfk::internal
{
	RFK_GENERATE_IMPLEMENTS_TEMPLATE1_METHOD_TRAITS(_rfk_registerChildClass);

	class CodeGenerationHelpers
	{
		public:
			CodeGenerationHelpers()		= delete;
			~CodeGenerationHelpers()	= delete;

			/**
			*	@brief	Register a child class to a parent class if the parent class implements
			*			the templated method "_registerChildClass" and the child class is reflected.
			* 
			*	@param	childClass The child class to register.
			*/
			template <typename ParentClass, typename ChildClass>
			static constexpr void							registerChildClass(rfk::Struct& childClass)	noexcept;

			/**
			*	@brief	Compute the pointer difference to transform a Derived pointer into a Base pointer.
			* 
			*	@tparam	Derived The derived class.
			*	@tparam Base	The base class.
			*/
			template <typename Derived, typename Base>
			RFK_NODISCARD static constexpr std::ptrdiff_t	computeClassPointerOffset()					noexcept;

			/**
			*	@brief	Retrieve the number of reflected fields of the provided class.
			* 
			*	@tparam ClassType Type of the class.
			* 
			*	@return The number of reflected fields in the class when the method is called. If the class is not reflected, return 0.
			*/
			template <typename ClassType>
			RFK_NODISCARD static std::size_t				getReflectedFieldsCount()					noexcept;

			/**
			*	@brief	Retrieve the number of reflected static fields of the provided class.
			* 
			*	@tparam ClassType Type of the class.
			* 
			*	@return The number of reflected static fields in the class when the method is called. If the class is not reflected, return 0.
			*/
			template <typename ClassType>
			RFK_NODISCARD static std::size_t				getReflectedStaticFieldsCount()				noexcept;

			/**
			*	@brief	Instantiate a class if it is default constructible.
			*			This is the default method used to instantiate classes through Struct::makeSharedInstance.
			*	
			*	@return A pointer to a newly allocated instance of the class if the class is default constructible, else nullptr.
			* 
			*	@exception Potential exception thrown by T constructor.
			*/
#if defined(__GNUC__) && !defined (__clang__) && __GNUC__ <= 9
			//Handle pre GCC 9 internal compiler error when using type traits in noexcept
			template <typename T>
			RFK_NODISCARD static rfk::SharedPtr<T>	defaultSharedInstantiator();
#else
			template <typename T>
			RFK_NODISCARD static rfk::SharedPtr<T>	defaultSharedInstantiator() noexcept(!std::is_default_constructible_v<T> || std::is_nothrow_constructible_v<T>);
#endif

			/**
			*	@brief	Instantiate a class if it is default constructible.
			*			This is the default method used to instantiate classes through Struct::makeUniqueInstance.
			*	
			*	@return A pointer to a newly allocated instance of the class if the class is default constructible, else nullptr.
			* 
			*	@exception Potential exception thrown by T constructor.
			*/
#if defined(__GNUC__) && !defined (__clang__) && __GNUC__ <= 9
			//Handle pre GCC 9 internal compiler error when using type traits in noexcept
			template <typename T>
			RFK_NODISCARD static rfk::UniquePtr<T>	defaultUniqueInstantiator();
#else
			template <typename T>
			RFK_NODISCARD static rfk::UniquePtr<T>	defaultUniqueInstantiator() noexcept(!std::is_default_constructible_v<T> || std::is_nothrow_constructible_v<T>);
#endif
	};

	template <auto>
	struct ForceGenerateSymbol
	{
	};

	struct RawTypenameFormat
	{
		/** Number of chars before getting the type part in the __PRETTY_FUNCTION__ / __FUNCSIG__ string. */
		std::size_t leadingCharsCount   = 0u;

		/** Number of chars after the type part in the __PRETTY_FUNCTION__ / __FUNCSIG__ string. */
		std::size_t trailingCharsCount  = 0u;
	};

	/**
	*   @brief Retrieve a unique ID for the type passed in template parameter.
	* 
	*   @tparam T The target type.
	* 
	*   @return A unique char array identifying the passed type.
	*/
	template <typename T>
	static constexpr auto const& getRawTypename() noexcept
	{
__RFK_DISABLE_WARNING_PUSH
__RFK_DISABLE_WARNING_LANGUAGE_EXTENSION_TOKEN

#ifdef _MSC_VER
		return __FUNCSIG__;
#else
		return __PRETTY_FUNCTION__;
#endif

__RFK_DISABLE_WARNING_POP
	}

	/**
	*	@brief Fill the format object according to the format of the __PRETTY_FUNCTION__ / __FUNCSIG__.
	* 
	*	@param out_format The format object to fill.
	* 
	*	@return true if the format was successfully filled, else false.
	*/
	static constexpr bool getCompilerRawTypenameFormat(RawTypenameFormat* out_format) noexcept
	{
		constexpr auto const& rawTypename = getRawTypename<char>();

		for (std::size_t i = 0u;; i++)
		{
			//Detect the "int" chars in the raw type name
			if (rawTypename[i] == 'c' && rawTypename[i+1] == 'h' && rawTypename[i+2] == 'a' && rawTypename[i+3] == 'r')
			{
				if (out_format != nullptr)
				{
					out_format->leadingCharsCount = i;
					out_format->trailingCharsCount = sizeof(rawTypename) - i - 4 - 1; // 4 to consume the "char" part, 1 for the string null terminator.
				}

				return true;
			}
		}

		return false;
	}

	/** Format of the typename for the used compiler. */
	inline static constexpr RawTypenameFormat typenameFormat = []
	{
		//The below line is not supported in g++8, so drop it
		//static_assert(getCompilerRawTypenameFormat(nullptr), "Unable to figure out how to generate type names on this compiler.");
			
		RawTypenameFormat format;
		getCompilerRawTypenameFormat(&format);

		return format;
	}();
		
	/**
	*	@brief Retrieve the typename of the type T.
	* 
	*	@tparam T Target type.
	* 
	*	@return The typename of T as a null terminated std::array.
	*/
	template <typename T>
	constexpr auto getTypenameAsArray() noexcept
	{
		constexpr std::size_t				typenameLength = sizeof(getRawTypename<T>()) - typenameFormat.leadingCharsCount - typenameFormat.trailingCharsCount;
		std::array<char, typenameLength>	typename_{};

		for (std::size_t i = 0; i < typenameLength - 1; i++)
		{
			typename_[i] = getRawTypename<T>()[i + typenameFormat.leadingCharsCount];
		}

		return typename_;
	}
		
	/**
	*	@brief Retrieve the typename of the type T.
	* 
	*	@tparam T Target type.
	* 
	*	@return The typename of T as a char const*.
	*/
	template <typename T>
	char const* getTypename() noexcept
	{
		static constexpr auto name = getTypenameAsArray<T>();
		
		return name.data();
	}

	#include "Refureku/Misc/CodeGenerationHelpers.inl"
}