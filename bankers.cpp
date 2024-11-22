#include <iostream>
using namespace std;

int main()
{
    int n = 5;
    int r = 3;

    int alloc[5][3] = {
        {0, 0, 1},
        {3, 0, 0},
        {1, 0, 1},
        {2, 3, 2},
        {0, 0, 3}};

    int max[5][3] = {
        {7, 6, 3},
        {3, 2, 2},
        {8, 0, 2},
        {2, 1, 2},
        {5, 2, 3}};

    int avail[3] = {2, 2, 4};

    int need[5][3];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < r; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int finished[n] = {0};
    int safeSeq[n];
    int count = 0;

    while (count < n)
    {
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (!finished[i])
            {
                bool canProceed = true;

                for (int j = 0; j < r; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        canProceed = false;
                        break;
                    }
                }

                if (canProceed)
                {
                    for (int j = 0; j < r; j++)
                    {
                        avail[j] += alloc[i][j];
                    }

                    safeSeq[count++] = i;
                    finished[i] = 1;
                    found = true;
                }
            }
        }

        if (!found)
        {
            cout << "System is not in a safe state!" << endl;
            return 0;
        }
    }

    cout << "The system is in a safe state.\nSafe Sequence: ";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << safeSeq[i];
        if (i != n - 1)
            cout << " -> ";
    }
    cout << endl;

    return 0;
}