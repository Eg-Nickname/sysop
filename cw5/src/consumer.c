#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <unistd.h>

#define PIPE_BUFF_SIZE 16

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
    // CHECK ARGUMENTS
    if (argc != 3) {
        fprintf(stderr, "Nie poprawna liczba argumentów: \n");
        fprintf(stderr, "%s ./pipe_name ./file_to_write \n", argv[0]);
        exit(1);
    }
    char* pipe_name = argv[1];
    char* write_file = argv[2];

    // Open named pipe to read from
    int read_pd = open(pipe_name, O_RDONLY);
    if (read_pd == -1) {
        perror("Can't open file to read data from");
        exit(1);
    }

    char** reader_buff[PIPE_BUFF_SIZE];

    // Open file to write
    int write_fd = open(write_file, O_CREAT | O_WRONLY, 0644);
    if (write_fd == -1) {
        perror("Can't open file to read data from");
        exit(1);
    }

    // Read bytes from file until eof
    ssize_t pipe_read_bytes;
    while ((pipe_read_bytes = read(read_pd, reader_buff, PIPE_BUFF_SIZE)) !=
           0) {
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
