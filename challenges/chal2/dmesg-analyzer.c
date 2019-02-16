#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <regex.h>   

#define REPORT_FILE "report.txt"

void analizeLog(char *logFile, char *report);
void lineCheck(char *line);

int main(int argc, char **argv) {

    if (argc < 2) {
	printf("Usage:./dmesg-analizer.o logfile.txt\n");
	return 1;
    }

    analizeLog(argv[1], REPORT_FILE);
    return 0;
}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);

     // Implement your solution here.
    int fileInput = open(logFile, O_RDONLY);
    int fileOutput = creat(report, S_IRUSR | S_IWUSR);
    char c;
    char *f = (char *)malloc(sizeof(char)*1);
    int counter = 0;
    char *line = (char *)malloc(sizeof(char)*1000);
    char *fNext = (char *)malloc(sizeof(char)*1);
    int state = 1;

    if (fileInput < 0){
        printf("Error\n");
    } else {
        if (fileOutput < 0){
            printf("Unable to create the report file\n");
        }
        while((c = read(fileInput, f, 1)) > 0 ){
            /*if(*f == '\n'){
                lineCheck(line);
	            *line = 0;
            } else {
                strcat(line, f);
                counter++;
            }
            
            // Tried by states but didn't work :( 
            */
            if(state == 1){
                write(fileOutput, f, 1);
                if(*f == ']'){
                    write(fileOutput, " ", 1);
                    state = 2;
                } 
            }
            if(state == 2){
                char *text = (char *)malloc(sizeof(char)*1000);
                int i = 0;
                text[i] = *f;
                i++;
                if(*f == ':' ){
                    write(fileOutput, "\n", 1);
                    write(fileOutput, text, 1);
                    state = 3;
                }
                if(*f == '\n'){
                    state = 1;
                }
            }
            if(state == 3){
                write(fileOutput, f, 1);
                if(*f == '\n'){
                    state = 1;
                }
            }
        } 
        close(fileInput);
        close(fileOutput);
        printf("Report is generated at: [%s]\n", report);
    }  
}


/*void lineCheck(char *line){
    char c;
    char *f = (char *)malloc(sizeof(char)*1);
    char *fNext = (char *)malloc(sizeof(char)*1);
    char *info = (char *)malloc(sizeof(char) * 10000000);

    while((*f = *line) != '\0') {
        *fNext = *++line; 
        --line;
        if(*f == ':' && *fNext == ' '){
            ++line;
            *f = *line;
        }  
    } 
}*/

