#include <iostream>
#include <vector>
using namespace std;
void displayMemory(const vector<int> &memory)
{
    cout << "Current Memory State: ";
    for (int i = 0; i < memory.size(); ++i)
        cout << "  " << memory[i] << "  ";
    cout << endl;
}
bool firstFit(vector<int> &memory, int blockSize)
{
    for (int i = 0; i < memory.size(); ++i)
    {
        if (memory[i] >= blockSize)
        {
            memory[i] -= blockSize;
            cout << "Allocated " << blockSize << " in block " << i + 1 << endl;
            return true;
        }
    }
    return false;
}
bool bestFit(vector<int> &memory, int blockSize)
{
    int minIndex = -1, minSize = INT32_MAX;
    for (int i = 0; i < memory.size(); ++i)
    {
        if (memory[i] >= blockSize && memory[i] < minSize)
        {
            minSize = memory[i];
            minIndex = i;
        }
    }
    if (minIndex != -1)
    {
        memory[minIndex] -= blockSize;
        cout << "Allocated " << blockSize << " in block " << minIndex + 1 << endl;
        return true;
    }
    return false;
}
bool worstFit(vector<int> &memory, int blockSize)
{
    int maxIndex = -1, maxSize = -1;
    for (int i = 0; i < memory.size(); ++i)
    {
        if (memory[i] >= blockSize && memory[i] > maxSize)
        {
            maxSize = memory[i];
            maxIndex = i;
        }
    }
    if (maxIndex != -1)
    {
        memory[maxIndex] -= blockSize;
        cout << "Allocated " << blockSize << " in block " << maxIndex + 1 << endl;
        return true;
    }
    return false;
}
int main()
{
    vector<int> memory = {100, 500, 200, 300, 600};
    int choice, blockSize;
    cout << "Initial Memory State: ";
    displayMemory(memory);
    do
    {
        cout << "\nMemory Allocation Strategies:\n";
        cout << "1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 4)
            break;
        cout << "Enter block size to allocate: ";
        cin >> blockSize;
        bool allocated = false;
        switch (choice)
        {
        case 1:
            allocated = firstFit(memory, blockSize);
            break;
        case 2:
            allocated = bestFit(memory, blockSize);
            break;
        case 3:
            allocated = worstFit(memory, blockSize);
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
        if (!allocated)
            cout << "Failed to allocate " << blockSize << " memory block.\n";

        displayMemory(memory);
    } while (true);
    cout << "Exiting program...\n";
    return 0;
}