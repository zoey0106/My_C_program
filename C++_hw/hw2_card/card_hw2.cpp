#include <iostream>
#include<stdlib.h>
#include <cstring>
#include <fstream>
#include <cstdlib> /* 亂數相關函數 */
#include <ctime>   /* 時間相關函數 */
#include <time.h>
#include <stdbool.h>//bool
using namespace std;
//用來計算時間
timespec diff(timespec start, timespec end) {
  timespec temp;
  if ((end.tv_nsec - start.tv_nsec) < 0) {
    temp.tv_sec = end.tv_sec - start.tv_sec - 1;
    temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec - start.tv_sec;
    temp.tv_nsec = end.tv_nsec - start.tv_nsec;
  }
  return temp;
}
// Return this number if it is a single digit, otherwise,
// (3)return the sum of the two digits
int getDigit (int number){
    int num = number - 48; //求真正數字
    num *=2; 
    if(num>=10){
        num -=9; //-9就為兩digits的加總        
    }
    return num;
}
// (2)Get the result from Step 2
int sumofDoubleEvenPlace (const string& cardNumber){
    int sum_second = 0;
    int every_second = 0;
    for(int i=cardNumber.length()-1;i>=0;i--){
        if(every_second == 1){//偶數為1 需計算
            sum_second += getDigit((int)cardNumber[i]);
            every_second = 0;
        }
        else{
            every_second = 1;
        }
    }
    return sum_second;
}
// (4)Return sum of odd-place digits in the card number
int sumOfOddPlace (const string& cardNumber){
    int every_second = 0;
    int sum_first = 0;
    for(int i=cardNumber.length()-1;i>=0;i--){
        if(every_second == 1){//1表示為偶不用計算
            every_second = 0;
        }
        else{
            sum_first += ((int)cardNumber[i]-48); //-48為真正數字
            every_second = 1;
        }
    }
    return sum_first;
}
// (1)Return true if the card number is valid
bool isvalid (const string& cardNumber){
    int sum_first = sumOfOddPlace(cardNumber);
    int sum_second = sumofDoubleEvenPlace(cardNumber);
    int sum = (sum_first + sum_second)%10 ;
    if(sum == 0){
        return true;
    }
    else{
        return false;
    }
}
// (5)Return true if substr is the prefix for cardNumber
bool startsWith (const string& cardNumber,const string& substr){
    int not_same = 0;
    for(int i=0;i<substr.length();i++){//比對substr和cardNumber有沒有前面完全相同
        if(cardNumber[i]!=substr[i]){
            not_same = 1;
        }
    }
    if(not_same == 0){
        return true;
    }
    else{
        return false;
    }

    return false;
}
//print the accurate brand
void card_print(const string& cardNumber){
    string Visa = "4";
    string Master = "5";
    string American = "37";
    string Discover = "6";

    if(startsWith(cardNumber,Visa)){
        cout << "Visa card" <<endl;
    }
    else if(startsWith(cardNumber,Master)){
        cout << "MasterCard card" <<endl;
    }
    else if(startsWith(cardNumber,American)){
        cout << "American card" << endl;
    }
    else if(startsWith(cardNumber,Discover)){
        cout << "Discover card" <<endl;
    }
    else{
        cout << "Unknow brand card" << endl;
    }
}
//生成指定的虛擬卡號
void generator(const string& buffer){
    struct timespec tt1, tt2;//c
    long timedif;
    clock_gettime(CLOCK_REALTIME, &tt1);//取得最先的時間
    
    int minus_num = 0;
    int intail_num = 0;
    string Visa = "004";
    string Master = "005";
    string American = "0037";
    string Discover = "006";
    char card_number[17] = {0};
    int valid_order = 0;
    if(startsWith(buffer,Visa)){
        card_number[0] = '4';
        minus_num = 1;
        valid_order = 1;
        cout << "Generated a valid Visa card : " ;
    }
    else if(startsWith(buffer,Master)){
        card_number[0] = '5';
        minus_num = 1;
        valid_order = 1;
        cout << "Generated a valid MasterCard card : " ;
    }
    else if(startsWith(buffer,American)){
        card_number[0] = '3';
        card_number[1] = '7';
        minus_num = 2; 
        valid_order = 1;
        cout << "Generated a valid American Express card : " ;
    }
    else if(startsWith(buffer,Discover)){
        card_number[0] = '6';
        minus_num = 1;
        valid_order = 1;
        cout << "Generated a valid Discover card : " ;
    }
    else{
        cout << "unknow brand card, cant generate!" <<endl;
    }

    if(valid_order == 1){
        //留最後一個為0待改
        for(int i=minus_num;i<15;i++){
            card_number[i] = (int) ( (10-1) * (double)rand()/RAND_MAX );
            card_number[i] += 48;
        }
        if(minus_num==2){
            card_number[14] = '0';
        }
        else{
            card_number[15] = '0'; 
        }
        int sum_first = sumOfOddPlace(card_number);
        int sum_second = sumofDoubleEvenPlace(card_number);
        int sum = (sum_first + sum_second)%10 ;
        if(sum!=0){
            sum = 10 - sum;//如果是0就不用補數
        }
        if(minus_num ==2){
            card_number[14] = sum + 48;
        }
        else{
            card_number[15] = sum + 48;
        }
        cout << card_number;

        clock_gettime(CLOCK_REALTIME, &tt2);//取得generate後的時間
        cout << "   ->  total time (clock_gettime) = " << diff(tt1, tt2).tv_sec << "." << diff(tt1, tt2).tv_nsec <<"s"<< endl;
    }
    

}
int main(int argc,char *argv[]){
    
    string buffer;
    int check_valid = 0;
    int ran_num = 0;
    srand(time(NULL));//亂數種子
    ifstream myFile;

    myFile.open(argv[1],ios::in);//要讀取的檔案
    if(!myFile.is_open()){//沒打開就fail
        cout << "fail open file" << endl;
        return 0;
    }

    //下一行不是空的都繼續執行
    while (getline(myFile, buffer)) {
        //13~16才是valid的
        if(buffer.length()>=13&&buffer.length()<=16){
            // ture表示valid
            if(isvalid(buffer)){
                cout << buffer << ":an vaild ";
                card_print(buffer);
            }
            else{
                cout << buffer << ":an invaild ";
                card_print(buffer);
            }
        }
        else if(buffer.length()==3||buffer.length()==4){//004...0037...
            generator(buffer);
        }
        else if(buffer.length()!=0){
            cout << "You may input the wrong command or miss some card's num!" << endl;
        }
        
    }


    // Close file
    myFile.close();

    system("pause");
    return 0;
}