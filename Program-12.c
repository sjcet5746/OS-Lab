#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 3

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t mutex, full, empty;

void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) { // Produce 10 items
        item = rand() % 100; // Generate a random item
        sem_wait(&empty); // Wait if the buffer is full
        sem_wait(&mutex); // Lock the buffer
        buffer[in] = item; // Put the item into the buffer
        printf("Producer produced item %d at position %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE; // Move the 'in' pointer
        sem_post(&mutex); // Unlock the buffer
        sem_post(&full); // Signal that the buffer is not empty
        sleep(rand() % 2); // Simulate production time
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) { // Consume 10 items
        sem_wait(&full); // Wait if the buffer is empty
        sem_wait(&mutex); // Lock the buffer
        item = buffer[out]; // Take an item from the buffer
        printf("Consumer consumed item %d from position %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE; // Move the 'out' pointer
        sem_post(&mutex); // Unlock the buffer
        sem_post(&empty); // Signal that the buffer is not full
        sleep(rand() % 2); // Simulate consumption time
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);

    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producers[i], NULL, producer, NULL);
    }

    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    // Join threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
