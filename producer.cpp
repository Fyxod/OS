#include <iostream>
using namespace std;

const int MAX_ITEMS = 5; 
int buffer[MAX_ITEMS];   
int count = 0;           

void producer() {
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (count < MAX_ITEMS) { 
            buffer[count] = i + 1; 
            cout << "Produced: " << buffer[count] << endl;
            count++; 
        } else {
            cout << "Buffer is full! Cannot produce more items.\n";
        }
    }
}

void consumer() {
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (count > 0) {
            cout << "Consumed: " << buffer[count - 1] << endl;
            count--; 
        } else {
            cout << "Buffer is empty! Cannot consume more items.\n";
        }
    }
}

int main() {
    producer();
    consumer();
    return 0;
}