#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    struct termios oldt, newt;

    // Disabilita il buffering di riga e l'eco dei caratteri nel terminale
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    printf("Premi un tasto per emettere un suono...\n");
    getchar();

    // printf("\a"); // Emette il suono di sistema del terminale
    // Basso.aiff     Bottle.aiff    Funk.aiff      Hero.aiff      Ping.aiff      Purr.aiff      Submarine.aiff
    // Blow.aiff      Frog.aiff      Glass.aiff     Morse.aiff     Pop.aiff       Sosumi.aiff    Tink.aiff
    system("afplay /System/Library/Sounds/Ping.aiff &");
    
    fflush(stdout);

    // Ripristina le impostazioni originali del terminale
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}
