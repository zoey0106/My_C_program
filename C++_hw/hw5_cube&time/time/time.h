#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string.h>
using namespace std;
class Time {
private :
    int days;
    int hours;
    int minutes;
    int seconds;
public:
    //constructor
    Time();
    Time(int s);
    Time(int d,int h,int m,int s);
    //os
    friend ostream& operator<<(ostream& os, const Time &r);
    friend istream& operator>> (istream& is,Time &r);
    //compare
    Time operator+(const Time &r)const;
    Time operator-(const Time &r)const;
    bool operator==(const Time &r)const;
    bool operator!=(const Time &r)const;
    bool operator<(const Time &r)const;
    bool operator>(const Time &r)const;
    bool operator<=(const Time &r)const;
    bool operator>=(const Time &r)const;
    //-
    friend Time operator-(const int &left,const Time &r);
    friend Time operator-(const Time &left,const int &r);
    //+
    friend Time operator+(const int &left,const Time &r);
    friend Time operator+(const Time &left,const int &r);
    //++
    Time& operator++();//++obj;
    const Time operator++(int x);//obj++;
    //--
    Time& operator--();//--obj;
    const Time operator--(int x);//obj--;
};