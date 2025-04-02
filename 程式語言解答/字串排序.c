#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char w[100][100];
int compare(const void *a, const void *b)
{
      char *c = (char *)a;
      char *d = (char *)b;
      return strcmp(c,d);
}
int main(){
    int i = 0;
    while(scanf("%s",&w[i++])!=EOF)
    qsort((void *)w, i, sizeof(w[0]), compare);
    for(int g = 0;g < i-1;g++){
        printf("%s\n",w[g]);
    }
    return 0;
}
