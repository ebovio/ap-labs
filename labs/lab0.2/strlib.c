// strlib.c
#include <stdio.h>

int strlen(char *str){
    int size = 0;
    while (str[size] != '\0'){
        size++;
    }
    return size;
}

char* stradd(char *origin, char *addition){
    size_t i = strlen(origin);
    size_t j = strlen(addition);
    char *strFinal = malloc(i + j);
    for (i = 0; i < strlen(origin); i++){
        strFinal[i] = origin[i];
    }
    for (j = 0; j < strlen(addition); j++){
        strFinal[i] = addition[j];
        i++;
    }
    return strFinal;
}


int strfind(char *origin, char *substr){
    size_t i = strlen(origin);
    size_t j = strlen(substr);
    if (j > i){
        return 0;
    } else if (j == 0){
        return 0;
    } else{
        for(int x = 0; x < i; x++){
            if(origin[i] != substr[x]){
                x = 0;
            }
            if(origin[i] == substr[x]){
                x++;
            }
            if(j == strlen(substr)){
                return 1;
            }
        }
    }
}