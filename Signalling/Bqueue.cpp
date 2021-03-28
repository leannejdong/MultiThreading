// Implement a producer-consumer pattern by implementing a blocking queue

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using std::cerr;
using std::mutex;
using std::queue;
using std::unique_lock;
using std::thread;


template<typename E>
class blocking_queue
{
private:
    mutex _mtx;
    std::condition_variable _cond;
    size_t _max_size;
    queue<E> _queue;

public:
    blocking_queue(int max_size): _max_size(max_size)
    {

    }

    void push(E e)
    {
        unique_lock<mutex> lock(_mtx);

        _cond.wait(lock, [this](){ return _queue.size() < _max_size; });

        _queue.push(e);

        lock.unlock();
        _cond.notify_one();
    }

    E front()
    {
        unique_lock<mutex> lock(_mtx);
         _cond.wait(lock, [this](){ return !_queue.empty(); });

        return _queue.front();
    }

    void pop()
    {
        unique_lock<mutex> lock(_mtx);

        _cond.wait(lock, [this](){ return !_queue.empty(); });

        _queue.pop();

        lock.unlock();
        _cond.notify_one();
    }

    int size()
    {
        std::lock_guard<mutex> lock(_mtx);
        return _queue.size();
    }
};

int main()
{
    blocking_queue<int> qu(3);

    thread t1([&](){
        for(int i = 0; i < 10; ++i)
        {
            cerr << "pushing " << i << ", ";
            cerr << "queue size is " << qu.size() << "\n";
            qu.push(i);
        }
    });

    thread t2([&](){
        for(int i = 0; i < 10; ++i)
        {
            auto item = qu.front();
            qu.pop();
            cerr << "consumed " << item << "\n";
        }
    });

    t1.join();
    t2.join();

    return 0;
}
// This is our final blocking queue. The next step is to use this to implement a thread pool.
