#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <cmath>
#include <fmt/format.h>
using std::cerr;

double calculate_pi(size_t terms, size_t start, size_t skip)
{
  double sum = 0.0;

  for(size_t i = start; i < terms; i += skip)
  {
    int sign = pow(-1, i);
    double term = 1.0/(i * 2 + 1);
    sum += sign * term;
  }
  return sum * 4;
}

int main()
{
  std::vector<std::shared_future<double>> futures;
  const size_t concurrency = std::thread::hardware_concurrency();
  auto start = std::chrono::steady_clock::now();
  for(size_t i = 0; i < concurrency; ++i)
  {
    std::shared_future<double> f = std::async(std::launch::async, calculate_pi, 1E8, i, concurrency);
    futures.push_back(f);
  }
  double sum = 0.0;
  for(auto f : futures)
  {
    sum += f.get();
  }
  auto end = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  cerr << "Duration: " << duration << "\n";
  fmt::print("PI: {:.15}\n", M_PI);
  fmt::print("Sum: {:.15}\n", sum);
  return 0;
}

// use fmt! https://godbolt.org/z/79n5EaE1o

