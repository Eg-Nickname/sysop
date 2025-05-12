// ======================================================================================
// Program przyjmuje 4 argmunety, nazwę pamiędi dzielonej, nazwe semafora
// producenta, nazwe semafora consumenta  oraz nazwę pliiku. Odczytuje dane z
// bufora cyklicznego  z pamięci dzielonej, wypisuje je na standardowe wyjśćie
// oraz zapisuje w podanym pliku.
// ======================================================================================
// Jakub Kurek 13-05-2025
// ======================================================================================

#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <threads.h>
#include <unistd.h>

#include "check_error.h"
#include "ring_buf.h"
#include "semaphore.h"
#include "shared_mem.h"

char* shm_name = NULL;
// Producer semaphore name
char* prod_sem_name = NULL;
// Consumer semaphore name
char* con_sem_name = NULL;

// Random max and min sleep time in ms
#define RSLEEP_MAX_TIME 1000
#define RSLEEP_MIN_TIME 500

// Helper function to sleep in ms
int msleep(unsigned long msec);
// Sleeps random amout of ms
void rsleep(void) {
    msleep(rand() % (RSLEEP_MAX_TIME - RSLEEP_MIN_TIME) + RSLEEP_MIN_TIME);
}

int main(int argc, char** argv) {
    if (argc != 5) {
        fprintf(stderr, "Nie poprawna liczba argumentów: \n");
        fprintf(stderr,
                "%s ./shm_name ./producer_sem_name ./consumer_sem_name "
                "./file_to_write \n",
                argv[0]);
        _exit(1);
    }
    // vars for easier use of program args
    shm_name = argv[1];
    prod_sem_name = argv[2];
    con_sem_name = argv[3];
    char* write_file = argv[4];

    // Get prod sem
    sem_t* prod_sem = NULL;
    ChildCheckError(prod_sem = open_named_sem(prod_sem_name));
    // Get con sem
    sem_t* con_sem = NULL;
    ChildCheckError(con_sem = open_named_sem(con_sem_name));

    // Print value and adress of semaphores
    int prod_sem_val = 0;
    CheckError(get_sem_val(prod_sem, &prod_sem_val));
    int con_sem_val = 0;
    CheckError(get_sem_val(con_sem, &con_sem_val));
    printf(
        "[SHM_SEM CONSUMER] prod_sem val %d adr %p, con_sem val %d adr %p \n",
        prod_sem_val, (void*)prod_sem, con_sem_val, (void*)con_sem);

    // Get shared mem
    int shm_fd = 0;
    ChildCheckError(shm_fd = open_shm(shm_name));
    printf("[SHM_SEM CONSUMER] Shm fd %d\n", shm_fd);

    // Map shm to ring buffer
    Rb_ptr rb_ptr = (Rb_ptr)mmap(NULL, sizeof(RingBuf), PROT_READ | PROT_WRITE,
                                 MAP_SHARED, shm_fd, 0);
    if (rb_ptr == (void*)-1) {
        perror("mmap error");
        _exit(1);
    }

    // Open write file
    int write_fd = open(write_file, O_CREAT | O_WRONLY, 0644);
    if (write_fd == -1) {
        perror("Can't open file to read data from");
        _exit(1);
    }
    // ======================================================
    RingData consumer_data;
    while (1) {
        ChildCheckError(sem_w(con_sem));
        int read_pos = rb_pop(rb_ptr, &consumer_data);
        ChildCheckError(sem_p(prod_sem));
        // Check if consumer data signaled end of data
        int read_data_size = strnlen(consumer_data.element, RB_ELEMENT_SIZE);
        // 0 len str signals end of data to read
        if (read_data_size == 0) {
            break;
        }
        // Write data to file
        if (write(write_fd, &consumer_data.element, read_data_size) == -1) {
            perror("File write error");
            _exit(1);
        }
        // Write infromation to stdout
        int prod_sem_loop_val;
        int con_sem_loop_val;
        ChildCheckError(get_sem_val(prod_sem, &prod_sem_loop_val));
        ChildCheckError(get_sem_val(con_sem, &con_sem_loop_val));
        printf(
            "\n  [CONSUMER] con_sem_val: %d, prod_sem_val: %d, read bytes: %d "
            "from buf[%d] | %s",
            con_sem_loop_val, prod_sem_loop_val, read_data_size, read_pos,
            consumer_data.element);
        // Simulate working on data before next read from rb
        rsleep();
    }

    // ======================================================
    // Unmap shm
    if (munmap(rb_ptr, sizeof(RingBuf)) == -1) {
        perror("munmap error");
        _exit(1);
    }
    // Close shm
    ChildCheckError(close_shm(shm_fd));
    // Close write file
    if (close(write_fd) == -1) {
        perror("File close error");
        _exit(1);
    }
    printf("\n[SHM_SEM CONSUMER] Finished reading\n");
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
