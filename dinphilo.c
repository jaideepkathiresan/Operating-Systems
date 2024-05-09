#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };

sem_t mutex;
sem_t S[N];

void* philosopher(void* num)
{
    int* i = num;
    int phnum = *i;

    while (1) {
        // No automatic transitioning between states here
        sleep(1);
    }
}

int main()
{
    int i;
    pthread_t thread_id[N];

    // initialize the semaphores
    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);

    for (i = 0; i < N; i++) {
        // create philosopher processes
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    char choice;
    int phnum;

    while (1) {
        printf("Select an action:\n");
        printf("1. Make a philosopher hungry\n");
        printf("2. Make a philosopher think\n");
        printf("3. Make a philosopher eat\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                printf("Enter the philosopher number to make hungry: ");
                scanf("%d", &phnum);
                state[phnum-1] = HUNGRY;
                printf("Philosopher %d is now hungry\n", phnum);
                break;
            case '2':
                printf("Enter the philosopher number to make think: ");
                scanf("%d", &phnum);
                state[phnum-1] = THINKING;
                printf("Philosopher %d is now thinking\n", phnum);
                break;
            case '3':
                printf("Enter the philosopher number to make eat: ");
                scanf("%d", &phnum);
                state[phnum-1] = EATING;
                printf("Philosopher %d is now eating\n", phnum);
                break;
            case '4':
                printf("Exiting...\n");
                sem_destroy(&mutex);
                for (i = 0; i < N; i++)
                    sem_destroy(&S[i]);
                for (i = 0; i < N; i++)
                    pthread_join(thread_id[i], NULL);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
/*
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

int state[N];
int phil[N] = {0, 1, 2, 3, 4};
int eating_sequence[N] = {1, 3, 0, 2, 4};  // Predefined sequence

pthread_mutex_t mutex;
pthread_cond_t condition[N];

void test(int phnum) {
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[phnum] = EATING;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d\n", phnum + 1, LEFT + 1, phnum + 1);
        printf("Philosopher %d is Eating\n", phnum + 1);
        pthread_cond_signal(&condition[phnum]);
    }
}

void take_fork(int phnum) {
    pthread_mutex_lock(&mutex);
    state[phnum] = HUNGRY;
    printf("Philosopher %d is Hungry\n", phnum + 1);
    test(phil[phnum]);
    while (state[phnum] != EATING)
        pthread_cond_wait(&condition[phnum], &mutex);
    pthread_mutex_unlock(&mutex);
}

void put_fork(int phnum) {
    pthread_mutex_lock(&mutex);
    state[phnum] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d is thinking\n", phnum + 1);
    test(LEFT);
    test(RIGHT);
    pthread_mutex_unlock(&mutex);
}

void* philospher(void* num) {
    int* i = num;
    sleep(1);
    take_fork(*i);
    sleep(0);
    put_fork(*i);
    return NULL;
}

int main() {
    int i;
    pthread_t thread_id[N];
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < N; i++)
        pthread_cond_init(&condition[i], NULL);

    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philospher, &eating_sequence[i]);
        pthread_join(thread_id[i], NULL);  // Wait for the philosopher to finish eating
    }
}
*/