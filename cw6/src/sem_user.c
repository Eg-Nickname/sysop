#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>
#include <unistd.h>

#include "semaphore.h"

/*
=======================================================
Makro CheckError: wskazuj lokalizacje bledu, wypisuje nazwe
przekazywanego argumentu (#Arg) i konczy program.
=======================================================
*/

#define CheckError(Arg)                                                        \
    if (!(Arg)) {                                                              \
        fprintf(stderr, "[ERROR] %s:%d (%s) -> CheckError argument: %s\n",     \
                __FILE__, __LINE__, __func__, #Arg);                           \
        _exit(EXIT_FAILURE);                                                   \
    }

// Random max and min sleep time in ms
#define RSLEEP_MAX_TIME 500
#define RSLEEP_MIN_TIME 200

// Helper function to sleep in ms
int msleep(unsigned long msec);
// Sleeps random amout of ms
void rsleep(void) {
    unsigned long msec =
        rand() % (RSLEEP_MAX_TIME - RSLEEP_MIN_TIME) + RSLEEP_MIN_TIME;
    // printf("Proc pid: %d sleeping for %lu ms", getpid(), msec);
    msleep(msec);
}

int main(int argc, char** argv) {
    if (argc != 4) {
        fprintf(stderr, "Nie poprawna liczba argumentów (%d): \n", argc);
        fprintf(stderr,
                "%s ./counter_file crit_section_count semaphore_name \n",
                argv[0]);
        _exit(1);
    }

    // Parse critical sections count from argv
    int crit_section_count = 0;
    if (sscanf(argv[2], "%d", &crit_section_count) != 1) {
        fprintf(stderr, "Invalid child proces count.\n");
        exit(1);
    }

    // Process pid for debug information
    int pid = getpid();
    // Seed rand function for sleeping using time and pid
    srand(time(NULL) + pid);

    // Num file name
    char* counter_file_name = argv[1];
    // Get sync semaphore name
    char* sem_name = argv[3];
    // Get sem_ptr from sem name
    sem_t* sem_ptr;
    CheckError(sem_ptr = open_named_sem(sem_name));
    printf("[PROC %d] Opened sem \n", pid);

    for (int i = 0; i < crit_section_count; i++) {
        int sem_val = 0;
        CheckError(get_sem_val(sem_ptr, &sem_val));
        printf("[PROC %d] Before crit section %d with sem val: %d \n", pid, i,
               sem_val);
        // ======================================
        // CRITICAL SECTION BEGIN
        // ======================================
        CheckError(sem_w(sem_ptr));
        int counter_buf = 0;
        CheckError(get_sem_val(sem_ptr, &sem_val));
        printf("\t[PROC %d] Inside crit section %d with sem val: %d \n", pid, i,
               sem_val);
        // Open file to read counter
        int fd = open(counter_file_name, O_RDONLY);
        if (fd == -1) {
            perror("Can't open file for counting");
            exit(1);
        }
        // Read counter from file
        if (read(fd, &counter_buf, sizeof(int)) == -1) {
            perror("File read error");
            exit(1);
        }
        // Close file
        if (close(fd) == -1) {
            perror("File close error");
            exit(1);
        }
        // Increment value and sleep for simulating expensive computation
        counter_buf++;
        rsleep();
        // Open file to write counter
        fd = open(counter_file_name, O_WRONLY);
        if (fd == -1) {
            perror("Can't open file for counting");
            exit(1);
        }
        // Write counter from file
        if (write(fd, &counter_buf, sizeof(int)) == -1) {
            perror("File write error");
            exit(1);
        }
        // Close file
        if (close(fd) == -1) {
            perror("File close error");
            exit(1);
        }
        CheckError(sem_p(sem_ptr));
        // ======================================
        // CRITICAL SECTION END
        // ======================================
        CheckError(get_sem_val(sem_ptr, &sem_val));
        printf("[PROC %d] After crit section %d with sem val: %d \n", pid, i,
               sem_val);
        rsleep();
    }

    printf("[PROC %d] ended \n", pid);
    return 0;
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
