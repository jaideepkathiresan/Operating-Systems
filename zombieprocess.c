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
        exit(0);
    } else {
        // Parent process
        printf("Parent process (PID: %d) created.\n", getpid());
        printf("Parent process is waiting for child process to complete...\n");

        // Wait for the child process to complete
        sleep(10); // Waiting longer than child's sleep time to observe zombie state

        printf("Parent process completed.\n");
    }
    

    return 0;
}


