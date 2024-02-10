#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CHAIRS 5

sem_t barber_sem;
sem_t customer_sem;
pthread_mutex_t mutex;

int num_waiting = 0;
int num_served = 0;

void* barber_thread(void* arg) {
    while (num_served < 10) { // Simulate serving 10 customers
        sem_wait(&customer_sem); // Wait for a customer to arrive
        pthread_mutex_lock(&mutex);
        num_waiting--;
        pthread_mutex_unlock(&mutex);
        sem_post(&barber_sem); // Signal that the barber is ready to cut hair
        printf("Barber is cutting hair\n");
        sleep(2); // Simulate cutting hair
        num_served++;
    }
    printf("Barber is going home\n");
    pthread_exit(NULL);
}

void* customer_thread(void* arg) {
    int id = *(int*)arg;
    pthread_mutex_lock(&mutex);
    if (num_waiting < NUM_CHAIRS) {
        printf("Customer %d is waiting\n", id);
        num_waiting++;
        pthread_mutex_unlock(&mutex);
        sem_post(&customer_sem); // Signal that a customer has arrived
        sem_wait(&barber_sem); // Wait for the barber to become available
        printf("Customer %d is getting a haircut\n", id);
    } else {
        printf("Customer %d left - no chairs available\n", id);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t barber, customers[20];
    int ids[20];

    // Initialize semaphores and mutex
    sem_init(&barber_sem, 0, 0);
    sem_init(&customer_sem, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create barber thread
    pthread_create(&barber, NULL, barber_thread, NULL);

    // Create customer threads
    for (int i = 0; i < 20; i++) {
        ids[i] = i + 1;
        pthread_create(&customers[i], NULL, customer_thread, &ids[i]);
        usleep(rand() % 100000); // Random delay between customer arrivals
    }

    // Join threads
    pthread_join(barber, NULL);
    for (int i = 0; i < 20; i++) {
        pthread_join(customers[i], NULL);
    }

    // Clean up
    sem_destroy(&barber_sem);
    sem_destroy(&customer_sem);
    pthread_mutex_destroy(&mutex);

    return 0;
}
