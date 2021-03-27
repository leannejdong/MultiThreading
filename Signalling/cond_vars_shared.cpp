#include <iostream>
#include <thread>
#include <chrono>
//#include <atomic>
#include <condition_variable>

using std::mutex;
using std::cerr;

int main()
{
  std::condition_variable condition;
  mutex mtx;
  bool ready;//from atomic to normal bool, since we'll implement proper thread sychronization.
  //It will be guaranteed that the states will be visible through threads
  std::thread t1([&](){
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    cerr << "t1 acquiring lock" << "\n";
    std::unique_lock<mutex> lock(mtx);
    ready = true;
    lock.unlock();
    cerr << "t1 released lock; notifying" << "\n";
    condition.notify_one();
    });
  cerr << "main thread acquiring lock" << "\n";
  std::unique_lock<mutex> lock(mtx);
  cerr << "main thread acquired lock" << "\n";
  condition.wait(lock, [&](){ return ready; });
  cerr << "main thread finished waiting" << "\n";
  std::cerr << "ready " << ready << "\n";
  t1.join();
  return 0;
}
