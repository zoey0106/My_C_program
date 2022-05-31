#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct info
{
    char name[50];
    char attribute[10];
    int attack;
    int hp;
    //
    int star;
}data;
int compare_hp(const void *a,const void *b){
    data *p = (data*)a;
    data *p2 = (data*)b;
    if(p->hp==p2->hp){ 
        return 0;
    }
    return p->hp > p2->hp ? 1:-1;
}
int compare_attack(const void *a,const void *b){
    data *p = (data*)a;
    data *p2 = (data*)b;
    if(p->attack==p2->attack){ 
        return 0;
    }
    return p->attack < p2->attack ? 1:-1;
}
int compare_name(const void *a,const void *b){
    data *p = (data*)a;
    data *p2 = (data*)b;
    int lenth_p = strlen(p->name);
    int lenth_p2 = strlen(p2->name);
    int min;
    if(lenth_p==lenth_p2){
        min = -1;
    }
    else if(lenth_p>lenth_p2){
        min = 2;//p>p2
    }
    else{
        min = 1;//p2>p
    }
    //一樣長
    if(min == -1){
        for(int i=0;i<lenth_p;i++){
            if(p->name[i]>p2->name[i]){
                return 1;
            }
            else if(p->name[i]<p2->name[i]){
                return -1;
            }
        }
        return 0;
    }
    else if(min == 2){
        for(int i=0;i<lenth_p2;i++){
            if(p->name[i]>p2->name[i]){
                return 1;
            }
            else if(p->name[i]<p2->name[i]){
                return -1;
            }
        }
        return 1;//p前面都和p2一樣，p2比較短要在前面，所以p>p2
    }
    else{//min = 1
        for(int i=0;i<lenth_p;i++){
            if(p->name[i]>p2->name[i]){
                return 1;
            }
            else if(p->name[i]<p2->name[i]){
                return -1;
            }
        }
        return -1;//p前面都和p2一樣，p比較短要在前面，所以p2>p
    }
    return 0;
}
int compare_attribute(const void *a,const void *b){
    data *p = (data*)a;
    data *p2 = (data*)b;
    if(p->star == p2->star){
        if(p->hp == p2->hp){
            return 0;
        }
        else{
            return p->hp > p2->hp ? 1:-1;//血少的順位前面
        }
    }
    return p->star > p2->star ? 1:-1;
}
void list(data pokemon[],int numbers){
    for(int i=0;i<numbers;i++){
        printf("%s %s %d %d\n",pokemon[i].name,pokemon[i].attribute,pokemon[i].attack,pokemon[i].hp);
    }
}
int main(){

    int numbers;
    int orders;
    data pokemon[100001];//之後調大100001
    char order[50];
    scanf("%d %d",&numbers,&orders);

    for(int i=0;i<numbers;i++){
       scanf("%s %s %d %d",pokemon[i].name,pokemon[i].attribute,&pokemon[i].attack,&pokemon[i].hp);
       switch (pokemon[i].attribute[0]){
        case 'W':
           pokemon[i].star = 0;
           break;
        case 'F':
           pokemon[i].star = 1;
           break;
        case 'E':
           pokemon[i].star = 2;
           break;
        case 'L':
           pokemon[i].star = 3;
           break;
        case 'D':
           pokemon[i].star = 4;
           break;
       default:
           pokemon[i].star = 5;
           break;
       }
    }
    for(int i=0;i<orders;i++){
        scanf("%s",order);
        printf("Case #%d:\n",i+1);
        if(strcmp(order,"NAME")==0){
            qsort(pokemon,numbers,sizeof(pokemon[0]),compare_name);
            list(pokemon,numbers);
        }
        else if(strcmp(order,"ATTRIBUTE")==0){
            qsort(pokemon,numbers,sizeof(pokemon[0]),compare_attribute);
            list(pokemon,numbers);
        }
        else if(strcmp(order,"ATTACK")==0){
            qsort(pokemon,numbers,sizeof(pokemon[0]),compare_attack);
            list(pokemon,numbers);
        }
        else if(strcmp(order,"HP")==0){
            qsort(pokemon,numbers,sizeof(pokemon[0]),compare_hp);
            list(pokemon,numbers);
        }
        memset(order,0,50);
    }
    system("pause");
    return 0;
}