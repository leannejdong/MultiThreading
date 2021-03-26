#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <vector>
#include <mutex>

class Process
{
public:
    Process(int& count) : m_count(count)
    {
    }

    void addThread()
    {
        threads.emplace_back([this]{ this->operator()(); });
    }

    void operator()()
    {
        for(size_t i = 0; i < 1E6; ++i)
        {
            std::lock_guard<std::mutex> guard(mutex);
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

    int& m_count;
    std::mutex mutex;  
};

int main()
{
   int count = 0;
   {
     Process p(count);
    //  std::thread t1(std::ref(p));
    //  std::thread t2(std::ref(p));
    p.addThread();
    p.addThread();
    p.addThread();
   }
   std::cout << count << "\n";

  return 0;
}
//https://godbolt.org/z/neGnEzYGb
