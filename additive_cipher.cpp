#include <bits/stdc++.h>
using namespace std;

string additive_cipher(string p, int shift){
    string ret(p.size(), ' ');
    for(int i=0; i<p.size(); ++i){
        if(p[i] == ' ')
            ret[i] = p[i];
        else
            ret[i] = 'a' + (((p[i]-'a') + shift)%26 + 26)%26;
    }
    return ret;
}

string additive_decipher(string c, int shift){
    string ret(c.size(), ' ');
    for(int i=0; i<c.size(); ++i){
        if(c[i] == ' ')
            ret[i] = c[i];
        else
            ret[i] = 'a' + ((((c[i]-'a') - shift))%26 + 26)%26;
    }
    return ret;
}

int main() {
    string p, c;
    int shift;
    getline(cin,p);
    cin>>shift;
    cout<<(c = additive_cipher(p,shift))<<endl;
    cout<<additive_decipher(c,shift)<<endl;
    return 0;
}

