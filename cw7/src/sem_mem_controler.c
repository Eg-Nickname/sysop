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
#include "semaphore.h"
#include "shared_mem.h"

char* shm_name = NULL;
char* sem_name = NULL;

void exit_fn(void) {
    CheckError(destroy_named_sem(sem_name));
    CheckError(destroy_shm(shm_name));
}

void sigint_handler(int _) { exit(EXIT_SUCCESS); }

int main(int argc, char** argv) {
    printf("Prodcon_sem_mem controler \n");

    // Validate arguments
    if (argc != 7) {
        fprintf(stderr, "Nie poprawna liczba argumentów: \n");
        fprintf(stderr,
                "%s ./shm_name ./sem_name ./producer_prog.x ./consumner_prog.x "
                "./file_to_read ./file_to_write \n",
                argv[0]);
        exit(1);
    }
    shm_name = argv[1];
    sem_name = argv[2];
    char* producer_prog = argv[3];
    char* consumer_prog = argv[4];
    char* read_file = argv[5];
    char* write_file = argv[6];

    // Declare atexit function closing named pipe
    if (atexit(exit_fn) != 0) {
        perror("atexit error");
        exit(1);
    }
    // Set SIGINT handling
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("Cant set customhandling for SIGINT");
        exit(EXIT_FAILURE);
    }

    // Create sem
    CheckError(create_named_sem(sem_name, 1));
    // Create shm
    int shm_fd = 0;
    CheckError(shm_fd = create_shm(shm_name));
    CheckError(init_shm(shm_fd, 16));

    // Spawn Producer process
    switch (fork()) {
    case -1:
        // Fork error code
        perror("Fork error");
        exit(1);
    case 0:
        // Child process code
        execlp(producer_prog, producer_prog, shm_name, sem_name, read_file);
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
        execlp(consumer_prog, consumer_prog, shm_name, sem_name, write_file);
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
