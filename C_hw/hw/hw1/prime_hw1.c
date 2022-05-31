#include<stdio.h>
#include<stdlib.h>
int main(){

    int number = 0;
    scanf("%d",&number);
    for(int i=2;i<=number;i++){
        while (number!=i)
        {
            if(number%i==0){
                printf("%d ",i);
                number=number/i;
            }
            else{
                break;
            }
        }
    }
    if(number!=1){
        printf("%d",number);
    }
    system("pause");

    return 0;
}