#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PORTS 5

pthread_mutex_t port_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t port_available = PTHREAD_COND_INITIALIZER;
int available_ports = NUM_PORTS;

void* open_port(void* arg) {
    int port_num = *((int*)arg);
    printf("Thread %d is trying to open port %d\n", port_num, port_num);
    pthread_mutex_lock(&port_mutex); // Acquire lock
    while (available_ports == 0) {
        pthread_cond_wait(&port_available, &port_mutex); // Wait if no ports available
    }
    available_ports--;
    printf("Thread %d has opened port %d\n", port_num, port_num);
    pthread_mutex_unlock(&port_mutex); // Release lock
    sleep(2); // Simulating usage of the port
    pthread_mutex_lock(&port_mutex); // Acquire lock
    available_ports++;
    printf("Thread %d is releasing port %d\n", port_num, port_num);
    pthread_cond_signal(&port_available); // Signal that port is available
    pthread_mutex_unlock(&port_mutex); // Release lock
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_PORTS];
    int port_numbers[NUM_PORTS];

    // Create threads to open ports
    for (int i = 0; i < NUM_PORTS; i++) {
        port_numbers[i] = i + 1;
        pthread_create(&threads[i], NULL, open_port, &port_numbers[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_PORTS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
