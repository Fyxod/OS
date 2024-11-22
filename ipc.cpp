#include <iostream>
using namespace std;
const int MESSAGE_COUNT = 5; 

void sender(int messages[])
{
    for (int i = 0; i < MESSAGE_COUNT; i++)
    {
        messages[i] = i + 1; 
        cout << "Sender: Sent message " << messages[i] << endl;
    }
}

void receiver(int messages[])
{
    for (int i = 0; i < MESSAGE_COUNT; i++)
    {
        cout << "Receiver: Received message " << messages[i] << endl; 
    }
}
int main()
{
    int messages[MESSAGE_COUNT]; 
    sender(messages);
    receiver(messages);
    return 0;
}