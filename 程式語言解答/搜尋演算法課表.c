/*29_3.搜尋演算法-查詢課表資料(40.0)*/
#include <stdio.h>
int main(){
int s,b,c,a[8][5]={0,1,2,3,0,
4,1,2,3,6,
7,5,6,4,6,
2,4,6,1,7,
5,4,7,5,3,
8,3,7,2,4,
7,2,1,6,8,
3,6,1,3,2};
scanf("%d %d",&b,&c);
for(;b!=0;){
    s=a[c-1][b-1];
    if(s==0) printf("自習\n");
    if(s==1) printf("國文\n");
    if(s==2) printf("英文\n");
    if(s==3) printf("數學\n");
    if(s==4) printf("地理\n");
    if(s==5) printf("歷史\n");
    if(s==6) printf("物理\n");
    if(s==7) printf("化學\n");
    if(s==8) printf("體育\n");
    scanf("%d %d",&b,&c);
}
   return 0;
}
