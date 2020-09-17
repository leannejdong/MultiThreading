#include<iostream>
#include <thread>
#include <vector>
#include <numeric>

#include "utility.h"

int main()
{
    const int no_of_threads = 5;
    const int no_of_elems = 500 * 500 * 500;
    const int step = no_of_elems / no_of_threads;
    std::vector<uint64_t> partial_sums(no_of_threads);

    std::thread t1(AccumulateRange, std::ref(partial_sums[0]), 0, step);
    std::thread t2(AccumulateRange, std::ref(partial_sums[1]), step, no_of_threads * step);

    t1.join();
    t2.join();

    uint64_t total = std::accumulate(partial_sums.begin(), partial_sums.end(), uint64_t(0));
    PrintVector(partial_sums);
    std::cout << " Total: " << total << std::endl;
}

