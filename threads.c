#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_MESSAGE_LENGTH 100

typedef struct {
    int id;
    char message[MAX_MESSAGE_LENGTH];
} ThreadData;

void* print_message(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    printf("Thread %d: %s\n", data->id, data->message);
    pthread_exit(NULL);
}

int main() {
    int num_threads;
    printf("Enter the number of threads to create: ");
    scanf("%d", &num_threads);

    pthread_t* threads = (pthread_t*)malloc(num_threads * sizeof(pthread_t));
    ThreadData* thread_data = (ThreadData*)malloc(num_threads * sizeof(ThreadData));

    for (int i = 0; i < num_threads; i++) {
        printf("Enter message for Thread %d: ", i);
        scanf("%s", thread_data[i].message);
        thread_data[i].id = i;
    }

    // Create threads and print messages
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, print_message, (void*)&thread_data[i]);
        pthread_join(threads[i], NULL); // Wait for each thread to finish before proceeding to the next one
    }

    free(threads);
    free(thread_data);

    return 0;
}
