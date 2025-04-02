#include<stdio.h>
#include <stdlib.h>
#define	GET_BIT(x, bit)	((x & (1 << bit)) >> bit)	/* 獲取第bit位 */
int pow2(int num,int t){
    int result = 1;
    for(int i=0;i<t;i++){
        result *= num;
    }

    return result;
}
int main(){

    unsigned int p,m,n;
    scanf("%u %u %u",&p,&m,&n);
    unsigned int array[10000]= {0};//可以開大但只能用規定bits
    int pointer = 0;
    while(1){
        
        unsigned int id;
        scanf("%d",&id);
        unsigned int id_id = id*id%p%m;
        pointer = id_id/32;
        id_id = id_id - 32*pointer;
        if(GET_BIT(array[pointer],id_id)!=1){
            printf("%u 1\n",id);
            array[pointer] += pow2(2,id_id);
        }
        else{
            printf("%u 0\n",id);
        }
        n--;
        if(n==0){
            break;
        }
    }
    system("pause");
    return 0;
}