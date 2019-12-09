#include "ThreadPool.h"
#include <iostream>

ThreadPool::ThreadPool(std::size_t _numThreads)
{
	Start(_numThreads);
}

ThreadPool::~ThreadPool()
{
	Stop();
}

void ThreadPool::Start(std::size_t _numThreads)
{
	for (size_t i = 0; i < _numThreads; i++)
	{
		threads.emplace_back([=]
		{
			while (true)
			{
				Task task;

				{
					/*
					keep this stuff in a scope so that the mutext 
					is only locked when we're messing with data
					*/
					std::unique_lock<std::mutex> lock{ eventMutex };
					eventVar.wait(lock, [=] 
					{ 
						return stop || !tasks.empty(); 
					});

					if (stop && tasks.empty())
					{
						break;
					}

					task = std::move(tasks.front());
					tasks.pop();
				}

				task();
			}

		});
	}
}

void ThreadPool::Stop() noexcept
{
	{
		std::unique_lock<std::mutex> lock{ eventMutex };
		stop = true;
	}

	eventVar.notify_all();

	for (auto &t : threads)
	{
		t.join();
	}
}

