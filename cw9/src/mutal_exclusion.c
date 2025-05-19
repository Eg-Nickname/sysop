#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>

int THREAD_LOG_START = 3; // 3 is messages before thread dependent info
// Globlas for threads
int CRIT_SECTION_COUNT = 0;
int THREAD_COUNT = 0;
int GLOBAL_COUNTER = 0;
pthread_mutex_t thread_mutex;

void *thread_fn(void *);

// Random max and min sleep time in ms
#define RSLEEP_MAX_TIME 1000
#define RSLEEP_MIN_TIME 700

// Helper function to sleep in ms
int msleep(unsigned long msec);
// Sleeps random amout of ms
void rsleep(void) {
    unsigned long msec =
        rand() % (RSLEEP_MAX_TIME - RSLEEP_MIN_TIME) + RSLEEP_MIN_TIME;
    // printf("Proc pid: %d sleeping for %lu ms", getpid(), msec);
    msleep(msec);
}

int main(int argc, char **argv) {
    // Clear screen for proper printing behaviour
    if (system("clear") == -1) {
        perror("Error in call to system() function");
        exit(EXIT_FAILURE);
    }

    // Validate arguments
    if (argc != 3) {
        fprintf(stderr, "Nie poprawna liczba argumentów: \n");
        fprintf(stderr, "%s thread_count crit_section_count \n", argv[0]);
        exit(1);
    }

    // Ppulate globals wiht correct values
    THREAD_COUNT = atoi(argv[1]);
    CRIT_SECTION_COUNT = atoi(argv[2]);
    THREAD_LOG_START += THREAD_COUNT;

    // Create mutex
    int mutex_init_ret = 0;
    if ((mutex_init_ret = pthread_mutex_init(&thread_mutex, NULL) != 0)) {
        fprintf(stderr, "Mutex creation error %s \n", strerror(mutex_init_ret));
        exit(1);
    }
    printf("Thread mutex created at %p \n", (void *)&thread_mutex);

    // Create thread_handle_buf
    pthread_t thread_handles[THREAD_COUNT];
    int thread_args[THREAD_COUNT];

    // Create threads
    for (int i = 0; i < THREAD_COUNT; i++) {
        thread_args[i] = i;
        int thread_create_ret = 0;
        if ((thread_create_ret =
                 pthread_create(&thread_handles[i], NULL, &thread_fn,
                                &thread_args[i]) != 0)) {
            fprintf(stderr, "Mutex create error %s \n",
                    strerror(thread_create_ret));
            exit(1);
        }
        // Print thread infromation
        printf("Createad thread %d with id %lu \n", i, thread_handles[i]);
    }

    // Join all threads
    for (int i = 0; i < THREAD_COUNT; i++) {
        int thread_join_ret = 0;
        if ((thread_join_ret = pthread_join(thread_handles[i], NULL) != 0)) {
            fprintf(stderr, "Thread join error %s \n",
                    strerror(thread_join_ret));
        }
    }

    // Fix print position
    printf("\033[%d;%dH\033[2K", THREAD_LOG_START + THREAD_COUNT + 1, 0);
    printf("Global counter %d expected %d \n", GLOBAL_COUNTER,
           THREAD_COUNT * CRIT_SECTION_COUNT);

    // Destroy mutex
    int mutex_destroy_ret = 0;
    if ((mutex_destroy_ret = pthread_mutex_destroy(&thread_mutex) != 0)) {
        fprintf(stderr, "Mutex destroy error %s \n",
                strerror(mutex_destroy_ret));
        exit(1);
    }

    return 0;
}

void *thread_fn(void *arg) {
    int thread_num = *((int *)arg);
    int thread_print_line = THREAD_LOG_START + thread_num;
    rsleep();
    for (int i = 0; i < CRIT_SECTION_COUNT; i++) {
        // Print thread information
        printf("\033[%d;%dH\033[2K", thread_print_line, 0);
        printf("Thread %d at iteration %d \n", thread_num, i);
        // Random sleep before trying to enter crit section
        rsleep();
        // ========================
        // Enter crit section
        // ========================
        int mutex_lock_ret = 0;
        if ((mutex_lock_ret = pthread_mutex_lock(&thread_mutex) != 0)) {
            fprintf(stderr, "Mutex lock error %s \n", strerror(mutex_lock_ret));
        }
        // Print that thread is in the crit section
        printf("\033[%d;%dH\033[2K", thread_print_line, 40);
        printf("Thread %d at crit section %d with counter at start %d \n",
               thread_num, i, GLOBAL_COUNTER);

        // Counter operations
        int local_counter = GLOBAL_COUNTER;
        local_counter++;
        // Random sleep before writing back to global counter and exiting crit
        // section
        rsleep();

        GLOBAL_COUNTER = local_counter;
        // ========================
        // Exit crit seciton
        // ========================
        int mutex_unlock_ret = 0;
        if ((mutex_unlock_ret = pthread_mutex_unlock(&thread_mutex) != 0)) {
            fprintf(stderr, "Mutex unlock error %s \n",
                    strerror(mutex_lock_ret));
        }
    }
    // Print thread finished
    printf("\033[%d;%dH\033[2K", thread_print_line, 0);
    printf("Thread %d finished! \n", thread_num);
    return NULL;
}

int msleep(unsigned long msec) {
    struct timespec ts;
    int res;

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = thrd_sleep(&ts, &ts);
    } while (res);

    return res;
}
