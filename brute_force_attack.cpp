#include <bits/stdc++.h>
using namespace std;

string additive_decipher(string c, int shift){
    string ret(c.size(), ' ');
    for(int i=0; i<c.size(); ++i){
        if(c[i] == ' ')
            ret[i] = c[i];
        else
            ret[i] = 'A' + ((((c[i]-'A') - shift))%26 + 26)%26;
    }
    return ret;
}

int main() {
    string c = "NCJAEZRCLASJLYODEPRLYZRCLASJLCPEHZDTOPDZQLNZTY";
    for(int shift=1; shift<26; ++shift)
        cout<<shift<<" "<<additive_decipher(c,shift)<<endl;
    return 0;
}

