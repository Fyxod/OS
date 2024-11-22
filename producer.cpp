#include <iostream>
using namespace std;

const int MAX_ITEMS = 5; // Number of items in the buffer
int buffer[MAX_ITEMS];   // Shared memory buffer
int count = 0;           // Counter to track the number of items in the buffer

// Producer function
void producer() {
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (count < MAX_ITEMS) { // Check if the buffer is not full
            buffer[count] = i + 1; // Produce item (assign value)
            cout << "Produced: " << buffer[count] << endl;
            count++; // Increment the count
        } else {
            cout << "Buffer is full! Cannot produce more items.\n";
        }
    }
}

// Consumer function
void consumer() {
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (count > 0) { // Check if the buffer has items to consume
            cout << "Consumed: " << buffer[count - 1] << endl;
            count--; // Decrement the count
        } else {
            cout << "Buffer is empty! Cannot consume more items.\n";
        }
    }
}

int main() {
    producer(); // Simulate producer producing items
    consumer(); // Simulate consumer consuming items
    return 0;
}