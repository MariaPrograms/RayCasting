#include <condition_variable>
#include <functional>
#include <vector>
#include <thread>
#include <queue>
#include <future>

class ThreadPool
{
public:
	using Task = std::function<void()>;
	ThreadPool(std::size_t _numThreads);
	~ThreadPool();

	template <class T>
	auto AddToQueue(T _task)->std::future<decltype(_task())>
	{
		auto wrapper = std::make_shared<std::packaged_task<decltype(_task()) ()>>(std::move(_task));

		//To restric the scope of the mutext
		{
			std::unique_lock<std::mutex> lock{ eventMutex };
			tasks.emplace([=]
			{
				(*wrapper)();
			});
		}

		eventVar.notify_one();
		return wrapper->get_future();
	}

private:
	void Start(std::size_t _numThreads);
	void Stop() noexcept;

	std::vector<std::thread> threads;
	std::condition_variable eventVar;
	std::mutex eventMutex;
	bool stop = false;

	std::queue<Task> tasks;
};

