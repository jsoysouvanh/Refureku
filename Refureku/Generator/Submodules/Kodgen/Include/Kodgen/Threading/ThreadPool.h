/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <thread>
#include <vector>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <functional>	//std::bind
#include <memory>		//std::shared_ptr
#include <type_traits>	//std::invoke_result

#include "Kodgen/Threading/Task.h"
#include "Kodgen/Threading/ETerminationMode.h"
#include "Kodgen/Misc/FundamentalTypes.h"

namespace kodgen
{
	class ThreadPool
	{
		private:
			/** Collection of all workers in this pool. */
			std::vector<std::thread>				_workers;

			/** List of all tasks. */
			//TODO: Might change to std::list to allow fast removal of any element
			std::vector<std::shared_ptr<TaskBase>>	_tasks;

			/** Set to true when the ThreadPool destructor has been called. */
			bool									_destructorCalled	= false;

			/** Condition used to notify workers there are tasks to proceed. */
			std::condition_variable					_taskCondition;

			/** Mutex used with taskCondition. */
			std::mutex								_taskMutex;

			/** Number of actual workers currently running a task. */
			std::atomic_uint						_workingWorkers;

			/**
			*	@brief Routine run by workers.
			*/
			void						workerRoutine()				noexcept;

			/**
			*	@brief	Retrieve a task which is ready to execute.
			*			This method doesn't lock the task mutex so make sure _tasks is safe to access BEFORE the method is called.
			*	
			*	@return A valid shared_ptr pointing to a ready-to-execute task if any, else an empty shared_ptr.
			*/
			std::shared_ptr<TaskBase>	getTask()					noexcept;

			/**
			*	@brief Check whether a worker should keep running or terminate.
			*	
			*	@return true if the worker should continue to poll new tasks, else false.
			*/
			bool						shouldKeepRunning()	const	noexcept;

		public:
			/** Termination mode to apply when this Thread pool will be destroyed. */
			ETerminationMode	terminationMode = ETerminationMode::FinishAll;

			ThreadPool(uint32			threadCount		= std::thread::hardware_concurrency(),
					   ETerminationMode	terminationMode = ETerminationMode::FinishAll)			noexcept;
			ThreadPool(ThreadPool const&)														= delete;
			ThreadPool(ThreadPool&&)															= delete;
			~ThreadPool()																		noexcept;

			/**
			*	@brief Submit a task to the thread pool.
			*	
			*	@param callable	Callable the submitted task should execute. It must take a TaskBase* as parameter.
			*	@param deps		Dependencies of the submitted task.
			*
			*	@return A pointer to the submitted task. It can be used as a dependency when submitting other tasks.
			*/
			template <typename Callable, typename = decltype(std::declval<Callable>()(std::declval<TaskBase*>()))>
			std::shared_ptr<TaskBase>	submitTask(Callable&&								callable,
												   std::vector<std::shared_ptr<TaskBase>>&& deps = {})	noexcept;

			/**
			*	@brief Join all workers.
			*/
			void						joinWorkers()				noexcept;
	};

	#include "Kodgen/Threading/ThreadPool.inl"
}