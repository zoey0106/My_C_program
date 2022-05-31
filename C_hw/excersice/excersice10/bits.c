#include <stdio.h>
#include <stdlib.h>
int main(){
    int ID_num;
    scanf("%d",&ID_num);
    char *arr_ID = (char *)calloc(ID_num/4, sizeof(char));
    int inputs_ID;
    while (scanf("%d",&inputs_ID)!=EOF)
    {
        int index = inputs_ID/4;//陣列的第幾格
        int bits = inputs_ID%4;//一byte中的第幾順位 (3->2->1->0)
        int num;
        switch (bits)
        {
        case 0:
            num = arr_ID[index] & 3;//0011
            if(num >= 3){printf("GOOD BYE\n");}
            else{printf("PASS\n"); arr_ID[index]= arr_ID[index] + 0b0001;}
            break;
        case 1:
            num = (arr_ID[index] >> 2) & 3;
            if(num >= 3){printf("GOOD BYE\n");}
            else{printf("PASS\n"); arr_ID[index]= arr_ID[index] + 0b0100;}
            break;
        case 2:
            num = (arr_ID[index] >> 4) & 3;
            if(num >= 3){printf("GOOD BYE\n");}
            else{printf("PASS\n"); arr_ID[index]= arr_ID[index] + 0b00010000;}
            break;
        case 3:
            num = (arr_ID[index] >> 6) & 3;
            if(num >= 3){printf("GOOD BYE\n");}
            else{printf("PASS\n"); arr_ID[index]= arr_ID[index] + 0b01000000;}
            break;
        default:
            printf("false\n");
            break;
        }
        
    }
    

    free(arr_ID);
    system("pause");
    return 0;
}