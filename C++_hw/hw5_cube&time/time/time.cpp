using namespace std;
#include "time.h"
//default 0
Time::Time(){
    days = 0;
    hours = 0;
    minutes = 0;
    seconds = 0;
}
Time::Time(int s){
    if(s <= 0){
        days = 0;
        hours = 0;
        minutes = 0;
        seconds = 0;
    }
    else{
        int d;//days
        int h;//hours
        int m;//minutes
        //有超過的部分要自己補成正確的格式
        m = s/60;
        s = s%60;
        h = m/60;
        m = m%60;
        d = h/24;
        h = h%24;
        days = d;
        hours = h;
        minutes = m;
        seconds = s;
    }
}
Time::Time(int d,int h,int m,int s){
    if(d<0||h<0||m<0||s<0){
        days = 0;
        hours = 0;
        minutes = 0;
        seconds = 0;
    }
    else{
        days = d;
        hours = h;
        minutes = m;
        seconds = s;
        if(seconds>=60){
            minutes+=seconds/60;
            seconds= seconds%60;
        }
        if(minutes>=60){
            hours+=minutes/60;
            minutes = minutes%60;
        }
        if(hours>=24){
            days+=hours/24;
            hours = hours%24;
        }
    }
}
ostream& operator<<(ostream& os, const Time &r){
        os<< r.days << "~";
        if((r.hours/10)<1){
            os<<"0";
        }
        os<<r.hours<<":";
        if((r.minutes/10)<1){//檢查有沒有超過兩位數
            os<<"0";
        }
        os<<r.minutes<<":";
        if((r.seconds/10)<1){
            os<<"0";
        }
        os<<r.seconds;
        return os;
    }
istream& operator>> (istream& is,Time &r){
        //is>>
        char input[100];
        is >> input;
        char temp[100]={0};
        int j = 0;
        int track = 0;
        for(int i=0;i<strlen(input);i++){
            //任一有負
            
            if(input[i] == '-'){//有負直接全部0
                r.days =0;
                r.hours =0;
                r.minutes=0;
                r.seconds=0;
                break;
            }
            if(input[i] == '~'){//找到~就把temp的值轉成數字
                r.days = atoi(temp);
                memset(temp, 0, sizeof(temp));
                j=0;
                track = 1;
            }
            else if(input[i] == ':'){//找到:就把temp轉成數字
                if(track == 1){//小時的
                    r.hours = atoi(temp);
                    track +=1;
                    memset(temp, 0, sizeof(temp));
                }
                else if(track == 2){//分鐘的
                    r.minutes = atoi(temp);
                    track +=1;
                    memset(temp, 0, sizeof(temp));
                }
                j=0;
            }
            else{
                temp[j] = input[i];
                j++;
            }
            if(track == 3 && i== strlen(input)-1){//代表數字進入尾聲
                r.seconds = atoi(temp);
            }
        }
        if(r.seconds>=60){
            r.minutes+=r.seconds/60;
            r.seconds = r.seconds%60;
        }
        if(r.minutes>=60){
            r.hours+=r.minutes/60;
            r.minutes = r.minutes%60;
        }
        if(r.hours>=24){
            r.days+=r.hours/24;
            r.hours = r.hours%24;
        }
        
        return is;
}
Time Time::operator+(const Time &r)const{
    Time result;
    result.days = (this->days)+r.days;
    result.hours = (this->hours)+r.hours;
    result.minutes = (this->minutes)+r.minutes;
    result.seconds = (this->seconds)+r.seconds;
    if(result.seconds>=60){
        result.minutes+=result.seconds/60;
        result.seconds = result.seconds%60;
    }
    if(result.minutes>=60){
        result.hours+=result.minutes/60;
        result.minutes = result.minutes%60;
    }
    if(result.hours>=24){
        result.days+=result.hours/24;
        result.hours = result.hours%24;
    }
    return result;
}
Time Time::operator-(const Time &r)const{
    Time result;
    result.days = (this->days)-r.days;
    result.hours = (this->hours)-r.hours;
    result.minutes = (this->minutes)-r.minutes;
    result.seconds = (this->seconds)-r.seconds;
    if(result.seconds<0){
        result.minutes -=1;
        result.seconds+=60;
    }
    if(result.minutes<0){
        result.hours -=1;
        result.minutes+=60;
    }
    if(result.hours<0){
        result.days -=1;
        result.hours+=24;
    }
    if(result.days<0||result.hours<0||result.minutes<0||result.seconds<0){
        result.days = 0;
        result.hours = 0;
        result.minutes = 0;
        result.seconds = 0;
    }
    return result;
}
bool Time::operator==(const Time &r)const{
        if((this->days)==r.days){
            if((this->hours)==r.hours){
                if((this->minutes)==r.minutes){
                    if((this->seconds)==r.seconds){
                        return true;
                    }
                }
            }
        }
        return false;
    }
