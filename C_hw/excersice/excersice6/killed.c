#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct game{
    char name[60];
    struct game *next;
    struct game *prior;
};
int main(){
    
    int people = 0;
    scanf("%d",&people);
    struct game *first = (struct game*)calloc(1,sizeof(struct game));//第一個node
    scanf("%s",first->name);
    struct game *prior = first;
    //建立連結
    for(int i=1;i<people;i++){
        struct game *next = (struct game*)calloc(1,sizeof(struct game));//node
        scanf ("%s",next->name);
        //把前面的next連起來
        prior ->next = next;
        //把後面的prior連起來
        next -> prior = prior;
        //把最後面的next連上最前面的節點
        if(i == people-1){
            next -> next = first;
        }
        //把最前面的prior連起來
        if(i == people-1){
            first ->prior = next;
        }
        prior = next;
    }
    int cycle;
    char direction[30];
    scanf("%d %s",&cycle,direction);
    cycle = cycle % people;//might wrong
    struct game *pointer;//類似temp的東西
    if(strcmp(direction,"CLOCKWISE") == 0){
        for(int i=1;i<people;i++){
            for(int j=0;j<cycle;j++){
                first = first->next; 
            }
            printf("%s KILLED\n",first->name);
            pointer = first->next;//先把下一個start存起來
            first -> prior -> next = first ->next;
            first -> next -> prior = first ->prior;
            free(first);
            first = pointer; 
        }
        printf("%s SURVIVE\n",first ->name);
    }
    else{
        for(int i=1;i<people;i++){
            for(int j=0;j<cycle;j++){
                first = first->prior; 
            }
            printf("%s KILLED\n",first->name);
            pointer = first->prior;//先把下一個start存起來
            first -> prior -> next = first ->next;
            first -> next -> prior = first ->prior;
            free(first);
            first = pointer; 
        }
        printf("%s SURVIVE\n",first ->name);
    }
    system("pause");
    return 0;
}