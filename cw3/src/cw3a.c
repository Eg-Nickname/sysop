// ======================================================================================
// Program przyjmuje synał oraz metode jego obsługi (doyślna, ignorowanie,
// własne) jako parametr a następnie ustawia jego obsługę.
// ======================================================================================
// Jakub Kurek 25-03-2025
// ======================================================================================

#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef void (*sighandler_t)(int);

enum SigHandleTypes {
    SIG_DEFAULT = 0,
    SIG_IGNORE = 1,
    SIG_CUSTOM_HANLDER = 2,
};

void set_signal_handling(int signal, int sig_handle_type);
void custom_signal_handler(int);

int main(int argc, char** argv) {
    //  Check if number of arguments passed to program is correct
    if (argc != 3) {
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
    if (sscanf(argv[1], "%d", &sig) != 1) {
        fprintf(stderr, "Invalid signal number argument.\n");
        exit(1);
    }
    // Parse and validate signal handle type from program arguments
    if ((sscanf(argv[2], "%d", &sig_handle_type) != 1) ||
        (sig_handle_type > SIG_CUSTOM_HANLDER)) {
        fprintf(stderr, "Invalid signal operaton type argument. \n");
        exit(1);
    }
    // Print pid of process handling singal
    printf("Pid for process capturing signal: %d \n", getpid());
    // Set handlig of signal
    set_signal_handling(sig, sig_handle_type);
    // Wait for incoming signal
    pause();

    return 0;
}

void set_signal_handling(int sig, int sig_handle_type) {
    sighandler_t sig_handle_fn;
    switch (sig_handle_type) {
    case 0:
        sig_handle_fn = SIG_DFL;
        break;
    case 1:
        sig_handle_fn = SIG_IGN;
        break;
    case 2:
        sig_handle_fn = &custom_signal_handler;
        break;
    default:
        sig_handle_fn = SIG_DFL;
    }
    if (signal(sig, sig_handle_fn) == SIG_ERR) {
        perror("Signal function cant set handling for passed signal");
        exit(EXIT_FAILURE);
    }
}

void custom_signal_handler(int sig) {
    printf("    Custom handling of singal \"%s\" with id \"%d\"`\n",
           strsignal(sig), sig);
    fflush(stdout);

    if (signal(sig, &custom_signal_handler) == SIG_ERR) {
        perror("Signal function cant set handling for passed signal");
        exit(EXIT_FAILURE);
    }
}
