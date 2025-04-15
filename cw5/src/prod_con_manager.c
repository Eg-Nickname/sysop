// ======================================================================================
// Program przyjmuje 5 argumentów, nazwe potoku, program produenta, program
// konsumenta, plik do oczytu danych, plik do zapisu danych. Progrma ten tworzy
// nazwany potok oraz 2 procesy potomne, którym przekazuje potok oraz
// odpowiednio plik zapisu/odczytu. Po zakończeniu procesów potomnych usuwa
// nazwany potok przy uzyciu funkcji atexit().
// ======================================================================================
// Jakub Kurek 15-04-2025
// ======================================================================================

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <threads.h>
#include <unistd.h>

char* pipe_name;
void close_pipe(void);

int main(int argc, char** argv) {
    // Validate arguments
    if (argc != 6) {
        fprintf(stderr, "Nie poprawna liczba argumentów: \n");
        fprintf(stderr,
                "%s ./pipe_name ./producer_prog.x ./consumner_prog.x "
                "./file_to_read ./file_to_write \n",
                argv[0]);
        exit(1);
    }
    pipe_name = argv[1];
    char* producer_prog = argv[2];
    char* consumer_prog = argv[3];
    char* read_file = argv[4];
    char* write_file = argv[5];

    // Create Named Pipe
    if (mkfifo(pipe_name, 0644) == -1) {
        perror("Mkfifo error");
        exit(1);
    }

    // Declare atexit function closing named pipe
    if (atexit(close_pipe) != 0) {
        perror("atexit error");
        exit(1);
    }

    // Spawn Producer process
    switch (fork()) {
    case -1:
        // Fork error code
        perror("Fork error");
        exit(1);
    case 0:
        // Child process code
        execlp(producer_prog, producer_prog, pipe_name, read_file);
        perror("Execlp error");
        _exit(2);
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
        execlp(consumer_prog, consumer_prog, pipe_name, write_file);
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

void close_pipe(void) {
    if (unlink(pipe_name) == -1) {
        perror("Unlink error");
        exit(1);
    }
}
