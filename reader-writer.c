#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, writeMutex;
int readers = 0;
int data = 1; // Shared data

void* reader(void* arg) {
    int member_id = *(int*)arg;
    printf("Team member %d is reading the file.\n", member_id);
    sem_wait(&mutex);
    readers++;
    if (readers == 1) {
        sem_wait(&writeMutex); // First reader waits for writers
    }
    sem_post(&mutex);

    // Read data
    printf("Team member %d is reading data: %d\n", member_id, data);

    sem_wait(&mutex);
    readers--;
    if (readers == 0) {
        sem_post(&writeMutex); // Last reader releases writers
    }
    sem_post(&mutex);
    return NULL;
}

void* writer(void* arg) {
    int member_id = *(int*)arg;
    sem_wait(&writeMutex);
    // Update data
    data = 2;
    printf("Team member %d is updating data to: %d\n", member_id, data);
    data++;
    sem_post(&writeMutex);
    return NULL;
}

int main() {
    int num_readers, num_writers;

    printf("Enter the number of readers: ");
    scanf("%d", &num_readers);

    printf("Enter the number of writers: ");
    scanf("%d", &num_writers);

    pthread_t readers_threads[num_readers], writer_threads[num_writers];
    int readers_ids[num_readers], writers_ids[num_writers];
    int sequence[num_readers + num_writers];
    
    sem_init(&mutex, 0, 1);
    sem_init(&writeMutex, 0, 1);

    // User input for the sequence
    printf("Enter the sequence of readers and writers (1 for reader, 0 for writer):\n");
    for (int i = 0; i < num_readers + num_writers; i++) {
        scanf("%d", &sequence[i]);
    }

    int reader_index = 0, writer_index = 0;
    for (int i = 0; i < num_readers + num_writers; i++) {
        if (sequence[i] == 1) {
            readers_ids[reader_index] = reader_index + 1;
            pthread_create(&readers_threads[reader_index], NULL, reader, &readers_ids[reader_index]);
            reader_index++;
        } else {
            writers_ids[writer_index] = writer_index + 1;
            pthread_create(&writer_threads[writer_index], NULL, writer, &writers_ids[writer_index]);
            writer_index++;
        }
    }

    // Join threads
    for (int i = 0; i < num_readers; i++) {
        pthread_join(readers_threads[i], NULL);
    }
    for (int i = 0; i < num_writers; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&writeMutex);

    return 0;
}
