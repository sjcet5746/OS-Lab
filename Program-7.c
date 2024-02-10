#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_PROCESSES 10
#define MAX_WAIT_TIME 10

// Structure to represent a process
typedef struct {
    int pid;
    int priority;
    int remaining_time;
} Process;

// Structure to represent a node in the priority queue
typedef struct {
    Process process;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(Process process) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->process = process;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a process into the priority queue
void insert(Node** head, Process process) {
    Node* newNode = createNode(process);
    if (*head == NULL || process.priority < (*head)->process.priority) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL && current->next->process.priority <= process.priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to remove and return the highest priority process from the priority queue
Process dequeue(Node** head) {
    if (*head == NULL) {
        exit(EXIT_FAILURE);
    }
    Process process = (*head)->process;
    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
    return process;
}

// Function to simulate priority scheduling algorithm with a maximum waiting time constraint
void priority_scheduling(Process processes[], int n) {
    Node* priorityQueue = NULL;
    int timer = 0;

    while (true) {
        // Insert processes into the priority queue based on their arrival time
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && processes[i].remaining_time <= MAX_WAIT_TIME) {
                insert(&priorityQueue, processes[i]);
                processes[i].remaining_time = 0;  // Mark the process as inserted
            }
        }

        // Execute processes with priority <= 10 for at least 1 second
        while (priorityQueue != NULL && priorityQueue->process.priority <= 10) {
            Process process = dequeue(&priorityQueue);
            printf("Executing Process %d with priority %d at time %d\n", process.pid, process.priority, timer);
            sleep(1);  // Simulate process execution for 1 second
            timer++;
            process.remaining_time--;
            if (process.remaining_time > 0) {
                insert(&priorityQueue, process);  // Reinsert the process into the queue if it's not finished
            }
        }

        // Check if all processes are executed
        bool allExecuted = true;
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                allExecuted = false;
                break;
            }
        }
        if (allExecuted) {
            break;
        }

        // Increment timer
        timer++;
    }
}

int main() {
    // Example processes
    Process processes[MAX_PROCESSES] = {
        {1, 1, 15},  // Process ID, Priority, Remaining Time
        {2, 2, 5},
        {3, 5, 8},
        {4, 8, 20},
        {5, 10, 3}
    };

    int n = sizeof(processes) / sizeof(processes[0]);

    printf("Priority Scheduling with Maximum Waiting Time Constraint:\n");
    priority_scheduling(processes, n);

    return 0;
}
