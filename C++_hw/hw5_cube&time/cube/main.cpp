#include <iostream>
#include "cube.h"
using namespace std;
int main(){

    Cube a(1,2,3);
    Cube b(1,2,3);
    Cube c(2,3,4);
    double result;
    result = a/b;
    cout << result << endl;
    result = c/a;
    cout << result << endl;
    if(a != b){
        cout << "not the same!" <<endl;
    }
    else{
        cout << "same!" <<endl;
    }
    return 0;
}