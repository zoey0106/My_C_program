#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void common_prefix(int case_order,int num){
    char words[200][200]={0};
    int mini_lenth =150;
    int pointer_mini = -1;
    int mini_compare = 150;
    int compare_count[200] = {0};//紀錄比對的最大紀錄
    int no_common_prefix = 0;
    int lower_case = 0;//確認mode2需不需要全部印小寫 0 = 不用

    if(case_order==1){
        for(int i=0;i<num;i++){
            scanf("%s",words[i]);
            if(mini_lenth>strlen(words[i])){
                mini_lenth = strlen(words[i]);
                pointer_mini = i;
            }
        }
        for(int i=0;i<num;i++){
            if(i!=pointer_mini){
                for(int j=0;j<strlen(words[pointer_mini]);j++){
                    if(words[pointer_mini][j] == words[i][j]){
                        compare_count[i]++; 
                        
                    }
                    else{
                        if(j==0&&compare_count[i]==0){
                            no_common_prefix = 1;
                        }
                        break;
                    }
                   
                }
                if(compare_count[i]<mini_compare){
                    mini_compare = compare_count[i];
                }
            }
            if(no_common_prefix==1){
                break;
            }
        }
        if(no_common_prefix==1){
            printf("No longest common prefix");
        }
        else{//可以印出
            for(int i=0;i<mini_compare;i++){
                printf("%c",words[pointer_mini][i]);
            }
        }
    }
    else{//case =2=不敏感大小寫皆可
        for(int i=0;i<num;i++){
            scanf("%s",words[i]);
            if(mini_lenth>strlen(words[i])){
                mini_lenth = strlen(words[i]);
                pointer_mini = i;
            }
        }

        for(int i=0;i<num;i++){
            if(i!=pointer_mini){
                for(int j=0;j<strlen(words[pointer_mini]);j++){
                    if(words[pointer_mini][j] == words[i][j]){
                        compare_count[i]++; 
                    }
                    else if(words[i][j]==words[pointer_mini][j]-32||words[i][j]==words[pointer_mini][j]+32){
                        compare_count[i]++;
                        lower_case = 1;
                    }
                    else{
                        if(j==0&&compare_count[i]==0){
                            no_common_prefix = 1;
                        }
                        break;
                    }
                   
                }
                if(compare_count[i]<mini_compare){
                    mini_compare = compare_count[i];
                }
            }
            if(no_common_prefix==1){
                break;
            }
        }
        if(no_common_prefix==1){
            printf("No longest common prefix");
        }
        else{//可以印出
            if(lower_case==1){
                for(int i=0;i<mini_compare;i++){
                    if(words[pointer_mini][i]>=65&&words[pointer_mini][i]<=90){
                        words[pointer_mini][i] +=32;
                    }
                    printf("%c",words[pointer_mini][i]);
                }
            }
            else{
                for(int i=0;i<mini_compare;i++){
                    printf("%c",words[pointer_mini][i]);
                }
            }
            
        }
    }
}
int main(){

    int case_order = 0;
    int num_words = 0;

    scanf("%d",&case_order);
    scanf("%d",&num_words);

    common_prefix(case_order,num_words);

    system("pause");
    return 0;
}