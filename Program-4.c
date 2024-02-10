#include<stdio.h>

// Structure to represent a process
typedef struct {
    int pid;
    int burst_time;
    int priority;
} Process;

// Function to simulate Round Robin scheduling algorithm
void roundRobin(Process processes[], int n, int quantum) {
    int remaining_burst_time[n];
    for (int i = 0; i < n; i++) {
        remaining_burst_time[i] = processes[i].burst_time;
    }
    int time = 0;
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (remaining_burst_time[i] > 0) {
                done = 0;
                if (remaining_burst_time[i] > quantum) {
                    time += quantum;
                    remaining_burst_time[i] -= quantum;
                    printf("Process %d executed with remaining burst time %d\n", processes[i].pid, remaining_burst_time[i]);
                } else {
                    time += remaining_burst_time[i];
                    printf("Process %d executed with remaining burst time 0\n", processes[i].pid);
                    remaining_burst_time[i] = 0;
                }
            }
        }
        if (done == 1) {
            break;
        }
    }
}

// Function to simulate Shortest Job First (SJF) scheduling algorithm
void sjf(Process processes[], int n) {
    int time = 0;
    while (1) {
        int min_burst_index = -1;
        int min_burst_time = __INT_MAX__;
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (processes[i].burst_time > 0 && processes[i].burst_time < min_burst_time && time >= processes[i].arrival_time) {
                min_burst_index = i;
                min_burst_time = processes[i].burst_time;
                done = 0;
            }
        }
        if (done == 1) {
            break;
        }
        printf("Process %d executed with remaining burst time 0\n", processes[min_burst_index].pid);
        time += processes[min_burst_index].burst_time;
        processes[min_burst_index].burst_time = 0;
    }
}

// Function to simulate First-Come, First-Served (FCFS) scheduling algorithm
void fcfs(Process processes[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        printf("Process %d executed with remaining burst time %d\n", processes[i].pid, processes[i].burst_time);
        time += processes[i].burst_time;
    }
}

// Function to simulate Priority scheduling algorithm
void priority(Process processes[], int n) {
    int time = 0;
    while (1) {
        int highest_priority_index = -1;
        int highest_priority = -1;
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (processes[i].priority > highest_priority && processes[i].burst_time > 0 && time >= processes[i].arrival_time) {
                highest_priority_index = i;
                highest_priority = processes[i].priority;
                done = 0;
            }
        }
        if (done == 1) {
            break;
        }
        printf("Process %d executed with remaining burst time 0\n", processes[highest_priority_index].pid);
        time += processes[highest_priority_index].burst_time;
        processes[highest_priority_index].burst_time = 0;
    }
}

int main() {
    // Example processes
    Process processes[] = {
        {1, 10, 0},  // Process ID, Burst Time, Priority
        {2, 5, 1},
        {3, 8, 2}
    };

    int n = sizeof(processes) / sizeof(processes[0]);

    printf("Round Robin Scheduling:\n");
    roundRobin(processes, n, 2); // Quantum = 2

    printf("\nShortest Job First (SJF) Scheduling:\n");
    sjf(processes, n);

    printf("\nFirst-Come, First-Served (FCFS) Scheduling:\n");
    fcfs(processes, n);

    printf("\nPriority Scheduling:\n");
    priority(processes, n);

    return 0;
}
