/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <functional>		//std::function
#include <unordered_set>
#include <memory>			//std::shared_ptr
#include <atomic>
#include <future>
#include <chrono>			//std::chrono::nanoseconds
#include <cassert>

#include "Kodgen/Threading/TaskBase.h"

namespace kodgen
{
	template <typename ReturnType>
	class Task final : public TaskBase
	{
		friend class TaskHelper;

		private:
			/** Underlying task to execute. */
			std::packaged_task<ReturnType(TaskBase*)>	_task;

			/** Result of the call of the underlying _task. */
			std::future<ReturnType>						_result;

		public:
			Task()														= delete;
			Task(std::function<ReturnType(TaskBase*)>&&		task,
				 std::vector<std::shared_ptr<TaskBase>>&&	deps = {})	noexcept;
			Task(Task const&)											= default;
			Task(Task&&)												= default;
			virtual ~Task()												= default;

			virtual bool	isReadyToExecute()	const	noexcept override;
			virtual void	execute()					noexcept override;
			virtual bool	hasFinished()		const	noexcept override;
	};

	#include "Kodgen/Threading/Task.inl"
}