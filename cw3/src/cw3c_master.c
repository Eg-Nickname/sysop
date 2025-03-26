// ======================================================================================
// Program przyjmuje dwa proramy, synał oraz metode jego obsługi (doyślna,
// ignorowanie, własne) jako parametr. Tworzy nowy proces, któremu przekazuje
// program, sygnał i typ obsługi sygnału.
// ======================================================================================
// Jakub Kurek 25-03-2025
// ======================================================================================

#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc != 5) {
        fprintf(stderr, "Nie poprawna liczba argumentów: \n");
        fprintf(stderr,
                "%s program_tworzacy_procesy program_obslugujacy_sygnaly "
                "numer_sygnału typ_operacji \n",
                argv[0]);
        fprintf(stderr, "   - 0 - operacja domyślna\n");
        fprintf(stderr, "   - 1 - ignorowanie sygnału\n");
        fprintf(stderr, "   - 2 - przechwycenie i własna obsługa sygnału \n");
        exit(1);
    }
    char* child_proc_prog = argv[1];
    // Passed signal to handle
    int sig = 0;
    // Parse signal from programs arguments
    if (sscanf(argv[3], "%d", &sig) != 1) {
        fprintf(stderr, "Invalid signal number argument.\n");
        exit(1);
    }

    // Fork and spawn first program
    pid_t child_pid = 0;
    switch ((child_pid = fork())) {
    case -1:
        // Fork error code
        perror("Fork error");
        exit(1);
    case 0:
        // Child process code
        execv(child_proc_prog, (++argv));
        perror("Execv error");
        _exit(2);
        break;
    default:
        // Sleep for second to ensure all spawned processes are ready to capture
        // signal
        sleep(1);
        // Send signal to all processes in children group
        int child_pgid = getpgid(child_pid);

        if (kill(-child_pgid, sig) == -1) {
            perror("Kill error cant send signal");
            exit(1);
        }
        if (wait(NULL) == -1) {
            perror("Wait error");
            exit(1);
        }
        break;
    }
    return 0;
}
