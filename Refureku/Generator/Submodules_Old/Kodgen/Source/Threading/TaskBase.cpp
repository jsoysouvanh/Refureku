#include "Kodgen/Threading/TaskBase.h"

using namespace kodgen;

TaskBase::TaskBase(std::vector<std::shared_ptr<TaskBase>>&& deps) noexcept:
	dependencies{std::forward<std::vector<std::shared_ptr<TaskBase>>>(deps)}
{
}