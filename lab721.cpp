#include <iostream>
#include <exception>

using namespace std;

float internalDivide(float arg1, float arg2) {
    if (arg2 == 0)
        throw "cant divide by 0";
    return arg1 / arg2;
}

float divide(float arg1, float arg2) {
    float res;
    try {
        res = internalDivide(arg1, arg2);
    }
    catch (...){
        res = -1;
    }
    return res;
}
class DivException : public std::exception {
private:
    char* mess;
public:
    char* get_mess() {
        return this->mess;
    }
    DivException(char* mess) {
        this->mess = mess;
    }
};


int main(void) {
    float r, a, b;
    cout << "Enter two numbers separated by 'enter' key\n";
    while(cin >> a) {
        cin >> b;
        if(divide(a,b) != -1) {
            cout << divide(a, b) << endl;
        } else {
            cout << "Invalid input. You can't divide by zero." << endl;
        }
    }

    return 0;
}
