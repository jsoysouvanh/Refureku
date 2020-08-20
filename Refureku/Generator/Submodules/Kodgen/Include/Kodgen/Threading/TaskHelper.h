/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <type_traits>	//std::enable_if_t
#include <cassert>

#include "Kodgen/Threading/Task.h"

namespace kodgen
{
	class TaskHelper
	{
		public:
			TaskHelper()					= delete;
			TaskHelper(TaskHelper const&)	= delete;
			TaskHelper(TaskHelper&&)		= delete;
			~TaskHelper()					= delete;

			/**
			*	@brief Retrieve the result from a TaskBase object
			*	
			*	@param task The task we get the result from.
			*
			*	@return The result of the provided task.
			*/
			template <typename ResultType, typename = typename std::enable_if_t<!std::is_same_v<ResultType, void>>>
			static ResultType getResult(TaskBase* task);

			/**
			*	@brief	Retrieve the result from a TaskBase dependency.
			*			If the provided return type doesn't match the task dependency result type, the program will crash.
			*
			*	@param task				The executing task.
			*	@param dependencyIndex	Index of the dependency to retrieve the result of.
			*
			*	@exception	Any exception propagated from the dependency execution.
			*	@exception	std::out_of_range if dependencyIndex goes out of bound of the dependencies vector.
			*
			*	@return The result of the provided task.
			*/
			template <typename ResultType, typename = typename std::enable_if_t<!std::is_same_v<ResultType, void>>>
			static ResultType getDependencyResult(TaskBase* task, size_t dependencyIndex);
	};

	#include "Kodgen/Threading/TaskHelper.inl"
}