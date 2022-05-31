#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;
class Cube {
private :
    double x, y, z;
public:
    Cube(int a,int b,int c){//自己加的constructor
        x = a;
        y = b;
        z = c;
    }
    friend double operator/(Cube &s,Cube &r){//把x,y,z全部加起來 s/r
        double first = s.x + s.y + s.z;
        double second = r.x + r.y + r.z;
        return first/second;
    }
    bool operator==(const Cube &r)const{//比對this,r的cube大小
        double first = (this->x)*(this->y)*(this->z);
        double second = (r.x)*(r.y)*(r.z);
        if(first == second){
            return true;
        }
        return false;
    }
    bool operator!=(const Cube &r)const{
        return !(*this == r);
    }
};