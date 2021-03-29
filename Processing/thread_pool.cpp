//The idea of threads pool is to run lots of threads at the same time
#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include <random>
using std::cerr;
using std::mutex;
using std::queue;
using std::unique_lock;
using std::thread;
mutex g_mtx;

template<typename E>
class blocking_queue
{
private:
    mutex _mtx;
    std::condition_variable _cond;
    size_t _max_size;
    queue<E> _queue;

public:
    blocking_queue(int max_size): _max_size(max_size)
    {

    }

    void push(E e)
    {
        unique_lock<mutex> lock(_mtx);

        _cond.wait(lock, [this](){ return _queue.size() < _max_size; });

        _queue.push(e);

        lock.unlock();
        _cond.notify_one();
    }

    E front()
    {
        unique_lock<mutex> lock(_mtx);
         _cond.wait(lock, [this](){ return !_queue.empty(); });

        return _queue.front();
    }

    void pop()
    {
        unique_lock<mutex> lock(_mtx);

        _cond.wait(lock, [this](){ return !_queue.empty(); });

        _queue.pop();

        lock.unlock();
        _cond.notify_one();
    }

    int size()
    {
        std::lock_guard<mutex> lock(_mtx);
        return _queue.size();
    }
};

size_t work(size_t id)
{
  std::unique_lock<mutex> lock(g_mtx);
  cerr << "Starting " << id << "\n";
  lock.unlock();
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(3,8);
  auto random_3_8 = dis(gen);
  size_t seconds =size_t(random_3_8) /*size_t((5.0*rand())/RAND_MAX +3)*/;
  std::this_thread::sleep_for(std::chrono::seconds(3));
  return id;
}

int main()
{
  blocking_queue<std::shared_future<size_t>> futures(2);
  thread t([&](){
      for(size_t i = 0; i < 20; ++i)
      {
      std::shared_future<size_t> f = std::async(std::launch::async, work, i);
      futures.push(f);
      }
      });

      for(size_t i = 0; i < 20; ++i)
      {
      std::shared_future<size_t> f =futures.front(); 
      size_t value = f.get();
      futures.pop();
      cerr << "Returned: " << value << "\n";
      }

  t.join();

  return 0;
}
// When to use it?
// when some heavy work has to be done.
// that we want to distribute over multiple cores of our machine.
// Or we might just want some asynchronous behavior
// while waiting for something external
// https://godbolt.org/z/vfbn5cvdj
