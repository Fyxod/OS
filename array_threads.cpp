#include <iostream>
using namespace std;

const int SIZE = 10;
int data[SIZE] = {3, 1, 7, 4, 5, 9, 8, 6, 2, 0};

int sum = 0, maxValue = INT32_MIN, minValue = INT32_MAX;

void calculateSum() {
    for (int i = 0; i < SIZE; i++) {
        sum += data[i];
    }
    cout << "Thread 1: Sum of elements = " << sum << endl;
}

void findMax() {
    for (int i = 0; i < SIZE; i++) {
        if (data[i] > maxValue) {
            maxValue = data[i];
        }
    }
    cout << "Thread 2: Maximum value = " << maxValue << endl;
}

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

    calculateSum(); 
    findMax();      
    findMin();      

    cout << "Main thread: All threads completed." << endl;

    return 0;
}