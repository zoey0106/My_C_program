#include<stdio.h>
#include<stdlib.h>
unsigned short swap_bytes(unsigned short i){
    i = ((i << 8) & 0xff00) | ((i >> 8) & 0x00ff);
    return i;
}
int main(){
    unsigned short i;
    unsigned short ans;
    scanf("%hx",&i);
    ans = swap_bytes(i);
    printf("%hx\n",ans);
    system("pause");
    return 0;
}