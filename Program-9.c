#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define SHARED_MEM_SIZE 4096

int main() {
    // Create a shared memory region
    void *shared_memory = mmap(NULL, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_memory == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        printf("Child process writing to shared memory\n");
        sprintf((char*)shared_memory, "Hello from child process!");
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        printf("Parent process waiting for child...\n");
        wait(NULL); // Wait for the child process to complete
        printf("Parent process reading from shared memory\n");
        printf("Received message from child: %s\n", (char*)shared_memory);

        // Unmap the shared memory region
        if (munmap(shared_memory, SHARED_MEM_SIZE) == -1) {
            perror("munmap");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
