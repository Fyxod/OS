#include <iostream>
using namespace std;

struct Process {
    int pid, arrival_time, burst_time, waiting_time, completion_time, turn_around_time, priority;
};

void calculateTimes(Process p[], int n) {
    int currentTime = 0;
    bool completed[n] = {false};

    for (int completedCount = 0; completedCount < n; completedCount++) {
        int idx = -1;
        for (int i = 0; i < n; i++) {

            if (!completed[i] && p[i].arrival_time <= currentTime) {
                if (idx == -1 || p[i].priority > p[idx].priority) {
                    idx = i;
                }
            }
        }
        
        if (idx == -1) {
            currentTime++;
            completedCount--;
            continue;
        }

        currentTime += p[idx].burst_time;
        p[idx].completion_time = currentTime;
        p[idx].turn_around_time = p[idx].completion_time - p[idx].arrival_time;   
        p[idx].waiting_time = p[idx].turn_around_time - p[idx].burst_time;   

        completed[idx] = true;  
    }
}

void display(Process p[], int n, int &idle) {
    int totalWT = 0, totalTAT = 0;
    cout << "PID\tTAT\tBT\tPriority\tET\tWT\tTAT" << endl;
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].priority << "\t\t"
             << p[i].completion_time << "\t" << p[i].waiting_time << "\t" << p[i].turn_around_time << "\t" << endl;
        totalWT += p[i].waiting_time;
        totalTAT += p[i].turn_around_time;
    }
    float avgWT = totalWT / (float)n;
    float avgTAT = totalTAT / (float)n;
    cout << endl;
    cout << "Average\t\t\t\t\t" << avgWT << "\t" << avgTAT << "\t" << endl;
}

int main() {
    Process p[5] = {
        {1, 0, 4, 0, 0, 0, 0},  // PID, arrival_time, burst_time, waiting_time, completion_time, turn_around_time, Priority
        {2, 1, 3, 0, 0, 0, 0},
        {3, 2, 1, 0, 0, 0, 0},
        {4, 3, 5, 0, 0, 0, 0},
        {5, 4, 2, 0, 0, 0, 0}
    };
    int n=5;
    int idle = 0;
    calculateTimes(p, n);
    display(p, n, idle);
}