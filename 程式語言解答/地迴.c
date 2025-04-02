#include<stdio.h>
int k(int n);
int main(){
    int n;
    scanf("%d",&n);
    while(n>0){
        n=n-1;
        printf("%d\n",k(n));
        scanf("%d",&n);
    }


    return 0;


}
int k(int n){
    if(n==0||n==1)return n;
    else return 2*k(n-1)+3*k(n-2);
}
