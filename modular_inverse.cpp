#include <bits/stdc++.h>
using namespace std;

int extended_euclid(int a, int b, int& x, int& y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    int g = extended_euclid(b, a%b, x, y);
    int temp = y;
    y = x - (a/b)*y;
    x = temp;
    return g;
}

int modular_inverse(int a, int mod){
    int x, y;
    int g = extended_euclid(a, mod, x, y);
    if(g != 1)
        return 0;
    return (x + mod)%mod;
}

int main(){
    int a, mod;
    cin>>a>>mod;
    cout<<modular_inverse(a,mod)<<endl;
    return 0;
}
