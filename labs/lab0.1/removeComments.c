#include <stdio.h>
int main(){

  FILE *file, *copy;
  file = fopen("test.c", "r+");
  copy = fopen("result.c", "w+");
  char c, d, line[10000];
  int n, q, i;

  n = 1;

  while(!feof(file)){
    i = 0;

    for(c =fgetc(file); c!=EOF && c!='\n';){
      if(c == '"' && d!='\\'){
          q = 0;
          for(;c !='\n' && q == 0;){
              line[i++] = c;
              d = c;
              c = fgetc(file);
              if(c == '"' && d != '\\'){
                  q = 1;
                  line[i++] = c;
                  d = c;
                  c = fgetc(file);
                  break;
              }
          }
      } else if(c == '/'){
        d = c;
        c = fgetc(file);
        if(c=='/'){
            for(;fgetc(file)!='\n';);
            break;
        }
        if(c == '*'){
          n = 1;
          for(c=fgetc(file); n == 1;){
            if( c == '*'){
              d=c;
              c=fgetc(file);
              if(c =='/'){
                  n = 0;
              }
            }else{
                d=c;
                c=fgetc(file);
            }
          }
        }
      }else{
        line[i++] = c;
        d = c;
        c = fgetc(file);
      }
    }
    line[i]= '\0';
    if(i > 0){
        line[i] = '\0';
        fprintf(copy,"%s\n",line);
        fflush(stdin);
    }
  }
  fgetc(file);
  fclose(file);
  fclose(copy);
  return 0;
}
