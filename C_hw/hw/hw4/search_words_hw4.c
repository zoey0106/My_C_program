#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){

    char artical[10000000]={0};//交出去時再放大
    char words[1000000]={0};//
    char buffer[1000000]={0};//
    int count_show_up = 0;

    fgets(artical,9999999,stdin);//這邊也要放大
    scanf("%s",words);
    //把最後的換行換成0
    if(artical[strlen(artical)-1]=='\n'&&artical[strlen(artical)-2]=='\r'){
        artical[strlen(artical)-1]='\0';
        artical[strlen(artical)-1]='\0';
    }
    else{
        artical[strlen(artical)-1]='\0';
    }
    int pointer = 0;
    int word_count = 0;//buffer的字數計算，字數不一樣直接不用比較
    int fail = 0;
    for(int i=0;i<=strlen(artical);i++){
        if(artical[i]!=' '&&artical[i]!='\0'){
            buffer[pointer]=artical[i];
            pointer++;
            word_count++;
        }
        else{
            if(word_count==strlen(words)){
                for(int j=0;j<strlen(words);j++){
                    if(buffer[j]!=words[j]){
                        fail = 1;
                        break;
                    }
                }
                if(fail == 0){
                    count_show_up++;
                }
                else{
                    fail = 0;
                }
            }
            pointer = 0;
            word_count = 0;
        }
    }

    printf("%d",count_show_up);
    system("pause");
    return 0;
}