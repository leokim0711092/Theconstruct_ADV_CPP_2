#include <iostream>
#include <thread>


// The function you want to execute on the new thread.
void task()
{
    std::cout << "Executing work on a thread!" << std::endl;
}

int main()
{
    // Constructs the new thread and runs it. Does not block execution.
    std::thread t1(task);

    // Check the number of thread can be used
    std::cout<< std::thread::hardware_concurrency();
    // Makes the main thread wait for the new thread to finish execution, blocking its own execution.
    t1.join();
}