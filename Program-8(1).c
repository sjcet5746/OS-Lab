#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PORTS 5

sem_t port_sem;

void* open_port(void* arg) {
    int port_num = *((int*)arg);
    printf("Thread %d is trying to open port %d\n", port_num, port_num);
    sem_wait(&port_sem); // Decrement semaphore value
    printf("Thread %d has opened port %d\n", port_num, port_num);
    sleep(2); // Simulating usage of the port
    printf("Thread %d is releasing port %d\n", port_num, port_num);
    sem_post(&port_sem); // Increment semaphore value
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_PORTS];
    int port_numbers[NUM_PORTS];

    sem_init(&port_sem, 0, NUM_PORTS); // Initialize semaphore with the number of available ports

    // Create threads to open ports
    for (int i = 0; i < NUM_PORTS; i++) {
        port_numbers[i] = i + 1;
        pthread_create(&threads[i], NULL, open_port, &port_numbers[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_PORTS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&port_sem); // Destroy semaphore
    return 0;
}
