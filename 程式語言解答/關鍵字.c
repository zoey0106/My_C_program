/*29_4.搜尋演算法-查關鍵字(5.0)*/
#include <stdio.h>
int main(){
    char str[31];
    char find[31];
    scanf("%s %s",str,find);
    int count=0;
    int i=0;
    while(*(str+i)!='\0'){
        i++;
        count++;
    }
    i=0;
    int count2=0;
    while(*(find+i)!='\0'){
        i++;
        count2++;
    }
    i=0;
    int check=0;
    int v=0;
    int count3=0;
    while(i<count){
        if(str[i]==find[v]){
            check++;
            i++;
            v++;
            if(check==count2){
                check=0;
                v=0;
                count3++;
            }
        }
        else{
            check=0;
            v=0;
            i++;
        }
    }
    printf("%d",count3);

    return 0;
}
