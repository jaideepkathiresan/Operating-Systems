#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t mutex, writeblock;
int data = 0, rcount = 0;

void *reader(void *arg)
{
    int f;
    f = *((int *)arg);
    sem_wait(&mutex);
    rcount = rcount + 1;
    if (rcount == 1)
        sem_wait(&writeblock); // If it's the first reader, block writers
    sem_post(&mutex);

    printf("Data read by the reader%d is %d\n", f, data);
    sleep(1);

    sem_wait(&mutex);
    rcount = rcount - 1;
    if (rcount == 0)
        sem_post(&writeblock); // If no readers, unblock writers
    sem_post(&mutex);
    return NULL;
}

void *writer(void *arg)
{
    int f;
    f = *((int *)arg);
    sem_wait(&writeblock); // Wait for permission to write
    printf("Enter the value to be written by writer%d: ", f);
    scanf("%d", &data);
    printf("Data written by the writer%d is %d\n", f, data);
    sleep(1);
    sem_post(&writeblock); // Release the write lock
    return NULL;
}

int main()
{
    int i, num_readers, num_writers;
    printf("Enter the number of readers: ");
    scanf("%d", &num_readers);
    printf("Enter the number of writers: ");
    scanf("%d", &num_writers);
    pthread_t rtid[num_readers], wtid[num_writers];
    sem_init(&mutex, 0, 1);
    sem_init(&writeblock, 0, 1);

    for (i = 0; i < num_writers + num_readers; i++)
    {
        if (i % 2 == 0)
        { // Alternate between reader and writer
            if (pthread_create(&rtid[i / 2], NULL, reader, (void *)&i) != 0)
            {
                printf("Failed to create reader thread %d\n", i);
                return -1;
            }
        }
        else
        {
            if (pthread_create(&wtid[i / 2], NULL, writer, (void *)&i) != 0)
            {
                printf("Failed to create writer thread %d\n", i);
                return -1;
            }
        }
    }

    for (i = 0; i < num_writers; i++)
    {
        if (pthread_join(wtid[i], NULL) != 0)
        {
            printf("Failed to join writer thread %d\n", i);
            return -1;
        }
    }
    for (i = 0; i < num_readers; i++)
    {
        if (pthread_join(rtid[i], NULL) != 0)
        {
            printf("Failed to join reader thread %d\n", i);
            return -1;
        }
    }
    return 0;
}
