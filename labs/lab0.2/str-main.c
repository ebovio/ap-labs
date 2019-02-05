#include "stdio.h"

int strlen(char *str);
char* stradd(char *origin, char *addition);
int strfind(char *origin, char *substr);

int main(int argc, char const **argv)
{
    printf("Length: %d\n", strlen(argv[1]));
    printf("New String: %s\n", stradd(argv[1], argv[2]));
    if(strfind(stradd(argv[1], argv[2]), argv[3])){
        printf("The substring was found in the original string\n");
    } else {   
        printf("There is not substring\n");
    }
}