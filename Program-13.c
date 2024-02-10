#include <stdio.h>
#include <stdlib.h>

#define NUM_PARTITIONS 5
#define MEMORY_SIZE 1000

typedef struct {
    int start_address;
    int size;
    int is_allocated;
} Partition;

Partition partitions[NUM_PARTITIONS];

void initialize_partitions() {
    int partition_size = MEMORY_SIZE / NUM_PARTITIONS;
    for (int i = 0; i < NUM_PARTITIONS; i++) {
        partitions[i].start_address = i * partition_size;
        partitions[i].size = partition_size;
        partitions[i].is_allocated = 0;
    }
}

void display_partitions() {
    printf("Partitions:\n");
    for (int i = 0; i < NUM_PARTITIONS; i++) {
        printf("Partition %d: Start Address: %d, Size: %d, Allocated: %s\n", i + 1, partitions[i].start_address,
               partitions[i].size, partitions[i].is_allocated ? "Yes" : "No");
    }
}

int allocate_first_fit(int size) {
    for (int i = 0; i < NUM_PARTITIONS; i++) {
        if (!partitions[i].is_allocated && partitions[i].size >= size) {
            partitions[i].is_allocated = 1;
            return partitions[i].start_address;
        }
    }
    return -1; // No suitable partition found
}

int allocate_worst_fit(int size) {
    int max_size = -1;
    int index = -1;
    for (int i = 0; i < NUM_PARTITIONS; i++) {
        if (!partitions[i].is_allocated && partitions[i].size >= size && partitions[i].size > max_size) {
            max_size = partitions[i].size;
            index = i;
        }
    }
    if (index != -1) {
        partitions[index].is_allocated = 1;
        return partitions[index].start_address;
    }
    return -1; // No suitable partition found
}

int allocate_best_fit(int size) {
    int min_size = MEMORY_SIZE + 1;
    int index = -1;
    for (int i = 0; i < NUM_PARTITIONS; i++) {
        if (!partitions[i].is_allocated && partitions[i].size >= size && partitions[i].size < min_size) {
            min_size = partitions[i].size;
            index = i;
        }
    }
    if (index != -1) {
        partitions[index].is_allocated = 1;
        return partitions[index].start_address;
    }
    return -1; // No suitable partition found
}

int main() {
    initialize_partitions();
    display_partitions();

    int size = 300;
    printf("\nAllocating memory of size %d using First Fit...\n", size);
    int first_fit_address = allocate_first_fit(size);
    if (first_fit_address != -1) {
        printf("Memory allocated at address: %d\n", first_fit_address);
    } else {
        printf("Memory allocation failed. No suitable partition found.\n");
    }
    display_partitions();

    size = 400;
    printf("\nAllocating memory of size %d using Worst Fit...\n", size);
    int worst_fit_address = allocate_worst_fit(size);
    if (worst_fit_address != -1) {
        printf("Memory allocated at address: %d\n", worst_fit_address);
    } else {
        printf("Memory allocation failed. No suitable partition found.\n");
    }
    display_partitions();

    size = 200;
    printf("\nAllocating memory of size %d using Best Fit...\n", size);
    int best_fit_address = allocate_best_fit(size);
    if (best_fit_address != -1) {
        printf("Memory allocated at address: %d\n", best_fit_address);
    } else {
        printf("Memory allocation failed. No suitable partition found.\n");
    }
    display_partitions();

    return 0;
}
