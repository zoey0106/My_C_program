#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int numebr_courses;
/*<number of courses>
<course_id> <next> <piror> <course name>*/
struct course{
    int course_id;
    char name[60];
    struct course *next;
    struct course *prior;
    int int_next;
    int int_prior;
};
//印出現在課程，下一課程和上一課程
struct course *print_course(struct course *first,char order){
    if(order == 'n'){
        if(first -> next ==NULL){
            printf("There is no next course.\n");
        }
        else{
            first = first -> next;
        }
    }       
    else if(order == 'p'){
        if(first -> prior == NULL){
            printf("There is no previous course.\n");
        }
        else{
            first = first -> prior;
        }
    }
    return first;
}
//f的prior會是s
void conect_prior(struct course *f,struct course *s){
    f -> prior = s;
}
//f的next會是s
void conect_next(struct course *f,struct course *s){
    f -> next = s;
}
void conection(struct course *first,struct course *next){
    struct course *f = first; //以防萬一
    //先看以前的node
    //假定會從first一個一個串下去
    //如果next互相是彼此就會出事 不行再來修
    int count = 0;
    for(;f!=NULL;f = f->next){
        count++;
        if(f->next == NULL){
            //沒有連接且比對成功
            //把第一個的next連接上第二個
            if(f -> int_next == next -> course_id){
                conect_next(f,next);
            }
        }
        if(f->prior == NULL){
            if(f -> int_prior == next -> course_id){
                conect_prior(f,next);
            }
        }
        if(next -> next == NULL){
            if(next -> int_next == f ->course_id){
                conect_next(next,f);
            }
        }
        if(next -> prior == NULL){
            if(next -> int_prior == f->course_id){
                conect_prior(next,f);
            }
        }
        //最終手段
        if(count > numebr_courses){
            break;
        }
    }
    f = first;
    count = 0;
    for(;f!=NULL;f = f->prior){
        count++;
        if(f->next == NULL){
            //沒有連接且比對成功
            //把第一個的next連接上第二個
            if(f -> int_next == next -> course_id){
                conect_next(f,next);
            }
        }
        if(f->prior == NULL){
            if(f -> int_prior == next -> course_id){
                conect_prior(f,next);
            }
        }
        if(next -> next == NULL){
            if(next -> int_next == f ->course_id){
                conect_next(next,f);
            }
        }
        if(next -> prior == NULL){
            if(next -> int_prior == f->course_id){
                conect_prior(next,f);
            }
        }
        //最終手段
        if(count > numebr_courses){
            break;
        }
    }
}
int main(){
    
    numebr_courses = 0;
    scanf("%d",&numebr_courses);
    struct course *first = (struct course*)calloc(1,sizeof(struct course));//第一個node
    scanf ("%d %d %d %s",&(first->course_id),&(first->int_next),&(first->int_prior),first->name);
    
    //建立連結
    for(int i=1;i<numebr_courses;i++){
        struct course *next = (struct course*)calloc(1,sizeof(struct course));//建立node
        scanf ("%d %d %d %s",&(next->course_id),&(next->int_next),&(next->int_prior),next->name);
        conection(first,next);
    }
    //印出上下課程
    char order[2];
    while(1){
        printf("Current Course: %s\n",first ->name);
        printf("[n] Next course. [p] Prior course [q] Quit:");
        scanf("%s",order);
        if(order[0] == 'n'){
            first = print_course(first,order[0]);
        }
        else if(order[0] == 'p'){
            first = print_course(first,order[0]);
        }
        else if(order[0] == 'q'){
            break;
        }
    }
    free(first);//要修，不只有這個
    system("pause");
    return 0;
}