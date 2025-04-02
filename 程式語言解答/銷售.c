/*25_8.二維陣列是矩陣-銷售報告(10.0)*/
#include <stdio.h>
int main(){
int sales[100][100]={0};
int p,s,i,j,k,temp;
for(k=1;k<=30;k++){
    for(i=0;i<4;i++){
        for(j=0;j<5;j++){
            temp=sales[i][j];
            scanf("%d %d %d",&s,&p,&sales[i][j]);
            temp=temp+sales[i][j];
            sales[i][j]=temp;
        }
    }
}
printf("  銷售員1 銷售員2 銷售員3 銷售員4 總計\n");
int pt;
for(i=0;i<5;i++){
    printf("產品%d ",i+1);
    pt=0;
    for(j=0;j<4;j++){
        printf("%d  ",sales[j][i]);
        pt=pt+sales[j][i];
    }
    printf("%d\n",pt);
}
printf("總計  ");
s=0;
for(i=0;i<4;i++){
    temp=0;
    for(j=0;j<5;j++){
        temp=temp+sales[i][j];
    }
    printf("%d  ",temp);
    s=s+temp;
}
printf("%d",s);
printf("\n");
   return 0;
}


