#include <stdio.h>
#include <stdarg.h>

#define RESET       0
#define BRIGHT      1
#define DIM         2
#define UNDERLINE   3
#define BLINK       4
#define REVERSE     7
#define HIDDEN      8

#define BLACK       0
#define RED         1
#define GREEN       2
#define YELLOW      3
#define BLUE        4
#define MAGENTA     5
#define CYAN        6
#define WHITE       7

void textcolor(int attr, int fg){   
    char command[13];
    sprintf(command, "%c[%d;%dm", 0x1B, attr, fg + 30);
    printf("%s", command);  
}

int infof (const char *format, ...) {
    textcolor(BRIGHT, GREEN);
    int check;
    va_list arg;
    printf("INFO: ");
    textcolor(RESET, WHITE);
    va_start(arg, format);
    check = vprintf(format, arg);
    va_end(arg);
    return check;    
}

int warnf (const char *format, ...) {
    textcolor(BRIGHT, MAGENTA);
    int check;
    va_list arg;
    printf("WARN: ");
    va_start(arg, format);
    check = vprintf(format, arg);
    va_end(arg);
    textcolor(RESET, WHITE); 
    return check;
}

int errorf (const char *format, ...) {
    textcolor(BRIGHT, RED); 
    int check;
    va_list arg;
    printf ("ERROR: ");
    va_start (arg, format);
    check = vprintf (format, arg);
    va_end (arg);
    textcolor(RESET, WHITE); 
    return check;
}

int panicf (const char *format, ...) {
    textcolor(BRIGHT, YELLOW);
    int check;
    va_list arg;
    printf ("PANIC: ");
    va_start (arg, format);
    check = vprintf (format, arg);
    va_end (arg);
    textcolor (RESET, WHITE);
    return check;
}