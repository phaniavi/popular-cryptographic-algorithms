#include <bits/stdc++.h>
using namespace std;

int fast_exponentiation(int a, int b, int MOD){
    int ret = 1;
    a = a % MOD;
    while(b != 0){
        if(b & 1)
            ret = (ret * 1ll * a)%MOD;
        a = (a * 1ll * a)%MOD;
        b >>= 1;
    }
    return ret;
}

int extended_euclidean(int a, int b, int& x, int& y){
    if(a == 0){
        x = 0;
        y = 1;
        return b;
    }
    int xx, yy;
    int g = extended_euclidean(b%a, a, xx, yy);
    y = xx;
    x = yy - (b*1ll/a) * xx;
    return g;
}

int modular_inverse(int a, int MOD){
    int x, y;
    if(extended_euclidean(a,MOD,x,y) != 1)
        return 0;
    return (x + MOD)%MOD;
}

int phi(int n){
    int ret = n;
    if(n%2 == 0){
        ret -= ret / 2ll;
        while(n%2 == 0)
            n /= 2;
    }
    int factor = 3;
    int max_factor = sqrt(n);
    while(n!=1 and factor<=max_factor){
        if(n%factor == 0){
            ret -= ret / factor;
            while(n%factor == 0)
                n /= factor;
            max_factor = sqrt(n);
        }
        factor += 2;
    }
    if(n != 1)
        ret -= ret / n;
    return ret;
}

int findPrivateKey(int e, int p, int q){
    int n = p * q;
    int phi_n = (p-1) * (q-1);
    int d = modular_inverse(e,phi_n);
    return d;
}

vector<int> RSAEncrypt(vector<int> plain_text, int e, int p, int q){
    int n = p * q;
    vector<int> cipher_text(plain_text.size());
    for(int i=0; i<plain_text.size(); ++i)
        cipher_text[i] = fast_exponentiation(plain_text[i],e,n);
    return cipher_text;
}

vector<int> RSADecrypt(vector<int> cipher_text, int d, int p, int q){
    int n = p * q;
    vector<int> plain_text(cipher_text.size());
    for(int i=0; i<cipher_text.size(); ++i)
        plain_text[i] = fast_exponentiation(cipher_text[i],d,n);
    return plain_text;
}

int main() {
    int p, q, e, d;
    //cout<<"Enter values of p, q, e: ";
    cin>>p>>q>>e;
    d = findPrivateKey(e,p,q);
    cout<<"Private Key = "<<d<<endl;
    string str;
    cin>>str;
    vector<int> plain_text;
    for(int i=0; i<str.size(); ++i)
        plain_text.push_back((int)str[i]);
    vector<int> cipher_text = RSAEncrypt(plain_text,e,p,q);
    for(int i=0; i<cipher_text.size(); ++i)
        cout<<cipher_text[i]<<" ";
    cout<<endl;
    plain_text = RSADecrypt(cipher_text,d,p,q);
    for(int i=0; i<plain_text.size(); ++i)
        cout<<plain_text[i]<<" ";
    cout<<endl;
    return 0;
}

/*
INPUT:
73 227 29
IIT
OUTPUT:
Private Key = 10661
12556 12556 4922 
73 73 84 
*/
