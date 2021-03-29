#include <iostream>
#include <thread>


int main()
{
  std::cerr << std::thread::hardware_concurrency() << "\n";
  return 0;
}
