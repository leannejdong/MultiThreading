#include <iostream>
#include <future>
#include <chrono>

using std::cerr;
using std::async;
using std::launch;
using std::future;

size_t work(size_t id)
{
  for(size_t i = 0; i < 5; ++i)
  {
    cerr << "running " << id << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  return id * 7;
}

int main()
{
//  future<void> f1 = async(launch::deferred, work, 0);
//  f1.get();
  future<size_t> f1 = async(launch::async, work, 0);

  future<size_t> f2 = async(launch::async, work, 1);

  cerr << f1.get() << "\n";
  cerr << f2.get() << "\n";
  return 0;
}
#if 0
If the std::future obtained from std::async is not moved from or bound to a reference,
the destructor of the std::future will block at the end of the full expression until the
asynchronous operation completes, essentially making code such as the following synchronous:
#endif
