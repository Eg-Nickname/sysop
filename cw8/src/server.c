#include <fcntl.h>
#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#include "check_error.h"
#include "constants.h"
#include "mqueue.h"

#define SERVER_QUEUE_MSG_COUNT 7l

// Random max and min sleep time in ms
#define RSLEEP_MAX_TIME 1500
#define RSLEEP_MIN_TIME 800

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
void exit_fn(void) { CheckError(queue_destroy(SERVER_QUEUE_NAME)); }
// custom sigint handler
void sigint_handler(int _) { exit(EXIT_SUCCESS); }

long double calculate(long double num1, long double num2, char operator);

int main(int argc, char** argv) {
    // Create server queue to recive calculations
    int qd;
    CheckError(qd = queue_create(SERVER_QUEUE_NAME, SERVER_QUEUE_MSG_COUNT,
                                 MAX_SERVER_MSG_SIZE));
    // Close queue to open it only for reading
    CheckError(queue_close(qd));
    CheckError(qd = queue_open(SERVER_QUEUE_NAME, O_RDONLY));

    // Get queue attribiures
    queue_attr attr;
    CheckError(queue_get_attr(qd, &attr));
    printf("[SERVER] Queue descriptor: %d, q_flags %ld, q_maxmsg %ld, "
           "q_msgsize %ld, "
           "q_curmsgs %ld \n",
           qd, attr.mq_flags, attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

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

    // Recive msg until sigint
    char recive_msg_buf[MAX_SERVER_MSG_SIZE];
    char send_msg_buf[MAX_CLIENT_MSG_SIZE];
    char client_queue_name[MAX_CLIENT_NAME_LEN];
    while (1) {
        // Get msg and process it
        printf("\n\n[SERVER] Waiting for msg \n");
        // Read msg from queue
        int msg_bytes = 0;
        CheckError(msg_bytes =
                       queue_receive(qd, recive_msg_buf, MAX_SERVER_MSG_SIZE));
        if (msg_bytes < MAX_SERVER_MSG_SIZE) {
            recive_msg_buf[msg_bytes] = '\0';
        }
        // Debug print recived msg
        printf("[RECIVED MSG] %s \n", recive_msg_buf);

        // Parse out client queue name and equation to calculate
        int client_pid = 0;
        long double num1 = 0.0;
        long double num2 = 0.0;
        char operator= ' ';
        if (4 != sscanf(recive_msg_buf, "%d %Lf %c %Lf", &client_pid, &num1,
                        &operator, & num2)) {
            printf("Failed to parse out msg from client \n");
        }

        printf(
            "[SERVER] Parsed out pid: %d, with nums %Lf, %Lf, operator %c \n",
            client_pid, num1, num2, operator);

        // Create client queueu name
        int client_queue_name_len =
            snprintf(client_queue_name, MAX_CLIENT_NAME_LEN, "/%d", client_pid);

        // Check if server has correct client queue name
        if (client_queue_name_len == 0) {
            printf("Error creating queue for client %d with queue %s",
                   client_pid, client_queue_name);
            continue;
        }

        printf("[SERVER] Client queue name |%s| \n", client_queue_name);

        // Open cliend queue
        int client_qd;
        CheckError(client_qd = queue_open(client_queue_name, O_WRONLY));

        // Evaluate equation
        long double solution = calculate(num1, num2, operator);
        printf("[SERVER] Calculated solution %Lf \n", solution);

        // Simulate longer delay for calculating things on server
        rsleep();

        // Send solution to client
        int client_msg_size =
            snprintf(send_msg_buf, MAX_CLIENT_MSG_SIZE, "%Lf", solution);
        CheckError(queue_send(client_qd, send_msg_buf, client_msg_size, 0));

        // Close client queue
        CheckError(queue_close(client_qd));
    }
}

long double calculate(long double num1, long double num2, char operator) {
    switch (operator) {
    case '+':
        return num1 + num2;
        break;
    case '-':
        return num1 - num2;
        break;
    case '*':
        return num1 * num2;
        break;
    case '/':
        return num1 / num2;
        break;
    default:
        return 0;
    }
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
