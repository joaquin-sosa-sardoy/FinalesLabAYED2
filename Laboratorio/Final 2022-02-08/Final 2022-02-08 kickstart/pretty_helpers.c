#include <stdio.h>

// Para desactivar los colores deben descomentar la siguiente linea:
// #define NO_PRETTY

// Color ANSI code
#ifndef NO_PRETTY

#define ANSI_NOCOLOR "\033[0m"
#define ANSI_BLUE "\033[0;34m"
#define ANSI_GREEN "\033[38;2;0;200;0m"
#define ANSI_LIGHTGREEN  "\033[0;92m"
#define ANSI_CYAN "\033[0;36m"
#define ANSI_RED  "\033[0;31m"
#define ANSI_LIGHTRED  "\033[0;91m"
#define ANSI_GOLD  "\033[0;33m"
#define ANSI_GRAY  "\033[0;37m"
#define ANSI_WHITE "\033[38;2;255;255;255m"

#else

#define ANSI_NOCOLOR ""
#define ANSI_BLUE ""
#define ANSI_GREEN ""
#define ANSI_LIGHTGREEN  ""
#define ANSI_CYAN ""
#define ANSI_RED  ""
#define ANSI_LIGHTRED  ""
#define ANSI_GOLD  ""
#define ANSI_GRAY  ""
#define ANSI_WHITE ""

#endif

void color_no_color(void) {
    printf(ANSI_NOCOLOR);
}

void color_blue(void) {
    printf(ANSI_BLUE);
}

void color_green(void) {
    printf(ANSI_GREEN);
}

void color_lightgreen(void) {
    printf(ANSI_LIGHTGREEN);
}

void color_gold(void) {
    printf(ANSI_GOLD);
}

void color_gray(void) {
    printf(ANSI_GRAY);
}

void color_cyan(void) {
    printf(ANSI_CYAN);
}

void color_lightred(void) {
    printf(ANSI_LIGHTRED);
}
void color_red(void) {
    printf(ANSI_RED);
}

void color_white(void) {
    printf(ANSI_WHITE);
}

