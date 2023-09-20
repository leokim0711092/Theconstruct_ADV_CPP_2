#include <iostream>
#include <thread>
#include <string>
#include <mutex>

std::mutex mu;

void mySharedFunc(std::string msg, int id)
{
    std::lock_guard<std::mutex> lockGuard(mu);
    // This is a thread-safe zone: just one thread at a time is allowed
    std::cout << msg << ":" << id << std::endl;
}

void thread_function()
{
    for (int i = -100; i < 0; i++)
        mySharedFunc("thread function", i);
}

int main()
{
    std::thread t(&thread_function);
    for (int i = 100; i > 0; i--)
        mySharedFunc("main thread", i);
    t.join();
    return 0;
}