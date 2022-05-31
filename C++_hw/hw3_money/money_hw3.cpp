#include <iostream>
#include <string.h>
#include <cmath>
#include <ctype.h>
using namespace std;

class Coins {
    private:
        double money;
        int q;
        int d;
        int n;
        int p;
    public:
        Coins(char *s); //建構函數
        inline void monetary(const double money);//換算錢的函數
        void set_money(const char *s){//把money從字串轉成int
            money = stod(s);
        }
        inline const double re_m(){
            return money;
        }
        const void print();//印qdnp
        inline const int print_cash_q(){
            return q;
        }
        inline const int print_cash_d(){
            return d;
        }
        inline const int print_cash_n(){
            return n;
        }
        inline const int print_cash_p(){
            return p;
        }
};
Coins::Coins(char *s){
    int count = 0;
    while (1)
    {
        if(*(s+count)=='\n'||*(s+count)=='\0'){
            break;
        }
        else{
            count++;
        }
    }

    int i = 0;
    int check = 0;
    int check_point = 0;
    while(count>0){
        if(!isdigit(*(s+i))){
            if(*(s+i)!='.'&&check == 0){
                cout << "Wrong inputs! The input should all be numbers!" << endl;
                check = 1;
                break;
            }
            else if(*(s+i) =='.'&&check_point == 1){
                cout << "Wrong inputs! The input should all be numbers!" << endl;
                check = 1;
                break;
            }
            else{
                if(*(s+i)=='.'){
                    check_point = 1;
                }
            }
            
        }
        if(*(s+i) == '.'){
            int j = i;
            j += 3;
            if(*(s+j) != 0){//比兩位小數多
                cout << "Wrong inputs! The input should look like x.y1y2!" << endl;
                check = 1;
                break;
            }
        }
        i++;
        count--;
    }
    if(check == 0){
        set_money(s);
        monetary(money);
    }
}
const void Coins::print(){
    cout << "$" << money << " will be = "<<endl;
    cout << print_cash_q() << " quarters ," << print_cash_d() << " dimes ," << print_cash_n() << " nikkels ," << print_cash_p() << " pennies."<<endl;  
}
inline void Coins::monetary(const double money){//compute+save
    double x = money*100;
    int left = round(x);
    q=0;
    d=0;
    n=0;
    p=0;
    if(left!=0){
        q = left / 25 ;
        left = left % 25; 
    }
    if(left!=0){
        d = left / 10 ;
        left = left % 10;
    }
    if(left!=0){
        n = left / 5 ;
        left= left % 5;
    }
    if(left!=0){
        p = left / 1;
        left = left % 1;
    }
    print();
}

int main(int argc,char *argv[]){

    char *c = argv[1];
    Coins coins(c);
    return 0;
}