#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

int main() {
    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());

        // Execute a new program using exec
        execlp("ls", "ls", "-l", NULL);

        // exec will only return if there's an error
        perror("Exec failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);

        // Wait for the child process to finish
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process exited abnormally\n");
        }

        // Open a directory
        DIR *dir = opendir(".");
        if (dir == NULL) {
            perror("Failed to open directory");
            exit(EXIT_FAILURE);
        }

        // Read directory contents
        struct dirent *entry;
        printf("Directory contents:\n");
        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
        }

        // Close the directory
        closedir(dir);
    }

    return 0;
}
