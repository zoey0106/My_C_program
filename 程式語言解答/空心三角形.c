/*b7dc0a78fd09463ab213c4bc92092443_6.D卷-2-陣列函數-期末考-空心三角形(10.0)*/
#include <stdio.h>
int main(){
    int num;
    scanf("%d",&num);
    int num2=num-2;
    int num3=num2/2;
    int num4=num/2;
    int i=0;
    while(i<num4){
        printf(" ");
        i++;
    }
    printf("*\n");
    num4--;
    i=0;
    int v=0;
    while(i<num3){
        for(v=i;v<num4;){
            printf(" ");
            v++;
        }
        printf("*");
        for(v=i;v<(i+1);){
            printf(" ");
            v++;
        }
        printf("*\n");
        i++;
    }
    for(v=0;v<num;v++){
        printf("*");
    }
    return 0;
}
