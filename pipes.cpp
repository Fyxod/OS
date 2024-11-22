#include <iostream>
using namespace std;
const int BUFFER_SIZE = 10; // Size of the bu er
// Parent writes to the pipe (simulated with array)
void parent(int pipe[])
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        pipe[i] = i + 1; // Parent writes values into the pipe
    }
    cout << "Parent: Written data into the pipe." << endl;
}
// Child reads from the pipe (simulated with array)
void child(int pipe[])
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        cout << "Child: Read data from the pipe: " << pipe[i] << endl; // Child reads values from the pipe
    }
}
int main()
{
    int pipe[BUFFER_SIZE]; // Simulate a pipe with an array
    parent(pipe);
    child(pipe);
    return 0;
}
// Parent writes to the pipe
// Child reads from the pipe