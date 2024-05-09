#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
bool *choosing;
int *number;
pthread_mutex_t lock;

void enter_region(int thread_id, int num_threads) {
    choosing[thread_id] = true;
    int max_number = 0;
    for (int i = 0; i < num_threads; ++i) {
        if (number[i] > max_number) {
            max_number = number[i];
        }
    }
    number[thread_id] = max_number + 1;
    choosing[thread_id] = false;

    for (int i = 0; i < num_threads; ++i) {
        while (choosing[i]) {}
        while ((number[i] != 0) && ((number[i] < number[thread_id]) || ((number[i] == number[thread_id]) && (i < thread_id)))) {}
    }
}

void leave_region(int thread_id) {
    number[thread_id] = 0;
}

void* increment(void* arg) {
    int* args = (int*)arg;
    int thread_id = args[0];
    int num_threads = args[1];
    enter_region(thread_id, num_threads);
    printf("Thread %d: Entering critical section\n", thread_id);
    // Critical Section: Increment
    usleep(900000);
    printf("Thread %d: Exiting critical section\n", thread_id);
    leave_region(thread_id);
    return NULL;
}

int main() {
    int num_threads;

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    pthread_t threads[num_threads];
    int thread_ids[num_threads];
    choosing = (bool*)malloc(sizeof(bool) * num_threads);
    number = (int*)malloc(sizeof(int) * num_threads);

    pthread_mutex_init(&lock, NULL);

    printf("Enter the sequence of thread IDs (0 to %d): ", num_threads - 1);
    for (int i = 0; i < num_threads; ++i) {
        scanf("%d", &thread_ids[i]);
        choosing[thread_ids[i]] = false;
        number[thread_ids[i]] = 0;
        pthread_create(&threads[i], NULL, increment, (void*)&(int[]){thread_ids[i], num_threads});
    }

    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    free(choosing);
    free(number);

    return 0;
}
