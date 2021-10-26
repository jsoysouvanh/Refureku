/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <std::string_view const&... Strs>
constexpr auto StringViewJoiner<Strs...>::joinStringViews() noexcept
{
	constexpr std::size_t resultLength = (Strs.size() + ... + 0);
	std::array<char, len + 1> result{};
	result[resultLength] = 0;

	auto append = [i = 0, &result](auto const& s) mutable
	{
		for (auto c : s) result[i++] = c;
	};

	(append(Strs), ...);

	return result;
}