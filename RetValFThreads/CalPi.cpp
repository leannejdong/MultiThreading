#include <iostream>
#include <cmath>
#include <iomanip>

using std::cerr;

double calculate_pi(int terms)
{
  double sum = 0.0;

  for(int i = 0; i < terms; ++i)
  {
    int sign = pow(-1, i);
    double term = 1.0/(i * 2 + 1);
    sum += sign * term;
  }
  return sum * 4;
}

int main()
{
  cerr << setprecision(15) << calculate_pi(1E8) << "\n";
  return 0;
}

// use fmt! https://godbolt.org/z/79n5EaE1o

