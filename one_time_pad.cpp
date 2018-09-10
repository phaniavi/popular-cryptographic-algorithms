#include <bits/stdc++.h>
using namespace std;

int main(){
    string plain_text = "sendmoremoney";
    string cipher_text(plain_text.size(),' ');
    string output = "cashnotneeded";
    int key_stream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    for(int i=0; i<plain_text.size(); ++i)
        cipher_text[i] = 'a' + ((plain_text[i]-'a') + key_stream[i])%26;
    cout<<cipher_text<<endl;
    for(int i=0; i<output.size(); ++i)
        cout<<((cipher_text[i] - output[i] + 26)%26)<<" ";
    cout<<endl;
    return 0;
}
