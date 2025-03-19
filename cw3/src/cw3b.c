#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>



int main(int argc, char** argv){
    // Parse out arguments
    // Check if number of arguments passed to program is correct
    if(argc != 4){
        fprintf(stderr, "Nie poprawna liczba argumentów: \n");
        fprintf(stderr, "%s program_obslugujacy sygnaly numer_sygnału typ_operacji \n", argv[0]);
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
    if(sscanf(argv[2], "%d", &sig) != 1){
        fprintf(stderr, "Invalid signal number argument.\n");
        exit(1);
    }

    // Fork and exec prog a form args
    pid_t child_pid = 0;
    switch((child_pid = fork()))
        {
        case -1:
            // Fork error code
            perror("Fork error");
            exit(1);
        case 0:
            // Child process code
            execl(child_proc_prog, child_proc_prog, argv[2], argv[3], NULL);
            perror("Execlp error");
            _exit(2);
            break; 
        default:
            // Parent process code
            // Wait for spawning of child process
            sleep(1);
            // Check if child proces exists
            if(kill(child_pid, 0) == -1){
                // Child process is not alive
                perror("Kill error cant send signal");
                exit(1);
            }
            // If child is alive send signal to it
            if(kill(child_pid, sig) == -1){
                // Child process is not alive
                perror("Kill error cant send signal");
                exit(1);
            }
            // Wait for child process to ends
            if(wait(NULL)==-1){
                perror("Wait error");
                exit(3);
            }
            break;
        };

    return 0;
}