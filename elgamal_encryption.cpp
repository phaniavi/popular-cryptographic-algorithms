#include <bits/stdc++.h>
using namespace std;

int power(int a, int b, int MOD){
    int ret = 1;
    a %= MOD;
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
    int x1, y1;
    int g = extended_euclidean(b%a,a,x1,y1);
    x = y1 - (b/a) * x1;
    y = x1;
    return g;
}

int modular_inverse(int a, int n){
    int x, y;
    if(extended_euclidean(a,n,x,y) != 1)
        return 0;
    return (x + n)%n;
}

bool isPrimitive(int x, int p){
    set<int> hash;
    for(int e=1; e<p; ++e)
        hash.insert(power(x,e,p));
    return hash.size() == p-1;
}

void generateKey(int p, int& e1, int& e2, int& d){
    d = 2 + (rand() % (p-3));
    vector<int> primitive;
    for(int i=1; i<p; ++i){
        if(isPrimitive(i,p))
            primitive.push_back(i);
    }
    int idx = rand() % primitive.size();
    e1 = primitive[idx];
    e2 = power(e1,d,p);
}

vector< pair<int,int> > elgamalEncrypt(string plain_text, int k, int e1, int e2, int p){
    vector< pair<int,int> > cipher_text(plain_text.size());
    for(int i=0; i<plain_text.size(); ++i){
        int c1 = power(e1,k,p);
        int c2 = power(e2,k,p);
        int P = (int)plain_text[i];
        c2 = (c2 * 1ll * P)%p;
        cipher_text[i] = {c1,c2};
    }
    return cipher_text;
}

vector<int> elgamalDecrypt(vector< pair<int,int> >& cipher_text, int d, int p){
    vector<int> plain_text(cipher_text.size());
    for(int i=0; i<cipher_text.size(); ++i){
        int c1 = cipher_text[i].first;
        int c2 = cipher_text[i].second;
        c1 = power(c1,d,p);
        c1 = modular_inverse(c1,p);
        plain_text[i] = (c1 * 1ll * c2)%p;
    }
    return plain_text;
}

int main() {
    int p, e1, e2, d, k;
    string plain_text;
    getline(cin,plain_text);
    cin>>p;
    generateKey(p,e1,e2,d);
    k = 1 + rand() % (p-1);
    cout<<"e1 = "<<e1<<" e2 = "<<e2<<" d = "<<d<<" k = "<<k<<endl;
    vector< pair<int,int> > cipher_text = elgamalEncrypt(plain_text,k,e1,e2,p);
    cout<<"c1 = "<<cipher_text[0].first<<endl;
    cout<<"Encrypted text: ";
    for(int i=0; i<cipher_text.size(); ++i)
        cout<<cipher_text[i].second<<" ";
    cout<<endl;
    vector<int> ptext = elgamalDecrypt(cipher_text,d,p);
    cout<<"Decrypted text: ";
    for(int i=0; i<ptext.size(); ++i)
        cout<<char(ptext[i]);
    cout<<endl;
    return 0;
}
/*
INPUT:
Learning is Studying
421
OUTPUT:
e1 = 323 e2 = 298 d = 327 k = 178
c1 = 395
Encrypted text: 22 417 17 33 54 396 54 196 253 396 133 253 301 233 333 317 312 396 54 196 
Decrypted text: Learning is Studying
*/
