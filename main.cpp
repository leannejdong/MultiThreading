 //Simple one-thread example
#include <iostream>
#include <string>
#include <thread>
#include <vector>

// single thread
//void print(int n, const std::string &str)  {
//    std::cout << "Printing integer: " << n << std::endl;
//    std::cout << "Printing string: " << str << std::endl;
//}

// single thread
//int main()
//{
//    std::thread t1(print, 10, " Cat ");
//    t1.join();
//
//    return 0;
//    return 0;
//}

// multithread

 void print(int n, const std::string &str)  {
     std::string msg = std::to_string(n) + " : " + str;
     std::cout << msg  << std::endl;
 }

 int main() {
     std::vector<std::string> s = {
             "Cat.blog",
             "Cat",
             "fish",
             "is yummy"
     };
     std::vector<std::thread> threads;

     for (int i = 0; i < s.size(); i++) {
         threads.push_back(std::thread(print, i, s[i]));
     }

     for (auto &th : threads) {
         th.join();
     }
     return 0;
 }

