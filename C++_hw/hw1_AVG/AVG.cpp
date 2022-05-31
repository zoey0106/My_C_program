#include <iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
//功能:把不是合法分數的區分開來，包含09，0.0，以及任何不是數字的char
//0=valid 1=invalid
int check_invalid_input(const char *str){
    int check=0;
    for(int i=0;i<strlen(str);i++){
        if(i==0){//不可第一位為0
            if(str[i]<49||str[i]>58){
                check=1;
            }//可為-1
            if(str[i]=='-'){
                check=0;
           
           
            }
        }
        else{//0~9
            if(str[i]<47||str[i]>58){
                check=1;
            }
        }
        if(check==1){
            break;
        }
    }
    return check;
}
int AVG_printer(char condition[]){
    int invalid_condition = 0;
    unsigned int grades[200];//等等要改大
    char grade[100];
    int tempt_grade = 0; 
    unsigned int sum_of_grades = 0;
    int pointer=0;
    while(invalid_condition==0){
        cout <<"please input your score:\n";
        cin >> grade;
        invalid_condition = check_invalid_input(grade);
        if(invalid_condition == 0){
            tempt_grade=atoi(grade);//改成數字確認大小
            memset(grade,0,strlen(grade));
            if(tempt_grade<=100&&tempt_grade>=0){
                grades[pointer++]=tempt_grade;
                sum_of_grades += tempt_grade;
            }
            else if(tempt_grade == -1){
                invalid_condition=2;
            }
            else{
                invalid_condition=1;
            }
        }
    }
    if(invalid_condition==1){
        cout << "Invalid input! Do you want to input another set of grades? (Y/N): ";
        cin >> condition;
        if(condition[0]=='Y'||condition[0]=='y'){
            cout<<"new set bigin:\n";
            return 1;
        }
        else{
            cout<<"finish!\n";
            return 0;
        }
    }
    else if(invalid_condition==2){
        if(pointer!=0){
            cout<< "the Average of these grades is: "; 
            cout<< (float)sum_of_grades/pointer;
            cout<<"\nnumber of times user inputs: ";
            cout<< pointer;
        }
        else{
            cout<< "you didn't input any number yet,please try again!\n";
        }
        cout<<"\nDo you want to input another set of grades? (Y/N):";
        cin >> condition;
        if(condition[0]=='Y'||condition[0]=='y'){
            cout<<"new set bigin:\n";
            return 1;
        }
        else{
            cout<<"finish!\n";
            return 0;
        }
    }
    return 0;
}
int main(){
    
    
    char loop_condition[2]={'N'};
    int conti_break=1;
    cout<<"Notice: # the AVG result will show up if you input -1 #\n";
    while (conti_break==1)
    {   
        //conti_break==0的話代表不打算繼續執行了
        conti_break = AVG_printer(loop_condition);
    }

    system("pause");
    return 0;
}