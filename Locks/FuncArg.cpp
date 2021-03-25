#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>

void work(int &count,std::mutex &mtx)
{
   for(size_t i = 0; i < 1E6; ++i)
   {
     mtx.lock();
     ++count;
     mtx.unlock();
   }// lock just before altering the shared data and unlock immediately afterward
}  
int main()
{
  int count = 0;
  std::mutex mtx;

  std::thread t1(work, std::ref(count), std::ref(mtx));
  std::thread t2(work, std::ref(count), std::ref(mtx));

  t1.join();
  t2.join();
  std::cout << count << "\n";

  return 0;
}

#if 0
calling lock/unlock directly is exception-unsafe
locking/unlocking is expensive
mutex doesn't throw exception
The point is: when we call mtx.lock() and then an exception happens,
it is never unlocked.
With the raii scoped_lock, it is unlocked.
Passing in a mutex to use, is kind of strange
#endif
