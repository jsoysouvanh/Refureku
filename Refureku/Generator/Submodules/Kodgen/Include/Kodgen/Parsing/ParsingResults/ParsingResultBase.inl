/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline void ParsingResultBase::appendResultErrors(ParsingResultBase& result) noexcept
{
	if (!result.errors.empty())
	{
		errors.insert(errors.cend(), std::make_move_iterator(result.errors.cbegin()), std::make_move_iterator(result.errors.cend()));

		result.errors.clear();
	}
}