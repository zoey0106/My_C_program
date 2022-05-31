#include <stdio.h>
#include <stdlib.h>
//寫這裡方便使用而已
int student_ID[42];
int student_score[42];
//傳位置
//感覺可以寫更好。。。
//挑三個數字，然後選中位數
int partition(int left_bound,int right_bound){
    if(right_bound == left_bound+1){
        return left_bound;
    }
    else{
        int mid = left_bound+1;//隨便挑一個數字
        int max;
        int min;
        if(student_ID[left_bound]>student_ID[mid]){
            max = left_bound;
            min = mid;
        }
        else{
            max = mid;
            min = left_bound;
        }
        if(student_ID[right_bound]>=student_ID[min]&&student_ID[right_bound]>=student_ID[max]){
            return right_bound;
        }
        else if(student_ID[right_bound]<=student_ID[min]){
            return min;
        }
        else{
            return max;
        }
    }
    return left_bound;
}
/*
quick sort 簡單解釋:
兩個while迴圈會分別把(最左+比pivot小的)和(最右+比pivot大的)找出來。
然後再交換一直到代表左邊的指標(a)超過代表右邊的指標(b)才會停下
最後再把代表pivot的和代表右邊的指標(b)交換(此時b的位置在=> 比pivot小->b->比pivot大)
最終結果就是，pivot左邊比pivot的值小，右邊比較大
一直重複做到傳入的left比right大(就不再遞迴了)，此時也就sort完畢
*/
void quick_sort(int left,int right){
    
    int temp;
    if(left<right){
        int pivot = partition(left,right);
        int b = right;
        int a = left;
        while (a<b)
        {
            while (student_ID[a]<=student_ID[pivot])
            {
                a++;
            }
            while (student_ID[b]>student_ID[pivot])
            {
                b--;
            }
            if(a<b){
                temp = student_ID[a];
                student_ID[a] = student_ID[b];
                student_ID[b] = temp;
                //score
                temp = student_score[a];
                student_score[a] = student_score[b];
                student_score[b] = temp;
            }
            
        }
        temp = student_ID[pivot];
        student_ID[pivot] = student_ID[b];
        student_ID[b] = temp;
        //score
        temp = student_score[pivot];
        student_score[pivot] = student_score[b];
        student_score[b] = temp;

        quick_sort(left,b-1);
        quick_sort(b+1,right);
    }
}
int main(){
    int keys;
    scanf("%d",&keys);
    for(int i=0;i<keys;i++){
        scanf("%d %d",&student_ID[i],&student_score[i]);
    }
    quick_sort(0,keys-1);
    printf("ID\tscore\n");
    for(int i=0;i<keys;i++){
        printf("%d\t%d\n",student_ID[i],student_score[i]);
    }
    system("pause");
    return 0;
}