// ======================================================================================
// Program przyjmuje dwie nazwy plików, jeden do odczytu drugi do zapisuj.
// Tworzy jeden proces potomny, który przyjmuje dane odczytane z pliku
// przekazane przy użyciu potoku. Po odczycie wypsiuje je na standardowe wyjście
// oraz zapisuje do pliku podanego jako zapis. Procesy odczytujące i zapisujące
// dane posiadają losowy czas uśpienia pomidzy odczytem/zapisem symulujący
// przetwarzanie danych
// ======================================================================================
// Jakub Kurek 1-04-2025
// ======================================================================================

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <threads.h>
#include <unistd.h>

#define PIPE_READER_BUFF_SIZE 16
#define PIPE_WRITER_BUFF_SIZE 24

// Random max and min sleep time in ms
#define RSLEEP_MAX_TIME 1000
#define RSLEEP_MIN_TIME 500

// Helper function to sleep in ms
int msleep(unsigned long msec);
// Sleeps random amout of ms
void rsleep(void) {
    msleep(rand() % (RSLEEP_MAX_TIME - RSLEEP_MIN_TIME) + RSLEEP_MIN_TIME);
}

int main(int argc, char **argv) {
    // Validate arguments
    if (argc != 3) {
        fprintf(stderr, "Nie poprawna liczba argumentów: \n");
        fprintf(stderr, "%s ./file_to_read ./file_to_write \n", argv[0]);
        exit(1);
    }
    char *read_file = argv[1];
    char *write_file = argv[2];

    // Create pipeline for ipc
    int filedes[2];
    if (pipe(filedes) == -1) {
        perror("Pipe error");
        exit(1);
    }

    // Init random num generator
    srand(time(NULL));

    // Spawn child proc
    switch (fork()) {
    case -1:
        // Fork error code
        perror("Fork error");
        exit(1);
    case 0:
        // Child process code
        // Close unused pipeline
        if (close(filedes[1]) == -1) {
            perror("Pipe close error");
            exit(1);
        }
        int read_pd = filedes[0];
        char **reader_buff[PIPE_READER_BUFF_SIZE];

        // Open file to write
        int write_fd = open(write_file, O_CREAT | O_WRONLY, 0644);
        if (write_fd == -1) {
            perror("Can't open file to read data from");
            exit(1);
        }

        // Read bytes from file until eof
        ssize_t pipe_read_bytes;
        while ((pipe_read_bytes =
                    read(read_pd, reader_buff, PIPE_READER_BUFF_SIZE)) != 0) {
            // Sleep for simulating processing data
            rsleep();

            // Write to file and stdout
            write(write_fd, reader_buff, pipe_read_bytes);
            write(1, "[PipeRead]", strlen("[PipeRead]"));
            write(1, reader_buff, pipe_read_bytes);
            write(1, "\n", 1);
        }

        // After reading everything
        if (close(read_pd) == -1) {
            perror("Pipe close error");
            exit(1);
        }
        if (close(write_fd) == -1) {
            perror("File close error");
            exit(1);
        }
        break;
    default:
        // Parent code
        // Close unused pipeline
        if (close(filedes[0]) == -1) {
            perror("Pipe close error");
            exit(1);
        }
        int write_pd = filedes[1];
        char **writer_buff[PIPE_WRITER_BUFF_SIZE];

        // Open file to read
        int read_fd = open(read_file, O_RDONLY);
        if (read_fd == -1) {
            perror("Can't open file to read data from");
            exit(1);
        }

        // Read bytes from file until eof
        ssize_t file_read_bytes;
        while ((file_read_bytes =
                    read(read_fd, writer_buff, PIPE_WRITER_BUFF_SIZE)) != 0) {
            // Sleep for simulating processing data
            rsleep();

            // Write data to pipe
            write(write_pd, writer_buff, file_read_bytes);
            write(1, "[PipeWrite]", strlen("[PipeWrite]"));
            write(1, writer_buff, file_read_bytes);
            write(1, "\n\n", 2);
        }

        // After writing everything close pipe and file descriptor
        if (close(write_pd) == -1) {
            perror("Pipe close error");
            exit(1);
        }
        if (close(read_fd) == -1) {
            perror("File close error");
            exit(1);
        }

        // Wait for child process to end processing data
        if (wait(NULL) == -1) {
            perror("Wait error");
            exit(3);
        }
        break;
    }

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
