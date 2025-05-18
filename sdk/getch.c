/*  getch.c - POSIX-compatible character input functions
 *
 *  Copyright (c) Original Authors of POSIX-compatible Implementation
 *
 *  Licensed under the Mozilla Public License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      https://www.mozilla.org/en-US/MPL/2.0/
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  Copyright (c) SPC (SA-MP Programming Community)
 *  The SA-MP Programming Community holds copyright solely for the improvements
 *  made to this file and does not claim any rights to the original content.
 *  SPC improvements are licensed under the MIT License, available at:
 *  https://opensource.org/licenses/MIT
 */

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