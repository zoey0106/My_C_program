#include <stdio.h>
int main(){
    int number[6];
    for(int i = 0;i < 6;i++){
        scanf("%d",&number[i]);
    }
    int z = 1;
    for(int i = 0;i<5;i++){

    for(int i = 0;i < 5;i++){
        if(number[i+1]<number[i]){
            int a = number[i+1];
            number[i+1] = number[i];
            number[i] = a;
        }
    }
    printf("第%d回合\n",z++);
    for(int i = 0;i < 6;i++){
        printf("%d ",number[i]);
    }
    printf("\n");
    }
    return 0;
}
