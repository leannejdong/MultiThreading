#include <iostream>
#include <thread>
#include <chrono>
//#include <atomic>
#include <condition_variable>

using std::mutex;

int main()
{
  std::condition_variable condition;
  mutex mtx;
  bool ready;//from atomic to normal bool, since we'll implement proper thread sychronization.
  //It will be guaranteed that the states will be visible through threads
  std::thread t1([&](){
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::unique_lock<mutex> lock(mtx);
    ready = true;
    lock.unlock();
    condition.notify_one();
    });
  std::unique_lock<mutex> lock(mtx);

  while(!ready)
  {
    condition.wait(lock);
  }
  std::cerr << "ready " << ready << "\n";
  t1.join();
  return 0;
}
