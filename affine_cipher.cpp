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

string affine_cipher(string p, int a, int b, int mod){
    string ret(p.size(), ' ');
    for(int i=0; i<p.size(); ++i){
        if(p[i] == ' ')
            ret[i] = p[i];
        else
            ret[i] = 'a' + (((p[i]-'a')*a + b)%mod + mod)%mod;
    }
    return ret;
}

string affine_decipher(string c, int a, int b, int mod){
    string ret(c.size(), ' ');
    int a_inv = modular_inverse(a,mod);
    for(int i=0; i<c.size(); ++i){
        if(c[i] == ' ')
            ret[i] = c[i];
        else
            ret[i] = 'a' + ((((c[i]-'a') - b)*a_inv)%mod + mod)%mod;
    }
    return ret;
}

int main() {
    string p, c;
    int a, b, mod;
    getline(cin,p);
    cin>>a>>b>>mod;
    cout<<(c = affine_cipher(p,a,b,mod))<<endl;
    cout<<affine_decipher(c,a,b,mod)<<endl;
    return 0;
}

