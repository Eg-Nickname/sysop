#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
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
#define RSLEEP_MAX_TIME 500
#define RSLEEP_MIN_TIME 200

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
                "./file_to_read \n",
                argv[0]);
        _exit(1);
    }
    // vars for easier use of program args
    shm_name = argv[1];
    prod_sem_name = argv[2];
    con_sem_name = argv[3];
    char* read_file = argv[4];

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
        "[SHM_SEM PRODUCER] prod_sem val %d adr %p, con_sem val %d adr %p \n",
        prod_sem_val, (void*)prod_sem, con_sem_val, (void*)con_sem);

    // Get shared mem
    int shm_fd = 0;
    ChildCheckError(shm_fd = open_shm(shm_name));
    printf("[SHM_SEM PRODUCER] Shm fd %d \n", shm_fd);

    // Map shm to ring buffer
    Rb_ptr rb_ptr = (Rb_ptr)mmap(NULL, sizeof(RingBuf), PROT_READ | PROT_WRITE,
                                 MAP_SHARED, shm_fd, 0);
    if (rb_ptr == (void*)-1) {
        perror("mmap error");
        _exit(1);
    }

    // Open write file
    int read_fd = open(read_file, O_RDONLY, 0644);
    if (read_fd == -1) {
        perror("Can't open file to read data from");
        _exit(1);
    }
    // ======================================================
    RingData producer_data;
    while (1) {
        // Read data from file
        int bytes_read =
            read(read_fd, &producer_data.element, sizeof(producer_data));
        if (bytes_read == -1) {
            perror("Read file error");
            _exit(1);
        }
        // Null terminate shorter string than buf size
        // If read bytes are 0 we send just '\0' to signal end of data
        if (bytes_read < RB_ELEMENT_SIZE) {
            producer_data.element[bytes_read] = '\0';
        }

        // Write infromation to stdout
        int prod_sem_loop_val;
        int con_sem_loop_val;

        // Insert data into ringbuf section
        ChildCheckError(sem_w(prod_sem));
        int write_pos = rb_push(rb_ptr, producer_data);
        ChildCheckError(sem_p(con_sem));

        ChildCheckError(get_sem_val(prod_sem, &prod_sem_loop_val));
        ChildCheckError(get_sem_val(con_sem, &con_sem_loop_val));
        printf(
            "\n  [PRODUCER] con_sem_val: %d, prod_sem_val: %d, bytes written: "
            "%d at buf[%d] | %s",
            con_sem_loop_val, prod_sem_loop_val, bytes_read, write_pos,
            producer_data.element);

        // End reading if eof
        if (bytes_read == 0) {
            break;
        }
        // Simulate working on data before next write to rb
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
    if (close(read_fd) == -1) {
        perror("File close error");
        _exit(1);
    }
    printf("\n[SHM_SEM PRODUCER] Finished writing\n");
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
