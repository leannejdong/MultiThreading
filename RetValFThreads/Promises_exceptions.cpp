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
    std::promise<double> Promise;
    auto do_calculation = [&](int terms){
        try
        {
            auto result = calculate_pi(terms);
            Promise.set_value(result);
        } catch(...)
        {
            Promise.set_exception(std::current_exception());
        }

    };
    std::thread t1(do_calculation, 1E8);
    std::future<double> Future = Promise.get_future();

    fmt::print("{:.15}", /*calculate_pi(1e8)*/Future.get());
    t1.join();
    return 0;
}
//https://godbolt.org/z/oea8ohzEc 
