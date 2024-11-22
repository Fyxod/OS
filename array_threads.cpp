#include <iostream>
using namespace std;

// Shared data
const int SIZE = 10;
int data[SIZE] = {3, 1, 7, 4, 5, 9, 8, 6, 2, 0};

// Results for the threads
int sum = 0, maxValue = INT32_MIN, minValue = INT32_MAX;

// Thread 1: Calculates the sum of elements
void calculateSum() {
    for (int i = 0; i < SIZE; i++) {
        sum += data[i];
    }
    cout << "Thread 1: Sum of elements = " << sum << endl;
}

// Thread 2: Finds the maximum value
void findMax() {
    for (int i = 0; i < SIZE; i++) {
        if (data[i] > maxValue) {
            maxValue = data[i];
        }
    }
    cout << "Thread 2: Maximum value = " << maxValue << endl;
}

// Thread 3: Finds the minimum value
void findMin() {
    for (int i = 0; i < SIZE; i++) {
        if (data[i] < minValue) {
            minValue = data[i];
        }
    }
    cout << "Thread 3: Minimum value = " << minValue << endl;
}

int main() {
    cout << "Main thread: Starting simulated threads..." << endl;

    // Simulating threads by calling functions sequentially
    calculateSum(); // Simulate thread 1
    findMax();      // Simulate thread 2
    findMin();      // Simulate thread 3

    // All simulated threads are complete
    cout << "Main thread: All threads completed." << endl;

    return 0;
}