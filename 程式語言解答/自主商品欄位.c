/*28_8.排序演算法-自主學習(5.0)*/
#include <cstdio>
#include <algorithm>
#include <cstring>
struct student{
    int id;
    char name[200];
    int price;
    double rate;
};
struct student students[300];

int cmp_1(struct student a,struct student b){
    return a.id < b.id;
}
int cmp_2(struct student a,struct student b){
    if (strcmp(a.name ,b.name)>=1) return 0;
    else return 1;
}
int cmp_3(struct student a,struct student b){
    return a.rate < b.rate;
}
int cmp_4(struct student a,struct student b){
    return a.price < b.price;
}
int main(){
    int a,b = 0;
    char word[200];
    while(scanf("%d",&a)){
        if(a == -1)
            break;
        students[b].id = a;
        scanf(" %s %d %lf",&students[b].name,&students[b].price,&students[b].rate);
        b++;
    }
    while(scanf("%d",&a)){
        if(a==-1)
            return 0;
        printf("ID\tNAME\tPRICE\tRATE\n");
        if(a==1){
            sort(students,students+b,cmp_1);
            for(int i = 0;i < b;i++){
                printf("%d\t%s\t%d\t%.1f\n",students[i].id,students[i].name,students[i].price,students[i].rate);
            }
        }
        else if(a==2){
            sort(students,students+b,cmp_2);
            for(int i = 0;i < b;i++){
                printf("%d\t%s\t%d\t%.1f\n",students[i].id,students[i].name,students[i].price,students[i].rate);
            }
        }
        else if(a==3){
            sort(students,students+b,cmp_4);
            for(int i = 0;i < b;i++){
                printf("%d\t%s\t%d\t%.1f\n",students[i].id,students[i].name,students[i].price,students[i].rate);
            }
        }
        else if(a==4){
            sort(students,students+b,cmp_3);
            for(int i = 0;i < b;i++){
                printf("%d\t%s\t%d\t%.1f\n",students[i].id,students[i].name,students[i].price,students[i].rate);
            }
        }
    }
    return 0;
}
