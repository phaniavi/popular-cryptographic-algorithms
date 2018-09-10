#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
const double e = 2.718281828459;
const double f = 1.61803398875;
ll w, r, b, u, t, c, p, q, MOD;

ll odd(double val){
    ll fl = val;
    if(fl & 1)
        return fl;
    return fl+1;
}

ll left_circular_Shift(ll num, ll shift){
    shift %= w;
    return ((1ull<<w)-1) & ((num << shift) | (num >> (w-shift)));
}

ll right_circular_Shift(ll num, ll shift){
    shift %= w;
    return ((1ull<<w)-1) & ((num >> shift) | (num << (w-shift)));
}

int main() {
    cin>>w>>r>>b;
    MOD = 1ull << w;
    t = 2*r+2;
    u = w / 8;
    c = ceil(b*1.0/u);
    p = odd((e-2)*(1ll<<w));
    q = odd((f-1)*(1ll<<w));
    ll plain_text, cipher_text;
    cin>>plain_text;
    vector<ll> key(b), L(c), S(t);
    for(int i=0; i<b; ++i)
        cin>>key[i];
    for(int i=b-1; i>=0; --i)
        L[i/u] = (L[i/u] << 8ull) + key[i];
    S[0] = p;
    for(int i=1; i<t; ++i)
        S[i] = (S[i-1] + q)%MOD;
    ll i=0, j=0;
    ll A=0, B=0;
    for(int z=0; z<3*max(t,c); ++z){
        A = S[i] = left_circular_Shift(((S[i] + A)%MOD + B)%MOD, 3);
        B = L[j] = left_circular_Shift(((L[j] + A)%MOD + B)%MOD, (A + B));
        i = (i + 1)%t;
        j = (j + 1)%c;
    }
    A = plain_text >> w;
    B = ((1ull<<w)-1) & plain_text;
    A = (A + S[0])%MOD;
    B = (B + S[1])%MOD;
    for(int z=1; z<=r; ++z){
        A = (left_circular_Shift((A ^ B), B) + S[2*z])%MOD;
        B = (left_circular_Shift((A ^ B), A) + S[2*z+1])%MOD;
    }
    cipher_text = (A << w) | B;
    cout<<cipher_text<<endl;
    for(int z=r; z>0; --z){
        B = right_circular_Shift(B - S[2*z+1], A) ^ A;
        A = right_circular_Shift(A - S[2*z], B) ^ B;
    }
    B = B - S[1];
    A = A - S[0];
    plain_text = (A << w) | B;
    cout<<plain_text<<endl;
    return 0;
}

