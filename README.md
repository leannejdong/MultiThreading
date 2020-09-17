# Minimal Tutorial on Multithreading and Concurrency in Modern C++

One of the key skill for all C++ developers is concurrency. As programs continue to get more complex, 
computers are accompanied with more CPU cores to match. To efficiently design our C++ programs, we must 
write codes that utilizes multicore machines. This is accomplished through concurrency, a technique that ensures
the use of all cores and maximizes a machine's capacities.

To get ourself familiar with concurrent programming and multithreading. We will go through some basic definitions
and real world examples we need to know.

* Concurrency

Concurrency was first introduced into C++11, include threads, the memory model, conditional variables, 
mutexes and locks. This was dramatically improved in C++17 with the addition of parallel algorithms in STL. 
In C++20, new atomic smart pointers such as `std::atomic_shared_ptr` and `std::atomic_weak_ptr` are introduced to 
deal with data races that induces UB. Another new multithreading features in C++17 or 20 is parallel STL. See
[Parallel Algorithms of STL](https://www.modernescpp.com/index.php/parallel-algorithm-of-the-standard-template-library)

* How to implement concurrency

  * Multithreading
  
  * Parallelism

* Examples of multithreading

* Concurrency in action

The goal of this tutorial is to have ourselves be familiar with concurrency and multithreading in C++