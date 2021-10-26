/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <string_view>
#include <array>

namespace rfk
{
	
	template <std::string_view const&... Strs>
	class StringViewJoiner
	{
		private:
			/**
			*	@brief	Join all strings into a single std::array of chars.
			*			Implementation found here: https://stackoverflow.com/questions/38955940/how-to-concatenate-static-strings-at-compile-time
			* 
			*	@return An std::array that contains the concatenation of all passed std::string_view.
			*/
			static constexpr auto joinStringViews() noexcept;

			/** Array containing the concatenated string views. */
			static constexpr auto concatenatedStringsArray = joinStringViews();

		public:
			StringViewJoiner()	= delete;
			~StringViewJoiner()	= delete;

		/** Result of the concatenation. */
		static constexpr std::string_view value{concatenatedStringsArray.data(), concatenatedStringsArray.size() - 1};
	};

	#include "Refureku/Utility/StringViewJoiner.inl"
}