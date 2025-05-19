#include <fcntl.h>
#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <unistd.h>

#include "check_error.h"
#include "constants.h"
#include "mqueue.h"

#define CLIENT_QUEUE_SIZE 7

char client_queue_name[MAX_CLIENT_NAME_LEN];

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
// atexit function
void exit_fn(void) { CheckError(queue_destroy(client_queue_name)); }
// custom sigint handler
void sigint_handler(int _) { exit(EXIT_SUCCESS); }

int main(int arg, char** argv) {
    // Get pid for queue name
    int pid = getpid();
    if (0 == snprintf(client_queue_name, MAX_CLIENT_NAME_LEN, "/%d", pid)) {
        fprintf(stderr, "Failed to create valid name for clien queue");
        exit(1);
    }

    // Create client queue
    int client_qd;
    CheckError(client_qd = queue_create(client_queue_name, CLIENT_QUEUE_SIZE,
                                        MAX_CLIENT_MSG_SIZE));
    // Close queue to open it only for reading
    CheckError(queue_close(client_qd));
    CheckError(client_qd = queue_open(client_queue_name, O_RDONLY));

    // Get queue attribiures
    queue_attr attr;
    CheckError(queue_get_attr(client_qd, &attr));
    printf("[CLIENT] Queue descriptor: %d, q_flags %ld, q_maxmsg %ld, "
           "q_msgsize %ld, "
           "q_curmsgs %ld \n",
           client_qd, attr.mq_flags, attr.mq_maxmsg, attr.mq_msgsize,
           attr.mq_curmsgs);

    // Declare atexit function
    if (atexit(exit_fn) != 0) {
        perror("atexit error");
        exit(EXIT_FAILURE);
    }
    // Set SIGINT handling
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("Cant set custom handling for SIGINT");
        exit(EXIT_FAILURE);
    }
    // Seed rand function for sleeping using time and pid
    srand(time(NULL));

    // Open server queue
    int server_qd;
    CheckError(server_qd = queue_open(SERVER_QUEUE_NAME, O_WRONLY));

    // Read equations until EOF
    char send_msg_buf[MAX_SERVER_MSG_SIZE];
    char recive_msg_buf[MAX_CLIENT_MSG_SIZE];
    int max_line_size = MAX_SERVER_MSG_SIZE - strlen(client_queue_name) - 2;
    char line_buf[max_line_size];
    int server_msg_size = 0;
    // Read from stdin until eof
    printf("[CLIENT] Input equation for calculations: ");
    while (fgets(line_buf, max_line_size, stdin) != NULL) {
        // Create message for server

        // Replace new line character with '\0' for easier parsing on reciving
        // end
        char* nl_pos = strchr(line_buf, '\n');
        if (nl_pos != NULL) {
            *(nl_pos) = '\0';
        }

        // Create server msg
        server_msg_size =
            snprintf(send_msg_buf, MAX_SERVER_MSG_SIZE, "%d %s", pid, line_buf);

        if (server_msg_size <= 0) {
            printf("[CLIENT] snprintf msg creation error \n");
        }

        // Send msg to queue
        CheckError(queue_send(server_qd, send_msg_buf, server_msg_size, 0));

        // Simulate waiting before reciving calculation
        rsleep();

        // Wait for server response and read it
        CheckError(
            queue_receive(client_qd, recive_msg_buf, MAX_SERVER_MSG_SIZE));
        printf("[CLIENT] Calculation recived from server: %s \n",
               recive_msg_buf);
        printf("[CLIENT] Input equation for calculations: ");
    }
    // Close queues
    CheckError(queue_close(server_qd));
    CheckError(queue_close(client_qd));
    exit(EXIT_SUCCESS);
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
