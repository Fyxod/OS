#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_PROCESSES = 10; 

struct Process
{
    int id;              
    int arrival_time;    
    int burst_time;      
    int waiting_time;    
    int turnaround_time; 
};
bool compareByArrivalTime(const Process &a, const Process &b)
{
    return a.arrival_time < b.arrival_time;
}

void fcfs(Process processes[], int n)
{
    int current_time = 0; 
    for (int i = 0; i < n; ++i)
    {
        if (current_time < processes[i].arrival_time)
        {
            current_time = processes[i].arrival_time;
        }

        processes[i].waiting_time = current_time - processes[i].arrival_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;

        current_time += processes[i].burst_time;
    }
}

void sjfNonPreemptive(Process processes[], int n)
{
    int current_time = 0; 
    bool completed[MAX_PROCESSES] = {0}; 

    for (int completed_processes = 0; completed_processes < n;)
    {
        int idx = -1;       
        int min_burst = 1e9; 

        for (int i = 0; i < n; ++i)
        {
            if (!completed[i] && processes[i].arrival_time <= current_time && processes[i].burst_time < min_burst)
            {
                min_burst = processes[i].burst_time;
                idx = i;
            }
        }

        if (idx != -1)
        {
            processes[idx].waiting_time = current_time - processes[idx].arrival_time;
            processes[idx].turnaround_time = processes[idx].waiting_time + processes[idx].burst_time;
            current_time += processes[idx].burst_time; 
            completed[idx] = true;
            completed_processes++;
        }
        else
        {
            current_time++;
        }
    }
}

void sjfPreemptive(Process processes[], int n)
{
    int current_time = 0;          
    int remaining_burst[MAX_PROCESSES]; 
    for (int i = 0; i < n; ++i)
    {
        remaining_burst[i] = processes[i].burst_time; 
    }

    for (int completed_processes = 0; completed_processes < n;)
    {
        int idx = -1;        
        int min_burst = 1e9; 

        for (int i = 0; i < n; ++i)
        {
            if (processes[i].arrival_time <= current_time && remaining_burst[i] > 0 && remaining_burst[i] < min_burst)
            {
                min_burst = remaining_burst[i];
                idx = i;
            }
        }

        if (idx != -1)
        {
            remaining_burst[idx]--; 
            if (remaining_burst[idx] == 0)
            {
                processes[idx].waiting_time = current_time - processes[idx].arrival_time - processes[idx].burst_time;
                processes[idx].turnaround_time = processes[idx].waiting_time + processes[idx].burst_time;
                completed_processes++;
            }
        }
        current_time++; 
    }
}

void displayResults(Process processes[], int n)
{
    int total_waiting_time = 0;  
    int total_turnaround_time = 0; 

    cout << "\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; ++i)
    {
        cout << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t"
             << processes[i].burst_time << "\t\t" << processes[i].waiting_time << "\t\t"
             << processes[i].turnaround_time << endl;

        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    cout << "\nAverage Waiting Time: " << (float)total_waiting_time / n << endl;
    cout << "Average Turnaround Time: " << (float)total_turnaround_time / n << endl;
}

int main()
{

    int n, choice;
    cout << "Enter number of processes: ";
    cin >> n;

    Process processes[MAX_PROCESSES];
    
    for (int i = 0; i < n; ++i)
    {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
    }
    sort(processes, processes + n, compareByArrivalTime);

    cout << "\nChoose Scheduling Algorithm:\n";
    cout << "1. FCFS (First Come First Serve)\n";
    cout << "2. SJF Non-Preemptive (Shortest Job First)\n";
    cout << "3. SJF Preemptive (Shortest Job First)\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
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

    displayResults(processes, n);
    return 0;
}