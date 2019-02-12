#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>  
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/* filecopy:  copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp)
{
    int c;
    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);

}

int main(int argc, char *argv[])
{
    int r;
    char *f;
    f = (char *) malloc(1);
    int file = open(*++argv, O_RDONLY);

    if (argc == 1){ 
        /* no args; copy standard input */
    }else {
        while (--argc > 0)
	        if (file < 0) {
                fprintf(stderr, "File doesn't exists\n");
                return 1;
            } else {
                while((r = read(file,f,1)) > 0){
		            write(1, f, r);
		        }
                close(file);
            }
    }
    if (ferror(stdout)) {
        fprintf(stderr, "Error in write\n");
        return 2;
    }
    return 0;
}