/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>
#include <memory>	//std::shared_ptr
#include <atomic>

namespace kodgen
{
	class TaskBase
	{
		friend class TaskHelper;

		protected:
			/** Dependent tasks which must terminate before this task is executed. */
			std::vector<std::shared_ptr<TaskBase>>	dependencies;

		public:
			TaskBase()														= delete;
			TaskBase(std::vector<std::shared_ptr<TaskBase>>&& deps = {})	noexcept;
			TaskBase(TaskBase const&)										= default;
			TaskBase(TaskBase&&)											= default;
			virtual ~TaskBase()												= default;

			/**
			*	@brief	Check if this task is ready to execute, i.e. it has no dependency or
			*			all its dependencies have finished their execution.
			*	
			*	@return true if this task is ready to execute, else false.
			*/
			virtual bool	isReadyToExecute()	const	noexcept = 0;

			/**
			*	@brief Execute the underlying task.
			*/
			virtual void	execute()					noexcept = 0;

			/**
			*	@brief Check whether this task has finished executing or not.
			*	
			*	@return true if this task has finished, else false.
			*/
			virtual bool	hasFinished()		const	noexcept = 0;
	};
}