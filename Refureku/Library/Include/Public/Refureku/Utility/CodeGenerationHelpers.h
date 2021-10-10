/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <array>
#include <cstddef>
#include <type_traits>

#include "Refureku/Utility/TypeTraitsMacros.h"
#include "Refureku/TypeInfo/Archetypes/GetArchetype.h"
#include "Refureku/TypeInfo/Archetypes/Struct.h"

RFK_GENERATE_IMPLEMENTS_TEMPLATE1_METHOD_TRAITS(_rfk_registerChildClass)

#ifndef _RFK_UNPACK_IF_NOT_PARSING

//This macro "KODGEN_PARSING" must match the name defined by the kodgen parser when parsing source files
//It is used by the generated code to hide some portions of code to the parser
#ifdef KODGEN_PARSING
#define RFK_UNPACK_IF_NOT_PARSING(...)
#else
#define RFK_UNPACK_IF_NOT_PARSING(...) __VA_ARGS__
#endif

#endif

namespace rfk
{
	class CodeGenerationHelpers
	{
		public:
			CodeGenerationHelpers()		= delete;
			~CodeGenerationHelpers()	= delete;

			/**
			*	@brief	Register a child class to a parent class if the parent class implements
			*			the templated method "_registerChildClass" and the child class is reflected.
			*/
			template <typename ParentClass, typename ChildClass>
			static constexpr void	registerChildClass(rfk::Struct& childClass)	noexcept;
	};

	template <auto>
	struct ForceGenerateSymbol
	{
	};

	namespace internal
	{
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
	}

	#include "Refureku/Utility/CodeGenerationHelpers.inl"
}