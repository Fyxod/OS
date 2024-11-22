#include <iostream>
#include<algorithm>
using namespace std;

const int MAX_PROCESSES = 10; // Maximum number of processes supported

// Structure to represent a process
struct Process {
    int id;               // Process ID
    int arrival_time;     // Time at which the process arrives
    int burst_time;       // Time required by the process to complete
    int waiting_time;     // Time the process waits in the ready queue
    int turnaround_time;  // Total time from arrival to completion
};
bool compareByArrivalTime(const Process& a, const Process& b) {
    return a.arrival_time < b.arrival_time;
}
// Function to simulate First Come First Serve (FCFS) scheduling
void fcfs(Process processes[], int n) {
    int current_time = 0; // Keeps track of the current time in the system
    for (int i = 0; i < n; ++i) {
        // If the CPU is idle, fast-forward to the arrival time of the next process
        //This is to handle cases where process may be arriving late and not at t=0. 
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }

        // Calculate waiting time and turnaround time for the current process
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;

        // Update current time after executing the current process
        current_time += processes[i].burst_time;
    }
}

// Function to simulate Shortest Job First (SJF) Non-Preemptive scheduling
void sjfNonPreemptive(Process processes[], int n) {
    int current_time = 0;                  // Keeps track of the current time in the system
    bool completed[MAX_PROCESSES] = {0};   // Tracks if a process has completed execution

    for (int completed_processes = 0; completed_processes < n;) {
        int idx = -1;       // Index of the process to execute next
        int min_burst = 1e9; // Minimum burst time among ready processes

        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; ++i) {
            if (!completed[i] && processes[i].arrival_time <= current_time &&
                processes[i].burst_time < min_burst) {
                min_burst = processes[i].burst_time;
                idx = i;
            }
        }

        if (idx != -1) {
            // Execute the selected process
            processes[idx].waiting_time = current_time - processes[idx].arrival_time;
            processes[idx].turnaround_time = processes[idx].waiting_time + processes[idx].burst_time;
            current_time += processes[idx].burst_time; // Update current time
            completed[idx] = true;                    // Mark process as completed
            completed_processes++;
        } else {
            current_time++; // If no process is ready, move to the next unit of time
        }
    }
}

// Function to simulate Shortest Job First (SJF) Preemptive scheduling
void sjfPreemptive(Process processes[], int n) {
    int current_time = 0;                 // Keeps track of the current time in the system
    int remaining_burst[MAX_PROCESSES];   // Tracks remaining burst times for each process
    for (int i = 0; i < n; ++i) {
        remaining_burst[i] = processes[i].burst_time; // Initialize remaining burst times
    }

    for (int completed_processes = 0; completed_processes < n;) {
        int idx = -1;       // Index of the process to execute next
        int min_burst = 1e9; // Minimum remaining burst time among ready processes

        // Find the process with the shortest remaining burst time
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival_time <= current_time && remaining_burst[i] > 0 &&
                remaining_burst[i] < min_burst) {
                min_burst = remaining_burst[i];
                idx = i;
            }
        }

        if (idx != -1) {
            remaining_burst[idx]--; // Decrement the remaining burst time of the selected process
            if (remaining_burst[idx] == 0) {
                // If the process finishes, calculate waiting and turnaround times
                processes[idx].waiting_time = current_time - processes[idx].arrival_time - processes[idx].burst_time;
                processes[idx].turnaround_time = processes[idx].waiting_time + processes[idx].burst_time;
                completed_processes++;
            }
        }
        current_time++; // Move to the next unit of time
    }
}

// Function to display results and calculate averages
void displayResults(Process processes[], int n) {
    int total_waiting_time = 0;     // Sum of waiting times for all processes
    int total_turnaround_time = 0; // Sum of turnaround times for all processes

    cout << "\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; ++i) {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t"
             << processes[i].burst_time << "\t\t" << processes[i].waiting_time << "\t\t"
             << processes[i].turnaround_time << endl;

        // Update total times
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    // Display average waiting and turnaround times
    cout << "\nAverage Waiting Time: " << (float)total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << (float)total_turnaround_time / n << endl;
}

int main() {

    int n, choice;
    cout << "Enter number of processes: ";
    cin >> n;

    Process processes[MAX_PROCESSES];
    // Input process details
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
    }
    sort(processes,processes+n,compareByArrivalTime);

    // Prompt user to select scheduling algorithm
    cout << "\nChoose Scheduling Algorithm:\n";
    cout << "1. FCFS (First Come First Serve)\n";
    cout << "2. SJF Non-Preemptive (Shortest Job First)\n";
    cout << "3. SJF Preemptive (Shortest Job First)\n";
    cout << "Enter your choice: ";
    cin >> choice;

    // Apply the chosen scheduling algorithm
    switch (choice) {
        case 1:
            fcfs(processes, n);
            break;
        case 2:
            sjfNonPreemptive(processes, n);
            break;
        case 3:
            sjfPreemptive(processes, n);
            break;
        default:
            cout << "Invalid choice!\n";
            return 0;
    }

    // Display results
    displayResults(processes, n);
    return 0;
}
