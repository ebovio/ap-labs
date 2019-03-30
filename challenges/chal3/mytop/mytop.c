#include <stdio.h>
#include <string.h>
#include <dirent.h>

void clear();

int main(){
	 // Place your magic here
	DIR *d = opendir("/proc/");
	struct dirent *dir;
	FILE *fp;
	char path[30],
	c;
	int p = 0;

	strcpy(path, "/proc/");
	while((dir = readdir(d)) != NULL) {
		if(dir -> d_name[0] >= 48 && dir -> d_name[0] <= 57){
			strcat(path, dir -> d_name);
			strcat(path, "/status");
			printf("%s\n", path);

			fp = fopen(path, "r");

			while((c = getc(fp)) != 'P') {
			}

			while(p < 2){
				while((c = getc(fp)) != '\n'){
					printf("%c", c);
				}
				printf("\n");
				p++;
			}
			p = 0;
			strcpy(path, "/proc/");
		}
	}
	clear();
  	return 0;
}

void clear() {
  printf("\e[1;1H\e[2J"); 
}