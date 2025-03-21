#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc != 4) {
        fprintf(stderr, "Nie poprawna liczba argumentów: \n");
        fprintf(stderr,
                "%s program_obslugujacy_sygnaly "
                "numer_sygnału typ_operacji \n",
                argv[0]);
        fprintf(stderr, "   - 0 - operacja domyślna\n");
        fprintf(stderr, "   - 1 - ignorowanie sygnału\n");
        fprintf(stderr, "   - 2 - przechwycenie i własna obsługa sygnału \n");
        exit(1);
    }
    // Program to fork with
    char* child_proc_prog = argv[1];
    // Passed signal to handle
    int sig = 0;
    // Parse signal from programs arguments
    if (sscanf(argv[2], "%d", &sig) != 1) {
        fprintf(stderr, "Invalid signal number argument.\n");
        exit(1);
    }
    // Set pgid to own process group
    if (setpgid(0, 0) == -1) {
        perror("Setpgid error");
    }
    // Set signal ignroing
    if (signal(sig, SIG_IGN) == SIG_ERR) {
        perror("Signal function cant set handling for passed signal");
        exit(EXIT_FAILURE);
    }
    // Spawn a few child processes
    for (int i = 0; i < 4; i++) {
        switch ((fork())) {
        case -1:
            // Fork error code
            perror("Fork error");
            exit(1);
        case 0:
            // Child process code
            execv(child_proc_prog, (++argv));
            perror("Execlv error");
            _exit(2);
            break;
        default:
            break;
        }
    }
    // Sleep for second to ensure all spawned processes are ready to capture
    // signal
    sleep(1);
    // Send signal to all children
    if (kill(0, sig) == -1) {
        perror("Kill error cant send signal");
        exit(1);
    }
    // Wait for them to end
    int status = 0;
    pid_t child_pid = -1;
    // Waiting for all children to die. Wait will error with -1 when no more
    // children are alive and we expect it.
    while ((child_pid = wait(&status)) != -1) {
        // Pid of dead child with its ending status
        printf("    Process %d ended with status %d", child_pid,
               WIFSIGNALED(status));

        // If child died from signal print its id and name
        if (WIFSIGNALED(status)) {
            int signal_ended = WTERMSIG(status);
            printf(" and singal %d named %s", signal_ended,
                   strsignal(signal_ended));
        }
        printf("\n");
    }
    return 0;
}
