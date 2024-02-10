#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];
sem_t max_philosophers_sem;

void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(rand() % 3); // Simulate thinking

        sem_wait(&max_philosophers_sem); // Wait if maximum philosophers are eating
        pthread_mutex_lock(&forks[left_fork]); // Pick up left fork
        pthread_mutex_lock(&forks[right_fork]); // Pick up right fork

        printf("Philosopher %d is eating\n", id);
        sleep(rand() % 3); // Simulate eating

        pthread_mutex_unlock(&forks[left_fork]); // Put down left fork
        pthread_mutex_unlock(&forks[right_fork]); // Put down right fork
        sem_post(&max_philosophers_sem); // Signal that a philosopher has finished eating
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    sem_init(&max_philosophers_sem, 0, NUM_PHILOSOPHERS - 1); // Initialize semaphore

    // Initialize mutexes for forks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores and mutexes
    sem_destroy(&max_philosophers_sem);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
