#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char aux[10];

struct wordStruct{
    char word[20];
    char lines[10000];
    int count;
    struct wordStruct  *next;
};

struct wordStruct *new(char *s){
    struct wordStruct *wordList = (struct wordStruct*)malloc(sizeof(struct wordStruct)) ;
    strcpy((*wordList).word, s);
    (*wordList).count = 0;
    return wordList;
}

void insert(struct wordStruct* wordList, char* newWord, int numberline){
    struct wordStruct* tempWord = wordList;

    while((*tempWord).next != NULL){
        if(strcmp(newWord, (*tempWord).word)==0){
            (*tempWord).count = (*tempWord).count+1;
            sprintf(aux, "%d ", numberline);
            strcat((*tempWord).lines, aux);
            return;
        }
        tempWord = (*tempWord).next;
    }
    (*tempWord).next = new(newWord);
    tempWord = (*tempWord).next;
    (*tempWord).count = 1;
    sprintf(aux, "%d ", numberline);
    strcat((*tempWord).lines, aux);
    return;
}

void print(struct wordStruct* wordList){
    if(strlen((*wordList).word) > 0){
        if ((*wordList).count <=1 ){
            printf("%s appears once in line %s\n", (*wordList).word, (*wordList).lines);
        } else {
            printf("%s appears %d times in lines %s\n ", (*wordList).word, (*wordList).count, (*wordList).lines);
        }
    }
    if((*wordList).next !=NULL) print((*wordList).next);
}

int main(int argc, char **argv){

    FILE *fInput;
    char temp[2];
    char word[50];
    char c;
    int numberLine = 1;

    struct wordStruct* list = new("");
    fInput = fopen(argv[1], "r");

    if( fInput == 1 ){
        printf("Error in reading file\n");
        return 0;
    }
    while((c = fgetc(fInput)) != EOF){
        if ((c <='Z' && c >= 'A') || (c <='z' && c >= 'a')){
        temp[0] = c;
        strcat(word, temp);
        } else {
            if(strlen(word) > 3){
                insert(list, word, numberLine);
            }
            if(c == '\n'){
                numberLine++;
            }
            strcpy(word, "");
        }
    }
    fclose(fInput);
    print(list);
}