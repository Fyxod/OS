#include <iostream>
using namespace std;
int sharedVariable = 0;
bool semaphore = true;
void thread1()
{
    cout << "Thread 1: Waiting to enter the critical section...\n";
    while (!semaphore)
    {
        // Busy wait until semaphore becomes available
    }
    semaphore = false;
    cout << "Thread 1: Entered the critical section.\n";
    sharedVariable += 10;
    cout << "Thread 1: Updated shared variable to " << sharedVariable << endl;
    // semaphore = true;
    cout << "Thread 1: Exited the critical section.\n";
}
void thread2()
{
    cout << "Thread 2: Waiting to enter the critical section...\n";
    while (!semaphore)
    {
        // Busy wait until semaphore becomes available
    }
    semaphore = false;
    cout << "Thread 2: Entered the critical section.\n";
    sharedVariable += 20;
    cout << "Thread 2: Updated shared variable to " << sharedVariable << endl;
    semaphore = true;
    cout << "Thread 2: Exited the critical section.\n";
}

int main()
{
    cout << "Main thread: Starting simulated threads...\n";
    thread1();
    thread2();
    cout << "Main thread: Final value of shared variable is " << sharedVariable << endl;
    return 0;
}