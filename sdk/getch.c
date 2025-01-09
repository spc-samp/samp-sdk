#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include "getch.h"

#ifndef STDIN_FILENO
    #define STDIN_FILENO 0
#endif

static struct termios original_termios;
static int termios_initialized = 0;

static int setup_terminal(void) {
    if (!isatty(STDIN_FILENO))
        return -1;

    if (!termios_initialized) {
        if (tcgetattr(STDIN_FILENO, &original_termios) < 0)
            return -1;

        termios_initialized = 1;
    }

    struct termios raw = original_termios;
    raw.c_lflag &= ~(ICANON | ECHO | ISIG);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;

    return tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

static void restore_terminal(void) {
    if (termios_initialized)
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

int getch(void) {
    if (setup_terminal() < 0)
        return EOF;

    unsigned char c;
    ssize_t result = read(STDIN_FILENO, &c, 1);
    
    restore_terminal();
    
    return (result == 1) ? c : EOF;
}

int kbhit(void) {
    if (setup_terminal() < 0)
        return 0;

    fd_set read_fds;
    struct timeval timeout = {0, 0};

    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);

    int result = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &timeout);
    
    restore_terminal();
    
    return result == 1;
}

#ifdef TEST_GETCH
    int main(void) {
        char buffer[4] = {0};
        
        printf("Enter %zu keys to continue: ", sizeof(buffer) - 1);
        fflush(stdout);

        for (size_t i = 0; i < sizeof(buffer) - 1; i++)
            buffer[i] = getch();

        printf("\nYour input: [%s]\n", buffer);

        printf("Now hit any key to abort: ");
        fflush(stdout);
        
        while (!kbhit()) {
            printf(".");
            fflush(stdout);
            usleep(100000);
        }

        return 0;
    }
#endif