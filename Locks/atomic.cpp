#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <vector>
//#include <mutex>

class Process
{
public:
    Process(std::atomic<int>& count) : m_count(count)
    {
    }

    void addThread()
    {
        threads.emplace_back([this]{ this->work(); });
    }

    void work()
    {
        for(size_t i = 0; i < 1E6; ++i)
        {
            ++m_count;
        }
    }

    ~Process()
    {
        for (auto& thread: threads)
        {
            thread.join();
        }
    }

    std::vector<std::thread> threads;

    std::atomic<int>& m_count;
};

int main()
{
  std::atomic<int> count(0);
  {
    Process p(count);
    p.addThread();
    p.addThread();
    p.addThread();
  }
  std::cout << count << "\n";

  return 0;
}
// https://godbolt.org/z/j3o1K5c7j
