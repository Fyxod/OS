#include <iostream>
using namespace std;

int main() {
    // Number of processes and resources
    int n = 5; // Number of processes
    int r = 3; // Number of resources

    // Allocation matrix
    int alloc[5][3] = {
        {0, 0, 1},
        {3, 0, 0},
        {1, 0, 1},
        {2, 3, 2},
        {0, 0, 3}
    };

    // Maximum demand matrix
    int max[5][3] = {
        {7, 6, 3},
        {3, 2, 2},
        {8, 0, 2},
        {2, 1, 2},
        {5, 2, 3}
    };

    // Available resources
    int avail[3] = {2, 2, 4};

    // Step 1: Calculate the Need matrix (Need = Max - Alloc)
    int need[5][3];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Step 2: Initialize tracking arrays
    int finished[n] = {0}; // To track if a process is completed
    int safeSeq[n];        // To store the safe sequence
int count = 0;
    // Step 3: Find the safe sequence
    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finished[i]) { // Process not finished
                bool canProceed = true;

                // Check if resources can be allocated
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > avail[j]) {
                        canProceed = false;
                        break;
                    }
                }

                // If resources can be allocated
                if (canProceed) {
                    // Add allocated resources back to available
                    for (int j = 0; j < r; j++) {
                        avail[j] += alloc[i][j];
                    }

                    // Mark process as finished and add to safe sequence
                    safeSeq[count++] = i;
                    finished[i] = 1;
                    found = true;
                }
            }
        }

        // If no process could proceed, system is not in a safe state
        if (!found) {
            cout << "System is not in a safe state!" << endl;
            return 0;
        }
    }

    // Step 4: Print the safe sequence
    cout << "The system is in a safe state.\nSafe Sequence: ";
    for (int i = 0; i < n; i++) {
        cout << "P" << safeSeq[i];
        if (i != n - 1) cout << " -> ";
    }
    cout << endl;

    return 0;
}