// ======================================================================================
// Proces tworzy nowe procesy potomne oraz zmienia ich na liderów własnych grup oraz
// wypisuje informacje o processach
// ======================================================================================
// Jakub Kurek 09-03-2025
// ======================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "process_info.h"

int main(int argc, char **argv)
{
    printf("Proces macierzysty - ");
    print_process_info();

    for (int i = 0; i < 3; i++)
    {
        switch (fork())
        {
        case -1:
            // Fork error code
            perror("fork error");
            exit(1);
        case 0:
            // Child process code
            if (setpgid(0, 0) == -1)
            {
                perror("setpgid error");
            }
            printf("    Proces potomny - ");
            print_process_info();
            break;
        default:
            // Parent process code
            if(wait(NULL)==-1){
                perror("Wait error");
                exit(3);
            }
            break;
        };
    }
    return 0;
}