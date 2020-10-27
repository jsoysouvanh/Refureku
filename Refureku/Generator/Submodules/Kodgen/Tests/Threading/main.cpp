#include <iostream>

#include <Kodgen/Threading/ThreadPool.h>
#include <Kodgen/Threading/TaskHelper.h>

using namespace kodgen;

struct A
{

};

struct B
{
	void operator()(TaskBase*) noexcept { std::cout << "I am B!" << std::endl; }
};

int main()
{
	ThreadPool threadPool;

	//Depends on nothing, returns an int
	auto t1 = threadPool.submitTask([](TaskBase*) -> int
						  {
							  for (uint64 i = 0u; i < 20u; i++)
							  {
								  std::cout << i << std::endl;
							  }

							  return 42;
						  });

	//Depends on t1, return nothing
	auto t2 = threadPool.submitTask([](TaskBase* t)
						  {
							  std::cout << "This is a task: " << TaskHelper::getDependencyResult<int>(t, 0u) << std::endl;
						}, {t1});

	//Depends on nothing, return nothing
	auto t3 = threadPool.submitTask(B());

	//A is not callable, doesn't compile
	//auto t4 = threadPool.submitTask(A());

	return EXIT_SUCCESS;
}