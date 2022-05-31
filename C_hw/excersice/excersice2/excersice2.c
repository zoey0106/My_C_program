#define _GNU_SOURCE
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#define DEBUG 1
#define Print_first(buffer,j,pointer_article) while ((buffer+j)!=pointer_article)\
                    {\
                        printf("%c",buffer[j]);\
                        j++;\
                    }
#define Print_second(s2,lenth,d) for(d =0;d<lenth;d++)\
                    {\
                        printf("%c",s2[d]);\
                    }
#define Print_left(left,buffer,j) if(left>0){\
                        while (left>0)\
                        {\
                            printf("%c",buffer[j]);\
                            j++;\
                            left--;\
                        }\
                        printf("\n");\
                    }\
                    else{\
                        printf("\n");\
                    }
                    
void replace_maching(char s1[],char s2[],char buffer[],int case_alpha){
    //把要找到的字串全部翻成小寫

    #if DEBUG
    if(case_alpha==1){
        printf("this is case 1\n");
    }
    else{
        printf("this is case 0\n");
    }
    #endif

    if(case_alpha==1){
        for(int i=0;i<strlen(s1);i++){
            s1[i]=tolower(s1[i]);
        }
    }
    char lower_buffer[500]={0};
    int ch;
    int j=0;
    while ((ch=getchar())!=EOF)
    {   
        //確認是否為英文字,數字,dash
        if(isalpha(ch)!=0||isdigit(ch)!=0||ch==45){
            buffer[j]=(char)ch;
            j++;
        }else{
            //若buffer內無東西就跳過
            if(strlen(buffer)!=0){
                //
                //printf("buffer$$ :%s $$\n",buffer);
                #if DEBUG
                printf("the word is: %s\n",buffer);
                #endif
                
                j=0;
                char *pointer_article;
                if(case_alpha==0){
                    pointer_article = NULL;
                    pointer_article = strstr(buffer,s1);//比對有無此字串
                }
                else{
                    for(int i=0;i<strlen(buffer);i++){
                        lower_buffer[i]=tolower(buffer[i]);
                    }
                    //printf("lower_buffer:$$%s $$\n",lower_buffer);
                    pointer_article = NULL;
                    pointer_article = strstr(lower_buffer,s1);//比對有無此字串
                    if(pointer_article!=NULL){
                        int count=0;
                        //讓指針指向真正的buffer
                        for(int m=0;m<strlen(lower_buffer);m++){
                            if((lower_buffer+m)!=pointer_article){
                                count++;
                            }
                            else{
                                break;
                            }
                        }
                        pointer_article = buffer+count;
                    }
                    memset(lower_buffer,0,strlen(lower_buffer));
                }
                
                //如果比對成功就進入
                if(pointer_article!=NULL){
                    //印出替換字串前的字串
                    Print_first(buffer,j,pointer_article);
                    //印出替換字串
                    int d = 0;
                    Print_second(s2,strlen(s2),d);
                    j+=strlen(s1);//j為已經印出的總字數(只談原本的token)
                    int left = strlen(buffer)-j;//left為剩下該印出的字串總數不包含0
                    Print_left(left,buffer,j);
                }
                j=0;
                memset(buffer,0,strlen(buffer));//為了讓下一次印出buffer時不要出錯而初始化
            }
            
        }
        
    }
}
int main(){

    char order [1000]={0};
    char found_string [500]={0},replace[500]={0};

    fgets(order,999,stdin);

    if(order[strlen(order)-1]=='\n'&&order[strlen(order)-2]=='\r'){
        order[strlen(order)-1]='\0';
        order[strlen(order)-1]='\0';
    }
    else{
        order[strlen(order)-1]='\0';
    }
    int exit = 0;
    int i=0;
    //把需要被找到替換的token出來
    while(1){
        if(order[i]!=' '){
            //確認是否為英文字,數字,dash
            if(isalpha((int)order[i])!=0||isdigit((int)order[i])!=0||(int)order[i]==45){
                found_string[i]=order[i];
                i++;
            }
            else{
                printf("The input format: string1 string2 [parameter]");
                exit=1;
                break;
            }
        }
        else{
            break;
        }
    }
    i++;
    found_string[i]='\0';
    int j=0;
    //替換的token
    if(exit==0){
        while(1){
        if(order[i]!='\0'&&order[i]!=' '){
            //確認是否為英文字,數字,dash
            if(isalpha((int)order[i])!=0||isdigit((int)order[i])!=0||(int)order[i]==45){
                replace[j] =order[i];
                j++;
                i++;
            }
            else{
                printf("The input format: string1 string2 [parameter]");
                exit=1;
                break;
            }
        }
        else{
            break;
        }
    }
    }
    replace[j]='\0';

    int case_ignore = 0;
    if(exit==0){
        i++;
        if(order[i]!='\0'){//設定是最後(\n)我會改放\0所以如果-i後還有東西就是錯的包括空格
            if(order[i]=='-'&&order[++i]=='i'){
                i++;
                if(order[i]=='\0'){
                    case_ignore=1;
                }
                else{
                printf("The input format: string1 string2 [parameter]");
                exit=1;
                }
            }
            else{
                printf("The input format: string1 string2 [parameter]");
                exit=1;
            }
        }
    }
    

    char buffer[500]={0};
    
    if(exit==0){
        replace_maching(found_string,replace,buffer,case_ignore);   
    }

    system("pause");
    return 0;
}