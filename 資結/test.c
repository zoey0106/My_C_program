#include<stdio.h>
#include <stdlib.h>
#define	GET_BIT(x, bit)	((x & (1 << bit)) >> bit)	/* 獲取第bit位 */
int main(){
    //unsigned int a=0x51;
    //printf("0x%x的對應的二進制是：%d %x %x %x %x %x %x %x \n",a,GET_BIT(a,7),GET_BIT(a,6),GET_BIT(a,5),GET_BIT(a,4),GET_BIT(a,3),GET_BIT(a,2),GET_BIT(a,1),GET_BIT(a,0));
    //printf("0x%x的第0位的值是：%x\n",a,GET_BIT(a,0));
   int num; 
   scanf("%d",&num);
   while (num!=1)
    {
        
        printf("%d二進位:",num);
        for(int i = 23;i>=0;i--){
            printf("%d ",GET_BIT(num,i));
        }
        scanf("%d",&num);
        printf("\n");
    }
    
    
    
    system("pause");
    return 0;
}