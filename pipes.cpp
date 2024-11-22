#include <iostream>
using namespace std;
const int BUFFER_SIZE = 10; 

void parent(int pipe[])
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        pipe[i] = i + 1; 
    }
    cout << "Parent: Written data into the pipe." << endl;
}
void child(int pipe[])
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        cout << "Child: Read data from the pipe: " << pipe[i] << endl; 
    }
}
int main()
{
    int pipe[BUFFER_SIZE];
    parent(pipe);
    child(pipe);
    return 0;
}