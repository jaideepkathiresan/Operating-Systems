#include <stdio.h>
#include <pthread.h>

int x = 10;
pthread_mutex_t lock;

void* increment(void* arg) {
    pthread_mutex_lock(&lock);
    x++;
    printf("Process A: Incremented x to %d\n", x);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* decrement(void* arg) {
    pthread_mutex_lock(&lock);
    x--;
    printf("Process B: Decremented x to %d\n", x);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t threadA, threadB;
    int choice;

    pthread_mutex_init(&lock, NULL);

    printf("Choose which thread to execute first (1 for increment, 2 for decrement): ");
    scanf("%d", &choice);

    if (choice == 1) {
        pthread_create(&threadA, NULL, increment, NULL);
        pthread_create(&threadB, NULL, decrement, NULL);
    } else {
        pthread_create(&threadB, NULL, decrement, NULL);
        pthread_create(&threadA, NULL, increment, NULL);
    }

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}
