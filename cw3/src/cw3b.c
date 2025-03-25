// ======================================================================================
// Program przyjmuje program do uruchomienia, synał oraz metode jego obsługi
// (doyślna, ignorowanie, własne) jako parametr. Następnie tworzy nowy proces, w
// którym wywoływany jest przekazywany program oraz przekazuje do niego sygnał
// wraz z metoda obsługi. Następnie sprawdza czy process istnieje. Jeśli
// istnieje to wysyła do niego sygnał przy użyciu funkcji kill.
// ======================================================================================
// Jakub Kurek 25-03-2025
// ======================================================================================

#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
    // Parse out arguments
    // Check if number of arguments passed to program is correct
    if (argc != 4) {
        fprintf(stderr, "Nie poprawna liczba argumentów: \n");
        fprintf(stderr,
                "%s program_obslugujacy sygnaly numer_sygnału typ_operacji \n",
                argv[0]);
        fprintf(stderr, "   - 0 - operacja domyślna\n");
        fprintf(stderr, "   - 1 - ignorowanie sygnału\n");
        fprintf(stderr, "   - 2 - przechwycenie i własna obsługa sygnału \n");
        exit(1);
    }
    // Program to execute with passed arguments
    char* child_proc_prog = argv[1];
    // Passed signal to handle
    int sig = 0;
    // Parse signal from programs arguments
    if (sscanf(argv[2], "%d", &sig) != 1) {
        fprintf(stderr, "Invalid signal number argument.\n");
        exit(1);
    }

    // Fork and exec prog a form args
    pid_t child_pid = 0;
    switch ((child_pid = fork())) {
    case -1:
        // Fork error code
        perror("Fork error");
        exit(1);
    case 0:
        // Child process code
        execl(child_proc_prog, child_proc_prog, argv[2], argv[3], NULL);
        perror("Execl error");
        _exit(2);
        break;
    default:
        // Parent process code
        // Wait for spawning of child process
        sleep(1);
        // Check if child proces exists
        if (kill(child_pid, 0) == -1) {
            // Child process is not alive
            perror("Kill error cant send signal");
            exit(1);
        }
        // If child is alive send signal to it
        if (kill(child_pid, sig) == -1) {
            // Child process is not alive
            perror("Kill error cant send signal");
            exit(1);
        }
        // Wait for child process to ends
        int status;
        if (wait(&status) == -1) {
            perror("Wait error");
            exit(3);
        }
        // Wait for processs to end
        if (WIFSIGNALED(status)) {
            int signal_ended = WTERMSIG(status);
            printf("Process %d ended with singal %d named %s\n", child_pid,
                   signal_ended, strsignal(signal_ended));
        }
        break;
    };

    return 0;
}
