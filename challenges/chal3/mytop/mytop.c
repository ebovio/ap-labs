#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>

void processLine(char *line);
void searchOpenFiles();
static void signalHandler(int sig);
void analizeText(char *logFile);
void printTable();
void clear();

struct process{
    char pid[10];
    char parentPid[10];
    char name[10];
    char state[10];
    char memory[10];
    char threads[10];
    int openFiles; 
};

struct process processes[2000];
int counter = 0;
int position = 0;

int main(){
	if (signal(SIGINT, signalHandler) == SIG_ERR){
            perror("ERROR: Unable to catch signal\n");
	}
	
	struct dirent *dir;

	DIR *d = opendir("/proc/");

	char path[30], fpath[30];
	int c = 1;
    while(1){
		strcpy(path, "/proc/");
		strcpy(fpath, "/proc/");
		while((dir = readdir(d)) != NULL) {
			if(isdigit(dir->d_name[0])){
				strcat(path, dir->d_name);
				strcat(path, "/status");
				strcpy(processes[position].memory, "0");
				analizeText(path);
				position++;
				strcpy(path, "/proc/");
				strcat(fpath, dir->d_name);
				strcat(fpath, "/fd");
				searchOpenFiles(fpath);
				counter++;
			}
		}
		printTable();
		sleep(5);
		clear();
		c++;
    }
    clear();
    return 0;
}

void searchOpenFiles(char *fpath){
		int counterOpenFiles;
		DIR *fdd = opendir(fpath);
		struct dirent *fd_dir;
		while((fd_dir = readdir(fdd)) != NULL) {
			counterOpenFiles++;
		}
		closedir(fdd);
		processes[position].openFiles = counterOpenFiles - 2;
		strcpy(fpath, "/proc/");
}


void printTable(){
	float memory;
	printf("+--------+--------+---------------+-------+----------+----------+----------------------------------------+\n");
	printf("|   PID  | Parent |     State     |Threads|  Memory  |Open Files|                   Name                 |\n");
	printf("+--------+--------+---------------+-------+----------+----------+----------------------------------------+\n");
	for(int i = 0; i < position; i++){
		if(processes[i].pid == 0){
			continue;
		}
		memory = atof(processes[i].memory) / 1000;
		printf("|%8s|%8s|%15s|%7s|%8.4f M|%10i|%40s|\n", processes[i].pid, processes[i].parentPid, processes[i].state, processes[i].threads, memory, processes[i].openFiles, processes[i].name);	
	}
	printf("+--------+--------+---------------+-------+----------+----------+----------------------------------------+\n");
	return;
}

static void signalHandler(int sig){
    char fileName[100];
    strcpy(fileName, "mytop-status-");
    time_t unprocessedTime;
    struct tm * timeInfo;
    time ( &unprocessedTime );
    timeInfo = localtime ( &unprocessedTime );
    strcat(fileName, asctime(timeInfo));
    strcat(fileName, ".txt");
    float memory;

	FILE *fd = fopen(fileName, "w");

	if(fd == NULL){
		perror("Unable to open file");
		exit(1);
	}
	printf(fd, "+--------+--------+---------------+-------+----------+----------+----------------------------------------+\n");
	printf(fd, "|   PID  | Parent |     State     |Threads|  Memory  |Open Files|                   Name                 |\n");
	printf(fd, "+--------+--------+---------------+-------+----------+----------+----------------------------------------+\n");
	for(int i = 0; i < position; i++){
		if(processes[i].pid == 0){
			continue;
		}
		memory = atof(processes[i].memory) / 1000;
		
		fprintf(fd, "|%8s|%8s|%15s|%7s|%8.4f M|%10i|%40s|\n", processes[i].pid, processes[i].parentPid, processes[i].state, processes[i].threads, memory, processes[i].openFiles, processes[i].name);	

	}
	fprintf(fd, "+--------+--------+---------------+-------+----------+----------+----------------------------------------+\n");
	fclose(fd);
	printf("Result written in file: %s\n", fileName);
}

void processLine(char *line){
    char *buf = (char *)malloc(sizeof(char) * 4);
    char *lineData = (char *)malloc(sizeof(char) * 80);
    bool flag = true;
    int p = 0;
	int j = 0;

	for(int i = 0; line[i] != '\0'; i++){
		if(line[i] == ':'){
	    	flag = false;
		}
		if(flag){
			if(p < 4){
				buf[i] = line[i];
				p++;
			}
		}
		if(flag == false){
			if (strcmp(buf, "pid") == 0 || strcmp(buf, "ppid") == 0 || strcmp(buf, "name") == 0 || strcmp(buf, "stat") == 0 || strcmp(buf, "thre") == 0){
				if(line[i] != ' ' && line[i] != ':' && line[i] != '\t' && line[i] != '\n'){
					lineData[j] = line[i];
					j++;
				}	
			}
			if (strcmp(buf, "vmrs") == 0){
				if(line[i] != ' ' && line[i] != ':' && line[i] != '\t' && line[i] != '\n' && line[i] != 'k' && line[i] != 'b'){
					lineData[j] = line[i];
					j++;
				}	
			}	
		}
	}

    if (strcmp(buf, "pid") == 0){
		strcpy(processes[position].pid, lineData);
    }else if (strcmp(buf, "ppid") == 0){
		strcpy(processes[position].parentPid, lineData);
    }else if (strcmp(buf, "name") == 0){
		strcpy(processes[position].name, lineData);
    }else if (strcmp(buf, "stat") == 0){
		strcpy(processes[position].state, lineData);
    }else if (strcmp(buf, "thre") == 0){
		strcpy(processes[position].threads, lineData);
    }else if (strcmp(buf, "vmrs") == 0){
		strcpy(processes[position].memory, lineData);
    }
}

void analizeText(char *logFile) {
    int fileInput;
    int c;
    char *f = (char *)malloc(sizeof(char)*1);

    if((fileInput = open(logFile, O_RDONLY)) < 0){
		printf("cannot open file");
    }

    char line[500]; 
    memset(line, 0, 500);


    while((c = read(fileInput, f, 1)) > 0){
		*f = tolower(*f);
		if( *f == '\n'){
			strcat(line, "\n\0");
			processLine(line);
			memset(line, 0, 500);
		} else {
			strcat(line, f);
		}
    }
    close(fileInput);
}

void clear() {
  printf("\e[1;1H\e[2J"); 
}
