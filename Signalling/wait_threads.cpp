#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
int main()
{
  std::atomic<bool> ready;
  std::thread t1([&](){
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    ready = true;
    });
    t1.join();
    while(!ready)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }
    std::cerr << "ready " << ready << "\n";
    return 0;
}
