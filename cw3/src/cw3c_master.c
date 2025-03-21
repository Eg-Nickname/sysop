#include <stdio.h>
#include <stdlib.h>
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
        if (wait(NULL) == -1) {
            perror("Wait error");
            exit(1);
        }
        break;
    }
    return 0;
}
