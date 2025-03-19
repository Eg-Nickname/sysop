#include <stdio.h>

// Funkcja przed wysłaniem sygnału do procesu potomnego powinna 
// sprawdzić czy istnieje przy użyciu funkcji kill z parametrem 0
int main(int argc, char** argv){
    printf("Hello world! \n");
    return 0;
}