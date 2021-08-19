/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename ResultType, typename>
ResultType TaskHelper::getResult(TaskBase* task)
{
	assert(task != nullptr);

	return reinterpret_cast<Task<ResultType>*>(task)->_result.get();
}

template <typename ResultType, typename>
ResultType TaskHelper::getDependencyResult(TaskBase* task, size_t dependencyIndex)
{
	assert(task != nullptr);

	return TaskHelper::getResult<ResultType>(task->dependencies.at(dependencyIndex).get());
}