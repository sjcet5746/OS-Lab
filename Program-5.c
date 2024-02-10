#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct {
    int pid;
    int burst_time;
    int priority;
    int remaining_time;
} Process;

void dynamic_priority_scheduling(Process processes[], int n) {
    int current_time = 0;
    int total_burst_time = 0;

    // Calculate total burst time
    for (int i = 0; i < n; i++) {
        total_burst_time += processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Loop until all processes are executed
    while (total_burst_time > 0) {
        // Find the highest priority process that is ready
        int highest_priority_index = -1;
        int highest_priority = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && processes[i].priority > highest_priority) {
                highest_priority_index = i;
                highest_priority = processes[i].priority;
            }
        }

        // Execute the highest priority process for 1 unit of time
        if (highest_priority_index != -1) {
            printf("Executing Process %d (Priority: %d) at Time %d\n", processes[highest_priority_index].pid, processes[highest_priority_index].priority, current_time);
            processes[highest_priority_index].remaining_time--;
            total_burst_time--;
            current_time++;
        } else {
            current_time++;
        }

        // Update priorities dynamically
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                processes[i].priority = processes[i].priority - 1;
                if (processes[i].priority < 0) {
                    processes[i].priority = 0;
                }
            }
        }
    }
}

int main() {
    // Example processes
    Process processes[MAX_PROCESSES] = {
        {1, 10, 5},
        {2, 5, 3},
        {3, 8, 7}
    };

    int n = 3; // Number of processes

    printf("Dynamic Priority Scheduling:\n");
    dynamic_priority_scheduling(processes, n);

    return 0;
}
