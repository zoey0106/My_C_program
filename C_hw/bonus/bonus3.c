#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int numbers[1001]={0};
void swap(int x,int y){
    int temp = numbers[x];
    numbers[x] = numbers[y];
    numbers[y] = temp;
}
void selection(int index){
    int min;
    for(int i=0;i<index-1;i++){
        int min = i;
        for(int j=i;j<index;j++){
            if(numbers[j] < numbers[min]){
                min = j;
            }
        }
        if(min != i){
            swap(min,i);
        }
        for(int j=0;j<index;j++){
            printf("%d ",numbers[j]);
        }
        printf("\n");
    }
}
//的部分是可以精進的部分
void bubble(int index){
    int bubble_index = index;
    //int swap_flag = 0;
    for(int i=0;i<index-1;i++){
        for(int j=1;j<bubble_index;j++){
            if(numbers[j] < numbers[j-1]){
                swap(j,j-1);
                //swap_flag = 1;
            }
        }
        bubble_index--;
        for(int k=0;k<index;k++){
            printf("%d ",numbers[k]);
        }
        printf("\n");
        /*
        if(swap_flag == 0){
            break;
        }
        */
    }
}
void insertion(int index){
    for(int i=1;i<index;i++){
        int temp = numbers[i];
        for(int j = i-1;j>=0;j--){
            if(numbers[j]>temp){
                swap(j,j+1);
            }
        }
        for(int j=0;j<index;j++){
            printf("%d ",numbers[j]);
        }
        printf("\n");
    }
    
}
int main(){
    int index;
    scanf("%d",&index);
    for(int i=0;i<index;i++){
        scanf("%d",&numbers[i]);
    }
    char sort_option[10];
    scanf("%s",sort_option);
    if(strcmp(sort_option,"BUBBLE")==0){
        bubble(index);
    }
    else if(strcmp(sort_option,"INSERTION")==0){
        insertion(index);
    }
    else if(strcmp(sort_option,"SELECTION")==0){
        selection(index);
    }


    system("pause");
    return 0;
}