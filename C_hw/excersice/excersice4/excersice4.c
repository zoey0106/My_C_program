#include <stdio.h>
#include <stdlib.h>
typedef struct poly
{
    long int cof;
    long int exp;

}term;
term polynomail[100000];
int main(){
    int terms = 0;
    while (1)
    {
        scanf("%d",&terms);
        if(terms>0){
            break;
        }
        else{
            printf("The number must be greater than zero!\n");
        }
    }
  
    //printf("Enter each term with cof and exp:\n");
    for(int i=0;i<terms;i++){
        scanf("%ld",&polynomail[i].cof);
        while(polynomail[i].cof==0){
            printf("The number must be greater than zero!\n");
            scanf("%ld",&polynomail[i].cof);
        }
        scanf("%ld",&polynomail[i].exp);
    }
    for(int i=0;i<terms;i++){
        //printf("3x^2 + 2x^1 =")
        if(i==terms-1){
            printf("%ldx^%ld =\n",polynomail[i].cof,polynomail[i].exp);
        }
        else{
            printf("%ldx^%ld + ",polynomail[i].cof,polynomail[i].exp);
        }
    }
    
    int times = 0;
    while (1)
    {
        scanf("%d",&times);
        if(times<=0){
            printf("The number must be greater than zero!\n");
        }
        else{
            break;
        }
    }
    long int x = 0 ;
    long long int sum = 1 ;
    long long int total = 0;
    while (times>0)
    {   
        total = 0;
        sum = 1;
        while (1)
        {
            scanf("%ld",&x);
            if(x>0){
                break;
            }
            else{
                printf("The number must be greater than zero!\n");
            }
        }
        for(int i=0;i<terms;i++){
            for(int j=0;j<polynomail[i].exp;j++){
                sum = sum * x;
            }
            //printf("%lld is %ld^%ld\n",sum,x,polynomail[i].exp);
            sum *= polynomail[i].cof;
            total += sum;
            sum = 1;
        }
        printf("%lld\n",total);
        times--;
    }

    system("pause");
    return 0;
}