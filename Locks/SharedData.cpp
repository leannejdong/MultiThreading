#include <iostream>
#include <thread>
#include <chrono>

#if 0
When is multithreading useful?
1) When you are waiting for something external and want to execute code meanwhile (asynchronous execution)
Examples: pinging remote servers; drawing
graphics while also processing user input
2) Distributing processing across multiple cores
(big number crunching)
#endif

int main()
{
  int count = 0;
  const int ITERATIONS = 1E6;
  std::thread t1([&count](){
    for(size_t i = 0; i < ITERATIONS; ++i)
    {
      ++count;
    }
  });
  std::thread t2([&count](){
    for(size_t i = 0; i < ITERATIONS; ++i)
    {
      ++count;
    }
  });
  t1.join();
  t2.join();
  std::cout << count << "\n";

  return 0;
}
//1017734 (as we see when ITERATIONS get large, not all increments would work)
// What happened is that, we reserve some memory for our `int count` in the stack
// and to actually increment it, it has to be copied to a register in the CPU.
// And then it is incremented and then copied back into the memory where it normally resides,
// which because it is a local variable, will be in the stack.
// So essentailly the value of count hs to be copied  somewhere incremeneted and then copied back again
// to where it supposed to be. So it is a multi-step operation to increment count, even using the prefix version of this

// Lesson: if you have multiple threads on the same data, they will usually interfere with each other!
