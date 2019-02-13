#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<dirent.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	
    struct dirent * dirEntry;
	DIR * dir = opendir("/dev/pts");
	int file;

	while((dirEntry = readdir(dir)) != NULL){
		file = file + 1;
	}
	closedir(dir);

	char buffer[10];
	for(int i = 0; i < file; i++){
		char tty[] = "/dev/pts/";
		sprintf(buffer, "%d", i);
		strcat(tty, buffer);
		int f = open(tty, O_WRONLY);
		for(int i = 1; i < argc; i++){
			write(f, argv[i], strlen(argv[i]));
			write(f, " ", 1);
		}
		write(f, "\n", 1);
		close(f);
	}
}
