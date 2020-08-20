/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename Callable, typename>
std::shared_ptr<TaskBase> ThreadPool::submitTask(Callable&& callable, std::vector<std::shared_ptr<TaskBase>>&& deps) noexcept
{
	//Return type of the submitted task
	using ReturnType = typename std::invoke_result_t<Callable, TaskBase*>;

	std::shared_ptr<Task<ReturnType>> newTask =
		std::make_shared<Task<ReturnType>>(std::forward<Callable>(callable), std::forward<std::vector<std::shared_ptr<TaskBase>>>(deps));

	std::unique_lock lock(_taskMutex);

	_tasks.emplace_back(newTask);

	//Unlock mutex before notifying
	lock.unlock();

	_taskCondition.notify_one();

	return newTask;
}