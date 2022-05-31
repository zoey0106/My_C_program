#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){

    char word[1000000]={0};
    scanf("%s",word);
    int num = 0;
    scanf("%d",&num);
    if(num==1){
        for(int i=0;i<strlen(word);i++){
            if(word[i]>=97&&word[i]<=122){
                word[i] -=32;
            }
        }
        printf("%s",word);
    }
    else if(num==2){
        for(int i=0;i<strlen(word);i++){
            if(word[i]>=65&&word[i]<=90){
                word[i] +=32;
            }
        }
        printf("%s",word);
    }
    else{
        for(int i=1;i<=strlen(word);i++){
            if(i%2==0){
                if(word[i]>=97&&word[i]<=122){
                word[i] -=32;
                }
            }
            else{
                if(word[i]>=65&&word[i]<=90){
                word[i] +=32;
            }
            }
        }
        printf("%s",word);
    }

    system("pause");
    return 0;
}