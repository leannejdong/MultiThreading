//
// Created by leanne on 9/17/20.
//

#ifndef MULTITHREADING_UTILITY_H
#define MULTITHREADING_UTILITY_H

#include <cmath>
#include <iostream>
#include <numeric>
#include <string>

//-----------------------------------------------------
template <class T>
void PrintVector(std::vector<T> input) {
    std::cout << "{ ";
    unsigned int count = 0;
    for (auto n : input) {
        count++;
        std::cout << n;
        if (count < input.size()) std::cout << ", ";
    }
    std::cout << " }" << std::endl;
}
//-----------------------------------------------------
class AccumulateFunctor {
public:
    void operator()(uint64_t start, uint64_t end) {
        _sum = 0;
        for (auto i = start; i < end; i++) {
            _sum += i;
        }
        std::cout << _sum << std::endl;
    }
    uint64_t _sum;
};
//-----------------------------------------------------
/* All parameter are passed by value
 * Use std::ref to pass by reference */
void AccumulateRange(uint64_t &sum, uint64_t start, uint64_t end) {
    sum = 0;
    for (uint64_t i = start; i < end; i++) {
        sum += i;
    }
}
//-----------------------------------------------------
uint64_t GetRangeSum(uint64_t start, uint64_t end) {
    uint64_t sum = 0;
    for (uint64_t i = start; i < end; i++) {
        sum += i;
    }
    return sum;
}
#endif //MULTITHREADING_UTILITY_H
