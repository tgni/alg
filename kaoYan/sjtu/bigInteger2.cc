#include <iostream>
using namespace std;
#include <vector>
#include<string>
 
class BigNum {
    int a[1000];
    const int MAX = 10;
    const int size = 1000;
public:
    BigNum() { fill(a, a + size, 0); }
    BigNum(string s) {
        fill(a, a + size, 0);
        for (int j = 0, i = s.size() - 1;i >= 0;i--, j++) {
            a[j] = s[i] - '0';
        }
    }
    void operator+(BigNum& B) {
        BigNum C;
        int carry = 0;
        for (int i = 0;i<size;i++) {
            C.a[i] = a[i] + B.a[i] + carry;
            carry = C.a[i] / MAX;
            C.a[i] = C.a[i] % MAX;
        }
        C.print();
    }
    void operator-(BigNum& B) {
        int pos = size - 1;
        while (a[pos] == B.a[pos])pos--;
        if(a[pos] < B.a[pos]){
            for (int i = 0,t;i<size;i++){
                t=a[i];
                a[i]=B.a[i];
                B.a[i]=t;
            }
            cout<<'-';
        }
         
        BigNum C;
        int carry = 0;
        for (int i = 0;i<size;i++) {
 
            C.a[i] = a[i] - B.a[i] - carry;
            if (C.a[i] < 0) {
                carry = 1;
                C.a[i] = C.a[i] + MAX;
            }
 
            else {
                carry = 0;
                C.a[i] = C.a[i] % MAX;
            }
        }
        C.print();
    }
 
    void operator*(BigNum& B) {
        BigNum C;
        for (int i = 0;i<500;i++) {
            int carry = 0;
            for (int j = 0;j<500;j++) {
                C.a[i + j] = a[i] * B.a[j] + C.a[i + j] + carry;
                carry = C.a[i + j] / MAX;
                C.a[i + j] = C.a[i + j] % MAX;
            }
        }
        C.print();
    }
 
    void print() {
        int i = size - 1;
        while (a[i] == 0)i--;
        for (;i >= 0;i--) {
            cout << a[i];
        }
        cout << endl;
    }
 
};
int main() {
    string s1, s2;
    while (cin >> s1 >> s2) {
        BigNum a(s1), b(s2);
        a + b;
        a - b;
        a * b;
    }
}