bool Time::operator!=(const Time &r)const{
    return !(*this == r);
}
bool Time::operator<(const Time &r)const{
    if((this->days)<r.days){
        return true;
    }
    else if((this->days)==r.days){
        if((this->hours)<r.hours){
            return true;
        }
        else if((this->hours)==r.hours){
            if((this->minutes)<r.minutes){
                return true;
            }
            else if((this->minutes)==r.minutes){
                if((this->seconds)<r.seconds){
                    return true;
                }
            }
        }
    }
    return false;
}
bool Time::operator>(const Time &r)const{
    if((this->days)>r.days){
        return true;
    }
    else if((this->days)==r.days){
        if((this->hours)>r.hours){
            return true;
        }
        else if((this->hours)==r.hours){
            if((this->minutes)>r.minutes){
                return true;
            }
            else if((this->minutes)==r.minutes){
                if((this->seconds)>r.seconds){
                    return true;
                }
            }
        }
    }
    return false;
}
bool Time::operator<=(const Time &r)const{
    if((this->days)<r.days){
        return true;
    }
    else if((this->days)==r.days){
        if((this->hours)<r.hours){
            return true;
        }
        else if((this->hours)==r.hours){
            if((this->minutes)<r.minutes){
                return true;
            }
            else if((this->minutes)==r.minutes){
                if((this->seconds)<=r.seconds){
                    return true;
                }
            }
        }
    }
    return false;
}
bool Time::operator>=(const Time &r)const{
    if((this->days)>r.days){
        return true;
    }
    else if((this->days)==r.days){
        if((this->hours)>r.hours){
            return true;
        }
        else if((this->hours)==r.hours){
            if((this->minutes)>r.minutes){
                return true;
            }
            else if((this->minutes)==r.minutes){
                if((this->seconds)>=r.seconds){
                    return true;
                }
            }
        }
    }
    return false;
}
Time operator-(const int &left,const Time &r){
    Time result(left);
    return result - r;
}
Time operator-(const Time &left,const int &r){
    Time result(r);
    return left - result;
}
Time operator+(const int &left,const Time &r){
    Time result(left);
    return result + r;
}
Time operator+(const Time &left,const int &r){
    Time result(r);
    return left + result;
}
Time& Time::operator++(){//++obj;
    this->seconds +=1;
    if((this->seconds)>=60){
        this->minutes+=(this->seconds/60);
        this->seconds = (this->seconds%60);
    }
    if((this->minutes)>=60){
        this->hours+=(this->minutes/60);
        this->minutes = (this->minutes%60);
    }
    if((this->hours)>=24){
        this->days+=(this->hours/24);
        this->hours = (this->hours)%24;
    }
    return *this;
}
const Time Time::operator++(int x){//obj++;
    Time oldValue = *this; // fetch
    ++(*this); // increment
    return oldValue;
}
Time& Time::operator--(){//--obj;
    this->seconds -=1;
    if((this->seconds)<0){
        this->minutes -=1;
        this->seconds+=60;
    }
    if((this->minutes)<0){
       this->hours-=1;
       this->minutes+=60;
    }
    if((this->hours)<0){
        this->days-=1;
        this->hours+=24;
    }
    if(this->days<0||this->hours<0||this->minutes<0||this->seconds<0){
        this->days = 0;
        this->hours = 0;
        this->minutes = 0;
        this ->seconds = 0;
    }
    return *this;
}
const Time Time::operator--(int x){//obj--;
    Time oldValue = *this; // fetch
    --(*this); // increment
    return oldValue;
}






