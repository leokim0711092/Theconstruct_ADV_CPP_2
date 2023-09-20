#include <iostream>
#include <thread>
#include <string>
#include <mutex>

std::mutex mu;

void mySharedFunc(std::string msg, int id)
{
    mu.lock();
    // This is a thread-safe zone: just one thread at a time is allowed
    std::cout << msg << ":" << id << std::endl;
    mu.unlock();
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