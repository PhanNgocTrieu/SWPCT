#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

// The ioctl() function is used to control the terminal device.
#include <sys/ioctl.h>

/*** defines ***/
#define CTRL_KEY(k) ((k) & 0x1f)

/*** data ***/
struct termios orig_termios;

struct editorConfig {
    struct termios orig_termios;
};

struct editorConfig E;

/*** ternimal ***/

void die(const char* s) {
    // Clears the screen and repositions the cursor to the top-left corner before printing the error message.
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

    perror(s);
    exit(1);
}

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1) {
        die("tcsetattr");
    }
    printf("disable raw mode\n");
}

void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) {
        die("tcgetattr");
    }
    printf("enable raw mode\n");
    atexit(disableRawMode);
    struct termios raw = E.orig_termios;

    // Disable the IXON flag in the input modes (c_iflag) of the terminal.
    // BRKINT: Disables the break condition signal.
    // INPCK: Disables the parity check.
    // IXON: Disables software flow control (Ctrl+S/Ctrl+Q).
    // ICRNL: Disables the translation of carriage return (13) to newline (10).
    raw.c_iflag &= ~(BRKINT | INPCK | ICRNL | IXON);

    // Disable the OPOST flag in the output modes (c_oflag) of the terminal.
    // OPOST: Disables output processing, which converts newline characters to carriage return followed by newline.
    raw.c_oflag &= ~(OPOST);

    // Set the character size to 8 bits per byte.
    raw.c_cflag |= (CS8);


    // Disable ECHO and ICANON flags in the local modes (c_lflag) of the terminal.
    // ECHO: Disables the echoing of input characters.
    // ICANON: Disables canonical mode, allowing input to be read byte-by-byte instead of line-by-line.
    // ISIG: Disables the sending of signals like SIGINT (Ctrl+C) and SIGTSTP (Ctrl+Z).
    // IEXTEN: Disables Ctrl+V and Ctrl+O.
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);

    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    // Set the minimum number of bytes of input needed before read() can return.
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        die("tcsetattr");
    }
}

char editorReadKey() {
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) {
            die("read");
        }
    }
    return c;
}


int getWindowSize(int *rows, int *cols) {
    // The winsize structure stores the size of the terminal window (iside sys/ioctl.h).
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        return -1;
    } else {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }
}

/*** input ***/
void editorProcessKeypress() {
    char c = editorReadKey();
    switch (c) {
        case CTRL_KEY('q'): {
            write(STDOUT_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);
            exit(0);
            break;
        }
    }
}

/*** output ***/
void editorDrawRows() {
    for (int y = 0; y < 24; y++) {
        write(STDOUT_FILENO, "~\r\n", 3);
    }
}

void editorRefreshScreen() {
    /**
     * Clears the entire screen by writing the ANSI escape code "\x1b[2J" to the standard output (STDOUT).
     * The escape code "\x1b[2J" is used to clear the screen in terminal emulators.
     *
     * STDOUT_FILENO is a file descriptor for standard output, typically with a value of 1.
     * The write function sends the escape code to the terminal, causing it to clear the screen.
     *
     * Parameters:
     * - STDOUT_FILENO: The file descriptor for standard output.
     * - "\x1b[2J": The ANSI escape code to clear the screen.
     * - 4: The number of bytes to write (length of the escape code string).
     */
    write(STDOUT_FILENO, "\x1b[2J", 4);

    // Repositions the cursor to the top-left corner of the screen by writing the ANSI escape code "\x1b[H" to the standard output (STDOUT).
    // The escape code "\x1b[H" is used to reposition the cursor in terminal emulators.
    write(STDOUT_FILENO, "\x1b[H", 3);

    editorDrawRows();

    write(STDOUT_FILENO, "\x1b[H", 3);
}

/*** init ***/
int main() {
    enableRawMode();
    while (1) {
        editorRefreshScreen();
        editorProcessKeypress();
    }

    return 0;
}