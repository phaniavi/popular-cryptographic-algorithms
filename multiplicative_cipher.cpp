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

string multiplicative_cipher(string p, int mul){
    string ret(p.size(), ' ');
    for(int i=0; i<p.size(); ++i){
        if(p[i] == ' ')
            ret[i] = p[i];
        else
            ret[i] = 'a' + (((p[i]-'a')*mul)%26 + 26)%26;
    }
    return ret;
}

string multiplicative_decipher(string c, int mul){
    string ret(c.size(), ' ');
    int a_inv = modular_inverse(mul,26);
    for(int i=0; i<c.size(); ++i){
        if(c[i] == ' ')
            ret[i] = c[i];
        else
            ret[i] = 'a' + (((c[i]-'a')*a_inv)%26 + 26)%26;
    }
    return ret;
}

int main() {
    string p, c;
    int mul;
    getline(cin,p);
    cin>>mul;
    cout<<(c = multiplicative_cipher(p,mul))<<endl;
    cout<<multiplicative_decipher(c,mul)<<endl;
    return 0;
}

