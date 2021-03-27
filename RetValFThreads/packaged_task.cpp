#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include <iostream>
#include <cmath>
#include <thread>
#include <future>

using std::cerr;

double calculate_pi(int terms) 
{
    double sum = 0.0;

    if(terms < 1)
    {
        throw std::runtime_error("Terms cannot be less than 1");
    }

    for(int i = 0; i < terms; i++)
    {
        int sign = pow(-1, i);
        double term = 1.0/(i * 2 + 1);
        sum += sign * term;
    }

    return sum * 4;
}

int main() 
{
  std::packaged_task<double(int)> task1(calculate_pi);
  std::future<double> future1 = task1.get_future();
  std::thread t1(std::move(task1), 1E6);

  try
  {
    double result = future1.get();
    fmt::print("{:.15}", result);
  } catch(std::exception &e)
  {
    cerr << "ERROR! " << e.what() << "\n";
  }
    t1.join();
    return 0;
}
 
