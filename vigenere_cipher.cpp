#include <bits/stdc++.h>
using namespace std;

string update_key(string key, string& plain_text){
    string ret;
    int idx = 0;
    for(int i=0; i<plain_text.size(); ++i){
        if(plain_text[i] == ' ')
            ret.push_back(' ');
        else{
            ret.push_back(key[idx]);
            idx = (idx + 1)%key.size();
        }
    }
    return ret;
}

string vigenere_cipher(string& plain_text, string& key){
    key = update_key(key,plain_text);
    string cipher_text(plain_text.size(),' ');
    for(int i=0; i<plain_text.size(); ++i){
        if(plain_text[i] == ' ')
            continue;
        cipher_text[i] = 'A' + (plain_text[i] + key[i])%26;
    }
    return cipher_text;
}

string vigenere_decipher(string& cipher_text, string& key){
    string plain_text(cipher_text.size(), ' ');
    for(int i=0; i<cipher_text.size(); ++i){
        if(cipher_text[i] == ' ')
            continue;
        plain_text[i] = 'A' + (cipher_text[i] - key[i] + 26)%26;
    }
    return plain_text;
}

int main() {
    string key, plain_text, cipher_text;
    getline(cin,plain_text);
    cin>>key;
    transform(plain_text.begin(),plain_text.end(),plain_text.begin(),towupper);
    cout<<(cipher_text = vigenere_cipher(plain_text,key))<<endl;
    cout<<vigenere_decipher(cipher_text,key)<<endl;
    return 0;
}

