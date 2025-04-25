#include "semaphore.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
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
        exit(EXIT_FAILURE);                                                    \
    }

const char* sem_name;

void exit_fn(void) { CheckError(destroy_named_sem(sem_name)); }
void sigint_handler(int);

int main(int argc, char** argv) {
    // Validate arguments
    if (argc != 6) {
        fprintf(stderr, "Nie poprawna liczba argumentów (%d): \n", argc);
        fprintf(
            stderr,
            "%s ./counter_file ./sem_name ./child_proces_prog child_proc_count "
            "child_proc_crit_sections \n",
            argv[0]);
        exit(1);
    }
    char* counter_file_name = argv[1];
    sem_name = argv[2];
    char* child_proc_prog = argv[3];
    char* child_crit_sections_count = argv[5];

    int child_proc_count = 0;
    if (sscanf(argv[4], "%d", &child_proc_count) != 1) {
        fprintf(stderr, "Invalid child proces count.\n");
        exit(1);
    }
    int child_crit_sections_int_count = 0;
    if (sscanf(argv[5], "%d", &child_crit_sections_int_count) != 1) {
        fprintf(stderr, "Invalid child proces count.\n");
        exit(1);
    }

    // Create semaphore
    sem_t* sem_ptr;
    CheckError(sem_ptr = create_named_sem(sem_name, 1));
    int sem_val = 0;
    CheckError(get_sem_val(sem_ptr, &sem_val));
    printf("[SEM CONTROLER] Created sem at %p with val %d", (void*)sem_ptr,
           sem_val);
    // Flush stdout to ensure printing information before child processes data
    fflush(stdout);

    // Declare atexit function to clean up semaphore
    if (atexit(exit_fn) == -1) {
        perror("atexit error");
        exit(1);
    }
    // Set SIGINT handling
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("Cant set customhandling for SIGINT");
        exit(EXIT_FAILURE);
    }

    // Create and open file to read
    int fd = open(counter_file_name, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Can't open file for semaphores");
        exit(1);
    }
    // Write 0 to file
    int buf = 0;
    if (write(fd, &buf, sizeof(int)) == -1) {
        perror("File write error");
        exit(1);
    }
    // Close file
    if (close(fd) == -1) {
        perror("File close error");
        exit(1);
    }

    // Create child processes
    for (int i = 0; i < child_proc_count; i++) {
        // Create proceses
        switch (fork()) {
        case -1:
            // Fork error code
            perror("Fork error");
            exit(1);
        case 0:
            // Child process code
            execl(child_proc_prog, child_proc_prog, counter_file_name,
                  child_crit_sections_count, sem_name, NULL);
            perror("Execv error");
            _exit(2);
            break;
        default:
            break;
        }
    }

    // Wait for all children death
    for (int i = 0; i < child_proc_count; i++) {
        if (wait(NULL) == -1) {
            perror("Wait error");
            exit(1);
        }
    }
    // Verify correctly working semaphore
    int counter_buf = 0;
    // Open file to read counter
    int counter_fd = open(counter_file_name, O_RDONLY);
    if (fd == -1) {
        perror("Can't open file for counting");
        exit(1);
    }
    // Read counter from file
    if (read(counter_fd, &counter_buf, sizeof(int)) == -1) {
        perror("File read error");
        exit(1);
    }
    // Close file
    if (close(counter_fd) == -1) {
        perror("File close error");
        exit(1);
    }
    printf("\n\tCOUNTER VALUE: %d, EXPECTED VALUE: %d\n", counter_buf,
           child_proc_count * child_crit_sections_int_count);
    return 0;
}

void sigint_handler(int _) { exit(EXIT_SUCCESS); }
