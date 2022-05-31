#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[]){

    char *planet[]={"Mercury","Venus","Earth",
                    "Mars","Jupiter","Saturn",
                    "Uranus","Neptune","Pluto"};
    int i,j;
    int count = 0;
    for(int i=0;i<argc;i++){
        for(int j=0;j<9;j++){
            if(strcmp(argv[i],planet[j])==0){
                printf("%s is planet %d\n",argv[i],j+1);
                count=1;
                break;
            }
           
        } 
        if(count==0){
                printf("%s is not a planet\n",argv[i]);
        }
        count=0;
    }

    return 0;
}