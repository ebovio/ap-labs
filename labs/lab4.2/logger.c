#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>
#include <string.h>

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

int type = 0;

void textcolor(int attr, int fg){   
    char command[13];
    sprintf(command, "%c[%d;%dm", 0x1B, attr, fg + 30);
    printf("%s", command);  
}

int infof (const char *format, ...) {
    int check;
    va_list arg;
    if (type == 0){
        textcolor(BRIGHT, GREEN);
        printf("INFO: ");
        textcolor(RESET, WHITE);
        va_start(arg, format);
        check = vprintf(format, arg);
        va_end(arg);
        return check;
    } else {
        va_start(arg, format);
        vsyslog(LOG_USER | LOG_INFO, format, arg);
        va_end(arg);
        return 1;
    } 
}

int warnf (const char *format, ...) {
    int check;
    va_list arg;
    if (type == 0){
        textcolor(BRIGHT, MAGENTA);
        printf("WARN: ");
        va_start(arg, format);
        check = vprintf(format, arg);
        va_end(arg);
        textcolor(RESET, WHITE); 
        return check;
    } else {
        va_start(arg, format);
        vsyslog(LOG_USER | LOG_WARNING, format, arg);
        va_end(arg);
        return 1;
    } 
}

int errorf (const char *format, ...) { 
    int check;
    va_list arg;
    if (type == 0){
        textcolor(BRIGHT, RED);
        printf ("ERROR: ");
        va_start (arg, format);
        check = vprintf (format, arg);
        va_end (arg);
        textcolor(RESET, WHITE); 
        return check;
    } else {
        va_start(arg, format);
        vsyslog(LOG_USER | LOG_ERR, format, arg);
        va_end(arg);
        return 1;
    }
}

int panicf (const char *format, ...) {
    int check;
    va_list arg;
    if(type == 0){
        textcolor(BRIGHT, YELLOW);
        printf ("PANIC: ");
        va_start (arg, format);
        check = vprintf (format, arg);
        va_end (arg);
        textcolor (RESET, WHITE);
        return check;
    } else {
        va_start(arg, format);
        vsyslog(LOG_USER | LOG_EMERG, format, arg);
        va_end(arg);
        return 1;
    }
}

int initLogger(char *logType) {
    if(strcmp("stdout", logType) == 0 || strcmp ("", logType) == 0) {
        type = 0;
        return 1;
    } else if (strcmp("syslog", logType) == 0){
        type = 1;
        return 1;
    }
    return 0;
}