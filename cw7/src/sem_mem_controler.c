#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
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

void exit_fn(void) {
    CheckError(destroy_named_sem(prod_sem_name));
    CheckError(destroy_named_sem(con_sem_name));
    CheckError(destroy_shm(shm_name));
}

void sigint_handler(int _) { exit(EXIT_SUCCESS); }

int main(int argc, char** argv) {
    printf("Prodcon_sem_mem controler \n");

    // Validate arguments
    if (argc != 8) {
        fprintf(stderr, "Nie poprawna liczba argumentów: \n");
        fprintf(stderr,
                "%s ./shm_name ./producer_sem_name ./consumer_sem_name "
                "./producer_prog.x ./consumner_prog.x "
                "./file_to_read ./file_to_write \n",
                argv[0]);
        exit(1);
    }
    // vars for easier use of program args
    shm_name = argv[1];
    prod_sem_name = argv[2];
    con_sem_name = argv[3];
    char* producer_prog = argv[4];
    char* consumer_prog = argv[5];
    char* read_file = argv[6];
    char* write_file = argv[7];

    // Declare atexit function closing sem and shm
    if (atexit(exit_fn) != 0) {
        perror("atexit error");
        exit(1);
    }
    // Set SIGINT handling
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("Cant set custom handling for SIGINT");
        exit(EXIT_FAILURE);
    }
    sem_t* prod_sem;
    sem_t* con_sem;
    // Create sem
    CheckError(prod_sem = create_named_sem(prod_sem_name, RB_BUF_ELEMENTS));
    CheckError(con_sem = create_named_sem(con_sem_name, 0));

    // Print value and adress of semaphores
    int prod_sem_val = 0;
    CheckError(get_sem_val(prod_sem, &prod_sem_val));
    int con_sem_val = 0;
    CheckError(get_sem_val(con_sem, &con_sem_val));
    printf("[SHM_SEM MANAGER] prod_sem val %d adr %p, con_sem val %d adr %p \n",
           prod_sem_val, (void*)prod_sem, con_sem_val, (void*)con_sem);

    // Create shm
    int shm_fd = 0;
    CheckError(shm_fd = create_shm(shm_name));
    CheckError(init_shm(shm_fd, SHM_SIZE));
    printf("[SHM_SEM MANAGER] Shm fd %d size %lu \n", shm_fd, SHM_SIZE);
    fflush(stdout);

    // Spawn Producer process
    switch (fork()) {
    case -1:
        // Fork error code
        perror("Fork error");
        exit(1);
    case 0:
        // Child process code
        execlp(producer_prog, producer_prog, shm_name, prod_sem_name,
               con_sem_name, read_file, NULL);
        perror("Execlp error");
        _exit(1);
        break;
    default:
        // Parent process code
        break;
    };

    // Spawn Consumer process
    switch (fork()) {
    case -1:
        // Fork error code
        perror("Fork error");
        exit(1);
    case 0:
        // Child process code
        execlp(consumer_prog, consumer_prog, shm_name, prod_sem_name,
               con_sem_name, write_file, NULL);
        perror("Execlp error");
        _exit(1);
        break;
    default:
        // Parent process code
        break;
    };

    // WAIT FOR DEATH OF ALL CHILDREN
    for (int i = 0; i < 2; i++) {
        if (wait(NULL) == -1) {
            perror("Wait error");
            exit(1);
        }
    }
    return 0;
}
