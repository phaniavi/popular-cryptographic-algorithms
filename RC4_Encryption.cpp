#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin>>n;
    vector<int> plain_text(n);
    for(int i=0; i<n; ++i)
        cin>>plain_text[i];
    cin>>k;
    vector<int> key(256);
    for(int i=0; i<k; ++i)
        cin>>key[i];
    int s[256];
    for(int i=0; i<256; ++i){
        s[i] = i;
        key[i] = key[i%k];
    }
    int i=0, j=0, t=0;
    for(int i=0; i<256; ++i){
        j = (j + s[i] + key[i])%256;
        swap(s[i],s[j]);
    }
    i = j = 0;
    vector<int> cipher(n), decipher(n);
    for(int p=0; p<n; ++p){
        i = (i + 1)%256;
        j = (j + s[i])%256;
        swap(s[i],s[j]);
        t = s[(s[i]+s[j])%256];
        cipher[p] = plain_text[p] ^ t;
        decipher[p] = cipher[p] ^ t;
    }
    for(int i=0; i<n; ++i)
        cout<<cipher[i]<<" ";
    cout<<endl;
    for(int i=0; i<n; ++i)
        cout<<decipher[i]<<" ";
    cout<<endl;
    return 0;
}

/*
7
16 231 159 110 254 63 223
5
15 202 33 6 8
*/
