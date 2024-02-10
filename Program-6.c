#include <stdio.h>

// Structure to represent a job
typedef struct {
    int id;
    int weight;
    int remaining_time;
} Job;

// Function to simulate Round Robin scheduling algorithm
void round_robin(Job jobs[], int n) {
    int total_remaining_time = 0;
    for (int i = 0; i < n; i++) {
        total_remaining_time += jobs[i].remaining_time = jobs[i].weight;
    }

    int current_time = 0;
    int index = 0;

    while (total_remaining_time > 0) {
        if (jobs[index].remaining_time > 0) {
            printf("Executing Job %d with weight %d at time %d\n", jobs[index].id, jobs[index].weight, current_time);
            if (jobs[index].remaining_time > jobs[index].weight) {
                current_time += jobs[index].weight;
                jobs[index].remaining_time -= jobs[index].weight;
                total_remaining_time -= jobs[index].weight;
            } else {
                current_time += jobs[index].remaining_time;
                total_remaining_time -= jobs[index].remaining_time;
                jobs[index].remaining_time = 0;
            }
        }
        index = (index + 1) % n;
    }
}

int main() {
    // Example jobs
    Job jobs[] = {
        {1, 1, 0},  // Job ID, Weight, Remaining Time
        {2, 2, 0},
        {3, 3, 0},
        {4, 4, 0},
        {5, 5, 0}
    };

    int n = sizeof(jobs) / sizeof(jobs[0]);

    printf("Round Robin Scheduling with Time Slice Equivalent to Weight:\n");
    round_robin(jobs, n);

    return 0;
}
