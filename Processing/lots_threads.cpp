//The idea of threads pool is to run lots of threads at the same time
#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <vector>

using std::cerr;
using std::mutex;
mutex g_mtx;

size_t work(size_t id)
{
  std::unique_lock<mutex> lock(g_mtx);
  cerr << "Starting " << id << "\n";
  lock.unlock();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  return id;
}

int main()
{
  std::vector<std::shared_future<size_t>> futures;
  for(size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
  {
    std::shared_future<size_t> f = std::async(std::launch::async, work, i);
    futures.push_back(f);
  }
  for(auto f: futures)
  {
    cerr << "Returned: " << f.get() << "\n";
  }

  return 0;
}
// When to use it?
// when some heavy work has to be done.
// that we want to distribute over multiple cores of our machine.
// Or we might just want some asynchronous behavior
// while waiting for something external
