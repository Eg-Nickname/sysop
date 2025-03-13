#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

typedef void (*sighandler_t)(int);

enum SigHandleTypes{
    SIG_DEFAULT = 0,
    SIG_IGNORE = 1,
    SIG_CUSTOM_HANLDER = 2,
};

void set_signal_handling(int signal, int sig_handle_type);
void custom_signal_handler(int);

int main(int argc, char** argv){
    // Check if number of arguments passed to program is correct
    if(argc != 3){
        fprintf(stderr, "Nie poprawna liczba argumentów: \n");
        fprintf(stderr, "%s numer_sygnału typ_operacji \n", argv[0]);
        fprintf(stderr, "   - 0 - operacja domyślna\n");
        fprintf(stderr, "   - 1 - ignorowanie sygnału\n");
        fprintf(stderr, "   - 2 - przechwycenie i własna obsługa sygnału \n");
        exit(1);
    }
    // Passed signal to handle
    int sig = 0;
    // How to handle signal
    int sig_handle_type = 0;
    // Parse signal from programs arguments
    if(sscanf(argv[1], "%d", &sig) != 1){
        fprintf(stderr, "Invalid signal number argument.\n");
    }
    // Parse and validate signal handle type from program arguments
    if((sscanf(argv[2], "%d", &sig_handle_type) != 1) || (sig_handle_type > SIG_CUSTOM_HANLDER)){
        fprintf(stderr, "Invalid signal operaton type argument. \n");
    }
    // Set handlig of signal
    set_signal_handling(sig, sig_handle_type);
    for(int i=0;i<5;i++){
        printf("Waiting for next signal\n");
        fflush(stdout);
        pause();
    }

    return 0;
}

void set_signal_handling(int sig, int sig_handle_type){
    sighandler_t sig_handle_fn;
    switch (sig_handle_type){
        case 0:
            sig_handle_fn = SIG_DFL;
            break;
        case 1:
            sig_handle_fn = SIG_IGN;
        case 2:
            sig_handle_fn = &custom_signal_handler;
            break;
        default:
            sig_handle_fn = SIG_DFL;
    }
    if (signal(sig, sig_handle_fn) == SIG_ERR){
        perror("Signal function cant set handling for passed signal");
        exit(EXIT_FAILURE);
    }
}

void custom_signal_handler(int sig){
    printf("    Custom handling of singal %s \n", strsignal(sig));
    fflush(stdout);

    if (signal(sig, &custom_signal_handler) == SIG_ERR){
        perror("Signal function cant set handling for passed signal");
        exit(EXIT_FAILURE);
    }
}

// Napisać program do obslugi sygnałów z możliwościami: (1) wykonania operacji domy-
// ślnej, (2) ignorowania oraz (3) przechwycenia i własnej obslugi sygnalu. Do ocze-
// kiwania na sygnał użyć funkcji pause. Uruchamiać program i wysyłać do niego
// sygnaly przy pomocy sekwencji klawiszy oraz przy pomocy polecenia kill z poziomu
// powłoki.

// Numer sygnalu oraz opcj ,e jego obslugi we wszystkich powy˙zszych programach przeka-
// zywa´c za pomoc ,a argument´ow wywolania programu – sprawdza´c ich liczb ,e i wypisywa´c
// odpowiedni komunikat w przypadku bl ,ednego uruchomienia (ze wskaz´owk ,a jak poprawnie
// uruchomi´c program).