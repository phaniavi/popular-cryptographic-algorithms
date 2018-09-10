#include <bits/stdc++.h>
using namespace std;

vector<int> permute(vector<int>& key, vector<int>& permutation_key){
    vector<int> ret(permutation_key.size());
    for(int i=0; i<permutation_key.size(); ++i)
        ret[i] = key[permutation_key[i] - 1];
    return ret;
}

vector<int> circular_shift(vector<int>& permutation_key, int shift){
    int n = permutation_key.size();
    int lim = n / 2;
    vector<int> ret(n);
    for(int i=0; i<lim; ++i)
        ret[(i-shift+lim)%lim] = permutation_key[i];
    for(int i=0; i<lim; ++i)
        ret[lim + (i-shift+lim)%lim] = permutation_key[lim + i];
    return ret;
}

vector<int> expand(vector<int>& plain_text){
    vector<int> expansion_key = {4, 1, 2, 3, 2, 3, 4, 1};
    vector<int> ret(expansion_key.size());
    int lim = plain_text.size() / 2;
    for(int i=0; i<expansion_key.size(); ++i)
        ret[i] = plain_text[lim + expansion_key[i] - 1];
    return ret;
}

vector<int> apply_xor(vector<int>& lhs, vector<int>& rhs, int lim){
    vector<int> ret(lhs);
    for(int i=0; i<lim; ++i)
        ret[i] = lhs[i] ^ rhs[i];
    return ret;
}

void apply_swap(vector<int>& text){
    int n = text.size();
    int lim = n / 2;
    for(int i=0; i<lim; ++i)
        swap(text[i],text[lim+i]);
}

int value(int bit1, int bit2){
    int ret = 0;
    if(bit2)
        ret |= 1;
    if(bit1)
        ret |= 2;
    return ret;
}

vector<int> f_output(vector<int>& key, vector<vector<int> >& s0, vector<vector<int> >& s1){
    vector<int> ret;
    int r = value(key[0],key[3]);
    int c = value(key[1],key[2]);
    int val = s0[r][c];
    ret.push_back((int)(val>>1 & 1));
    ret.push_back((int)(val & 1));
    r = value(key[4],key[7]);
    c = value(key[5],key[6]);
    val = s1[r][c];
    ret.push_back((int)(val>>1 & 1));
    ret.push_back((int)(val & 1));
    return ret;
}

void fkey(vector<int>& plain_text, vector<int>& key){
    vector<vector<int> > s0 = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}};
    vector<vector<int> > s1 = {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}};
    vector<int> p4 = {2, 4, 3, 1};
    int n = plain_text.size();
    vector<int> temp = expand(plain_text);
    vector<int> fkey = apply_xor(temp,key,n);
    vector<int> f = f_output(fkey,s0,s1);
    f = permute(f,p4);
    plain_text = apply_xor(plain_text,f,n/2);
}

int main() {
    int n = 8;
    int k = 10;
    vector<int> plain_text(n);
    vector<int> cipher_text;
    vector<int> decipher_text;
    vector<int> cipher_key(k);
    for(int i=0; i<n; ++i)
        cin>>plain_text[i];
    for(int i=0; i<k; ++i)
        cin>>cipher_key[i];
    // Initial Permutation
    vector<int> ip = {2, 6, 3, 1, 4, 8, 5, 7};
    plain_text = permute(plain_text,ip);

    // Key Generation
    vector<int> p10 = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    vector<int> p8 = {6, 3, 7, 4, 8, 5, 10, 9};
    vector<int> key_1, key_2;
    key_1 = permute(cipher_key,p10);
    key_1 = circular_shift(key_1,1);
    key_2 = circular_shift(key_1,2);
    key_1 = permute(key_1,p8);
    key_2 = permute(key_2,p8);
    cout<<"KEY1 = ";
    for(int i=0; i<key_1.size(); ++i)
        cout<<key_1[i]<<" ";
    cout<<endl;
    cout<<"KEY2 = ";
    for(int i=0; i<key_1.size(); ++i)
        cout<<key_2[i]<<" ";
    cout<<endl;

    // Apply f_k1
    fkey(plain_text,key_1);

    // Swap left and right parts
    apply_swap(plain_text);

    // Apply f_k2
    fkey(plain_text,key_2);
    
    // Final Permutation
    vector<int> fip = {4, 1, 3, 5, 7, 2, 8, 6};
    plain_text = permute(plain_text,fip);

    // Print final output
    for(int i=0; i<plain_text.size(); ++i)
        cout<<plain_text[i]<<" ";
    cout<<endl;

    plain_text = permute(plain_text,ip);
    fkey(plain_text,key_2);
    apply_swap(plain_text);
    fkey(plain_text,key_1);
    plain_text = permute(plain_text,fip);
    for(int i=0; i<plain_text.size(); ++i)
        cout<<plain_text[i]<<" ";
    cout<<endl;
    return 0;
}

