#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Creating a child process
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) created.\n", getpid());
        printf("Child process is sleeping for 5 seconds...\n");
        sleep(5); // Simulating some work
        printf("Child process completed.\n");
        printf("Parent process ID is 1\n");
    } else {
        // Parent process
        printf("Parent process (PID: %d) created.\n", getpid());
        printf("Parent process is terminating now.\n");

        // Terminate parent process
        exit(0);
    }

    return 0;
}
