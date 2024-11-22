#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid, arrival_time, burst_time, waiting_time, completion_time, turn_around__time, priority;
    int remaining_bt; 
};

void calculateTimes(Process p[], int n) {
    int currentTime = 0;
    int completedCount = 0;
    vector<int> remaining_bt(n);

    for (int i = 0; i < n; i++) {
        remaining_bt[i] = p[i].burst_time;
    }

    while (completedCount < n) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= currentTime && remaining_bt[i] > 0) {
                if (idx == -1 || p[i].priority > p[idx].priority) {
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            currentTime++;
        } else {
            remaining_bt[idx]--;
            currentTime++;

            if (remaining_bt[idx] == 0) {
                p[idx].completion_time = currentTime; 
                p[idx].turn_around__time = p[idx].completion_time - p[idx].arrival_time; 
                p[idx].waiting_time = p[idx].turn_around__time - p[idx].burst_time; 
                completedCount++;
            }
        }
    }
}

void display(Process p[], int n, int &idle) {
    int totalWT = 0, totalTAT = 0;
    cout << "PID\ttat\tBT\tPriority\tET\tWT\tTAT" << endl;
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].priority << "\t\t"
             << p[i].completion_time << "\t" << p[i].waiting_time << "\t" << p[i].turn_around__time << "\t" << endl;
        totalWT += p[i].waiting_time;
        totalTAT += p[i].turn_around__time;
    }
    float avgWT = totalWT / (float)n;
    float avgTAT = totalTAT / (float)n;
    cout << endl;
    cout << "Average\t\t\t\t\t" << avgWT << "\t" << avgTAT << "\t" << endl;
}

int main() {
    Process p[5] = {
        {1, 0, 4, 0, 0, 0, 2},  // PID, arrival_time, burst_time, waiting_time, completion_time, turn_around__time, Priority
        {2, 1, 3, 0, 0, 0, 3},
        {3, 2, 1, 0, 0, 0, 4},
        {4, 3, 5, 0, 0, 0, 5},
        {5, 4, 2, 0, 0, 0, 5}
    };

    int n=5;
    int idle = 0;
    calculateTimes(p, n);
    display(p, n, idle);
    return 0;
}