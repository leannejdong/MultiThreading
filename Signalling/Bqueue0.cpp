#include <iostream>
#include <thread>

using std::cerr;
using std::thread;

template<typename E>
class blocking_queue
{
  public:
  void push(E e)
  {
    cerr << "push" << "\n";
  }

  void pop()
  {
    cerr << "pop" << "\n";
  }
};

int main()
{
  blocking_queue<int> qu;
  thread t1(&blocking_queue<int>::push, &qu, 7);
  thread t2(&blocking_queue<int>::pop, &qu);

  t1.join();
  t2.join();

  return 0;
}

