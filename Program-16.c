#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESSES 5
#define NUM_RESOURCES 3

int available[NUM_RESOURCES];
int max[NUM_PROCESSES][NUM_RESOURCES];
int allocation[NUM_PROCESSES][NUM_RESOURCES];
int need[NUM_PROCESSES][NUM_RESOURCES];
bool finished[NUM_PROCESSES] = {false};

void initialize_data() {
    // Initialize available resources
    available[0] = 3;
    available[1] = 3;
    available[2] = 2;

    // Initialize maximum resource allocation for each process
    max[0][0] = 7; max[0][1] = 5; max[0][2] = 3;
    max[1][0] = 3; max[1][1] = 2; max[1][2] = 2;
    max[2][0] = 9; max[2][1] = 0; max[2][2] = 2;
    max[3][0] = 2; max[3][1] = 2; max[3][2] = 2;
    max[4][0] = 4; max[4][1] = 3; max[4][2] = 3;

    // Initialize allocation and need matrices
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            allocation[i][j] = 0;
            need[i][j] = max[i][j];
        }
    }
}

bool is_safe_state(int process, int request[]) {
    // Check if the request can be granted
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (request[i] > need[process][i] || request[i] > available[i]) {
            return false; // Request cannot be granted
        }
    }

    // Try to allocate the resources temporarily
    for (int i = 0; i < NUM_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Check if the system is in a safe state after the allocation
    bool safe_state = true;
    bool can_finish[NUM_PROCESSES];
    for (int i = 0; i < NUM_PROCESSES; i++) {
        can_finish[i] = finished[i]; // Initialize with current finished status
    }
    for (int i = 0; i < NUM_RESOURCES; i++) {
        int work = available[i];
        int j = 0;
        while (j < NUM_PROCESSES) {
            if (!can_finish[j] && need[j][i] <= work) {
                work += allocation[j][i];
                can_finish[j] = true;
                j = 0; // Start from the beginning to check again
            } else {
                j++;
            }
        }
        for (int k = 0; k < NUM_PROCESSES; k++) {
            if (!can_finish[k]) {
                safe_state = false;
                break;
            }
        }
        if (!safe_state) {
            break;
        }
    }

    // Rollback the allocation if the state is not safe
    if (!safe_state) {
        for (int i = 0; i < NUM_RESOURCES; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
    }

    return safe_state;
}

void request_resources(int process, int request[]) {
    printf("Process %d requesting resources: ", process);
    for (int i = 0; i < NUM_RESOURCES; i++) {
        printf("%d ", request[i]);
    }
    printf("\n");

    if (is_safe_state(process, request)) {
        printf("Request granted. Current state:\n");
        printf("Available: %d %d %d\n", available[0], available[1], available[2]);
        printf("Allocation:\n");
        for (int i = 0; i < NUM_PROCESSES; i++) {
            printf("Process %d: %d %d %d\n", i, allocation[i][0], allocation[i][1], allocation[i][2]);
        }
        printf("Need:\n");
        for (int i = 0; i < NUM_PROCESSES; i++) {
            printf("Process %d: %d %d %d\n", i, need[i][0], need[i][1], need[i][2]);
        }
    } else {
        printf("Request denied. System in unsafe state.\n");
    }
}

int main() {
    initialize_data();

    // Example requests
    int request1[NUM_RESOURCES] = {0, 1, 0};
    int request2[NUM_RESOURCES] = {2, 0, 0};
    int request3[NUM_RESOURCES] = {3, 0, 2};
    int request4[NUM_RESOURCES] = {2, 1, 1};
    int request5[NUM_RESOURCES] = {0, 0, 2};

    request_resources(1, request1);
    printf("\n");
    request_resources(4, request2);
    printf("\n");
    request_resources(0, request3);
    printf("\n");
    request_resources(2, request4);
    printf("\n");
    request_resources(3, request5);

    return 0;
}
