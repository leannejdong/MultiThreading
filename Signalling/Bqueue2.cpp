// Producer consumer

// The idea: A finite-size buffer and two classes of threads, producers and consumers
// put items into the buffer(producers) and take items out of the buffer(consumers).
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using std::cerr;
using std::thread;
using std::queue;
using std::mutex;
using std::unique_lock;
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
        {// put thread synchronization
          unique_lock<mutex> lock(_mtx);
          _cond.wait(lock, [this](){ return _queue.size() < _max_size; });// use 'this' to capture _queue
          cerr << "start pushing" << "\n";
          _queue.push(e);
          cerr << "end pushing" << "\n";
          lock.unlock();
          _cond.notify_one();
        }

        E pop()
        {
          unique_lock<mutex> lock(_mtx);
          cerr << "start popping" << "\n";
          _cond.wait(lock, [this](){ return !_queue.empty(); });
          E item = _queue.front();//access item from the front of the queue
          _queue.pop();
          lock.unlock();//don't wait up other threads til u hv released the lock
          _cond.notify_one();
          cerr << "end popping" << "\n";
          return item;
        }
        int size()
        {
          return _queue.size();
        }
};

int main()
{
#if 0
  blocking_queue<int> qu;
  thread t1(&blocking_queue<int>::push, &qu, 7);
  thread t2(&blocking_queue<int>::pop, &qu);
#endif

  blocking_queue<size_t> qu(5);
  thread t1([&](){
    for(size_t i = 0; i < 10; ++i)
    {
      cerr << "pushing " << i << "\n";
      cerr << "queue size is " << qu.size() << "\n";
      qu.push(i);
    }
    });
 
  thread t2([&](){
    for(size_t i = 0; i < 10; ++i)
    {
      auto item = qu.pop();
      cerr << "consumed " << item << "\n";
    }
    });
  t1.join();
  t2.join();

  return 0;
}
