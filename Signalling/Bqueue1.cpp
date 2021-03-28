// A Thread safe version of Bqueue0.cpp
// Thread safe: objects can be accessed by multiple threads and so we don't worry about sychronization
// Is stl containers thread safe?
#include <iostream>
#include <thread>
#include <queue>

using std::cerr;
using std::thread;
using std::queue;

template<typename E>
class blocking_queue
{
  private:
        size_t _max_size;
        queue<E> _queue;

  public:
        blocking_queue(int max_size): _max_size(max_size)
        {
        }
        void push(E e)
        {
          cerr << "start pushing" << "\n";
          _queue.push(e);
          cerr << "end pushing" << "\n";

        }

        E pop()
        {
          cerr << "start popping" << "\n";
          E item = _queue.front();//access item from the front of the queue
          _queue.pop();
          cerr << "end popping" << "\n";
          return item;
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
// This program might have UB in some OS :)
