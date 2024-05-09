#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int num;
    pid_t parent_pid = getpid(); // Get the parent process ID

    printf("Parent process ID: %d\n", parent_pid);

    printf("Enter the number of child processes to create: ");
    scanf("%d", &num);

    for (int i = 0; i < num; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            printf("Fork failed\n");
            exit(1);
        } else if (pid == 0) {
            // Child process
            printf("Child process %d, ID: %d, Parent process ID: %d\n", i + 1, getpid(), getppid());
            exit(0);
        }
    }

    // Parent process waits for all child processes to finish
    for (int i = 0; i < num; i++) {
        wait(NULL);
    }

    return 0;
}