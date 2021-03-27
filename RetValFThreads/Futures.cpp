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
    std::promise<double> Promise;
    auto do_calculation = [&](int terms){
        auto result = calculate_pi(terms);
        Promise.set_value(result);// use promise to set result
    };
    std::thread t1(do_calculation, 1E8);
    std::future<double> Future = Promise.get_future();

    fmt::print("{:.15}", calculate_pi(1e8));
    t1.join();
    return 0;
}
// https://godbolt.org/z/n7njb5WY8

//The idea is to separate consumer to producer
