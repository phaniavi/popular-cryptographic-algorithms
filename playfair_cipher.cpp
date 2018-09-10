#include <bits/stdc++.h>
using namespace std;

map<char, pair<int,int> > deconv;
map<pair<int,int>, char> conv;

void construct_matrix(string key){
    map<char, bool> temp;
    int r=0, c=0;
    for(int i=0; i<key.size(); ++i){
        if(isalpha(key[i]) and key[i]!='J' and temp.find(key[i])==temp.end()){
            temp[key[i]] = true;
            deconv[key[i]] = {r,c};
            conv[{r,c}] = key[i];
            ++c;
            if(c == 5)
                ++r, c=0;
        }
    }
    for(char ch='A'; ch<='Z'; ++ch){
        if(ch!='J' and temp.find(ch) == temp.end()){
            temp[ch] = true;
            deconv[ch] = {r,c};
            conv[{r,c}] = ch;
            ++c;
            if(c == 5)
                ++r, c=0;
        }
    }
}

string playfair_cipher(string plain_text){
    int n = 0;
    for(int i=0; i<plain_text.size(); ++i){
        if(isalpha(plain_text[i]))
            plain_text[n++] = plain_text[i];
    }
    plain_text.erase(plain_text.begin()+n, plain_text.end());
    int i = 0;
    while(i<plain_text.size() and i+1<plain_text.size()){
        if(plain_text[i] == plain_text[i+1])
            plain_text.insert(plain_text.begin()+i+1, 'X');
        else
            i += 2;
    }
    if(plain_text.size()%2 == 1)
        plain_text.push_back('X');
    string ret(plain_text.size(), ' ');
    pair<int,int> pos1, pos2;
    for(int i=0,j=1; j<plain_text.size(); i+=2,j+=2){
        pos1 = deconv[plain_text[i]];
        pos2 = deconv[plain_text[j]];
        if(pos1.first == pos2.first){
            ret[i] = conv[{pos1.first,(pos1.second+1)%5}];
            ret[j] = conv[{pos2.first,(pos2.second+1)%5}];
        }
        else if(pos1.second == pos2.second){
            ret[i] = conv[{(pos1.first+1)%5,pos1.second}];
            ret[j] = conv[{(pos2.first+1)%5,pos2.second}];
        }
        else{
            ret[i] = conv[{pos1.first,pos2.second}];
            ret[j] = conv[{pos2.first,pos1.second}];
        }
    }
    return ret;
}

string playfair_decipher(string cipher_text){
    string ret(cipher_text.size(), ' ');
    pair<int,int> pos1, pos2;
    for(int i=0,j=1; j<cipher_text.size(); i+=2,j+=2){
        pos1 = deconv[cipher_text[i]];
        pos2 = deconv[cipher_text[j]];
        if(pos1.first == pos2.first){
            ret[i] = conv[{pos1.first,(pos1.second+4)%5}];
            ret[j] = conv[{pos2.first,(pos2.second+4)%5}];
        }
        else if(pos1.second == pos2.second){
            ret[i] = conv[{(pos1.first+4)%5,pos1.second}];
            ret[j] = conv[{(pos2.first+4)%5,pos2.second}];
        }
        else{
            ret[i] = conv[{pos1.first,pos2.second}];
            ret[j] = conv[{pos2.first,pos1.second}];
        }
    }
    int n = 0;
    for(int i=0; i<ret.size(); ++i){
        if(ret[i] != 'X'){
            ret[n++] = ret[i];
        }
    }
    ret.erase(ret.begin()+n, ret.end());
    return ret;
}

int main() {
    string key, plain_text,  cipher_text;
    getline(cin,key);
    getline(cin,plain_text);
    transform(key.begin(), key.end(), key.begin(), towupper);
    transform(plain_text.begin(), plain_text.end(), plain_text.begin(), towupper);
    construct_matrix(key);
    for(int i=0; i<5; ++i){
        for(int j=0; j<5; ++j){
            cout<<conv[{i,j}]<<" ";
        }
        cout<<endl;
    }
    cout<<(cipher_text = playfair_cipher(plain_text))<<endl;
    cout<<playfair_decipher(cipher_text)<<endl;
    return 0;
}

