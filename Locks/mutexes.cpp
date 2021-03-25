
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>

int main()
{
  int count = 0;
  const int ITERATIONS = 1E6;
  std::mutex mtx;
  auto func = [&]() {
    for(size_t i = 0; i < ITERATIONS; ++i)
    {
      mtx.lock();
      ++count;
      mtx.unlock();
    }// lock just before altering the shared data and unlock immediately afterward
  };

  std::thread t1(func);
  std::thread t2(func);

  t1.join();
  t2.join();
  std::cout << count << "\n";

  return 0;
}
// only 1 thread can lock a mutex at a given time
