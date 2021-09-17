#include<iostream>
#include<bitset>
#include<vector>

using namespace std;

/* Bit Manipulation */
#define _isSet(n, i) ((n) & (1u<<(i)))
#define _set(n, i) n = (n | (1u<<(i))) 
#define _reset(n, i) n = (n & (~(1u<<(i))))
#define _flip(n, i) n = (n ^ (1u<<(i)))
#define _rset(n, i, cnt) n = n | (((1u<<(cnt))-1)<<i)
#define _rreset(n, i, cnt) n = n & ~(((1u<<(cnt))-1)<<i)
#define _ffzi(n, i) __builtin_ffs(~(((1u<<i+1)-1) | n))

// S-box Table
int sb[8][4][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                       0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                       4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                       15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },
                     { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                       3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                       0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                       13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },
                     { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                       13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                       13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                       1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
                     { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                       13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                       10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                       3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
                     { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                       14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                       4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                       11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },
                     { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                       10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                       9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                       4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },
                     { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                       13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                       1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                       6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },
                     { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                       1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                       7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                       2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };

/* intial permutation */
int ip[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
                         60, 52, 44, 36, 28, 20, 12, 4,
                         62, 54, 46, 38, 30, 22, 14, 6,
                         64, 56, 48, 40, 32, 24, 16, 8,
                         57, 49, 41, 33, 25, 17, 9, 1,
                         59, 51, 43, 35, 27, 19, 11, 3,
                         61, 53, 45, 37, 29, 21, 13, 5,
                         63, 55, 47, 39, 31, 23, 15, 7 };

/* key64 permutation 1 - 64 bit to 56 bit */
int kp[56] = { 57, 49, 41, 33, 25, 17, 9,
               1, 58, 50, 42, 34, 26, 18,
               10, 2, 59, 51, 43, 35, 27,
               19, 11, 3, 60, 52, 44, 36,
               63, 55, 47, 39, 31, 23, 15,
               7, 62, 54, 46, 38, 30, 22,
               14, 6, 61, 53, 45, 37, 29,
               21, 13, 5, 28, 20, 12, 4 };

/* key64 permutation 2 - contraction from 56 to 48 */
int kp2[48] = { 14, 17, 11, 24, 1, 5,
                     3, 28, 15, 6, 21, 10,
                     23, 19, 12, 4, 26, 8,
                     16, 7, 27, 20, 13, 2,
                     41, 52, 31, 37, 47, 55,
                     30, 40, 51, 45, 33, 48,
                     44, 49, 39, 56, 34, 53,
                     46, 42, 50, 36, 29, 32 };

/* left shift table */
int shift[16] = { 1, 1, 2, 2,
                        2, 2, 2, 2,
                        1, 2, 2, 2,
                        2, 2, 2, 1 }; 

/* expansion permutation */
int ep[48] = { 32, 1, 2, 3, 4, 5, 4, 5,
               6, 7, 8, 9, 8, 9, 10, 11,
               12, 13, 12, 13, 14, 15, 16, 17,
               16, 17, 18, 19, 20, 21, 20, 21,
               22, 23, 24, 25, 24, 25, 26, 27,
               28, 29, 28, 29, 30, 31, 32, 1 };

/* permutation of expanded right half key64 */
int p[32] = { 16, 7, 20, 21,
              29, 12, 28, 17,
              1, 15, 23, 26,
              5, 18, 31, 10,
              2, 8, 24, 14,
              32, 27, 3, 9,
              19, 13, 30, 6,
              22, 11, 4, 25 };

/* inverse permutation */
int ip_inv[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
                   39, 7, 47, 15, 55, 23, 63, 31,
                   38, 6, 46, 14, 54, 22, 62, 30,
                   37, 5, 45, 13, 53, 21, 61, 29,
                   36, 4, 44, 12, 52, 20, 60, 28,
                   35, 3, 43, 11, 51, 19, 59, 27,
                   34, 2, 42, 10, 50, 18, 58, 26,
                   33, 1, 41, 9, 49, 17, 57, 25 };

template<size_t N>
void rotl(bitset<N> &bs, int n) {
    bitset<N> cipher = bs>>(N-n);
    bs<<=n;
    bs |= cipher;
}

bitset<32> sbox(bitset<48> &inp) {
    bitset<32> out;
    int s1, s2, si;
    int k=0;
    for(int i=0; i<48; i+=6) {
        s1 = 0x00;
        s2 = 0x00;
        si = i/6;
        /* set s1 */
        if(inp.test(i)) _set(s1, 0);
        if(inp.test(i+5)) _set(s2, 1);

        /* set s2 */
        for(int j=1; j<=4; ++j)
            if(inp.test(i+j)) _set(s2, j-1);
        
        for(int j=0; j<4; ++j)
            if(_isSet(sb[si][s1][s2], 3-j)) out.set(k++);
    }

    return out;
}

bitset<64> applyIP(bitset<64> &pt) {
    bitset<64> cipher;
    for(int i=0; i<64; ++i) {
        if(pt.test(ip[i]-1)) cipher.set(i);
        else cipher.reset(i);
    }
    return cipher;
}

bitset<56> applyKP(bitset<64> &key64) {
    bitset<56> key56;
    for(int i=0; i<56; ++i) {
        if(key64.test(kp[i]-1)) key56.set(i);
        else key56.reset(i);
    }
    return key56;
}

bitset<48> applyKP2(bitset<56> &key56) {
    bitset<48> round_key;
    for(int j=0; j<48; ++j) {
        if(key56.test(kp2[j]-1)) round_key.set(j);
        else round_key.reset(j);
    }
    return round_key;
}

bitset<48> applyEP(bitset<32> &rcipher) {
    bitset<48> expn_rcipher;
    for(int j=0; j<48; ++j) {
        if(rcipher.test(ep[j]-1)) expn_rcipher.set(j);
        else expn_rcipher.reset(j);
    }
    return expn_rcipher;
}

bitset<32> applyP(bitset<32> &res) {
    bitset<32> perm;
    for(int j=0; j<32; ++j) {
        if(res.test(p[j]-1)) perm.set(j);
        else perm.reset(j);
    }
    return perm;
}

bitset<64> applyIIP(bitset<64> &cipher) {
    bitset<64> perm;
    for(int i=0; i<64; ++i) {
        if(cipher.test(ip_inv[i]-1)) perm.set(i);
        else perm.reset(i);
    }
    return perm;
}

bitset<64> encrypt(bitset<64> &pt, bitset<64> &key64) {
    /* Initial permutation on plain text */
    bitset<64> cipher = applyIP(pt);

    /* permuted choice 1 on key64 to obtain 56 bit key */
    bitset<56> key56 = applyKP(key64);

    /* divide the cipher and key56 into two parts */
    bitset<32> lcipher, rcipher;
    bitset<28> lkey, rkey;
    for(int i=0; i<32; ++i) {
        lcipher[i] = cipher[i];
        rcipher[i] = cipher[i+32];
    }
    for(int i=0; i<28; ++i) {
        lkey[i] = pt[i];
        rkey[i] = pt[i+28];
    }

    /* Start the rounds */
    /* Create bitset for round key64 of 48 bits */
    bitset<48> round_key;
    /* Create array for expanded rcipher of pt of 48 bits */
    bitset<48> expn_rcipher;
    /* intermediate res */
    bitset<32> res;
    for(int i=0; i<16; ++i) {
        /* circular left shift keys - lkey */
        rotl(lkey, shift[i]);
        rotl(rkey, shift[i]);
        for(int j=0; j<28; ++j)
            key56[i] = lkey[i];
        for(int j=28; j<56; ++j)
            key56[j] = rkey[j-28];

        /* Permuted choice 2 on key56 to get round subkey (56 to 48 bits) */
        round_key = applyKP2(key56);

        /* Expansion of rcipher (32 to 48 bits) */
        expn_rcipher = applyEP(rcipher);

        /* xor with computed round key64 (48 bits)*/
        expn_rcipher ^= round_key;

        /* sbox (48 to 32 bits)*/
        res = sbox(expn_rcipher);

        /* permutation of res */
        res = applyP(res);

        /* XOR with L */
        res ^= lcipher;

        /* lcipher = prev rcipher value, rcipher = res */
        lcipher = rcipher;
        rcipher = res;
    }
    /* combine lcipher and rcipher with their position interchanged*/
    for(int i=0; i<32; ++i)
        cipher[i] = rcipher[i];
    for(int i=32; i<64; ++i)
        cipher[i] = lcipher[i-32];

    /* apply inverse permutation on pt */
    return applyIIP(cipher);
}

string bit_seq(string str) {
    string seq = "";
    for(int i=0; i<str.size(); ++i) {
        for(int j=7; j>=0; --j)
            seq += _isSet(str[i], j)?"1":"0";
    }
    return seq;
}

vector<bitset<64>> string_to_bits(string plain_text) {
    vector<bitset<64>> vec;
    for(int i=0; i<plain_text.size(); i+=8) {
        string sub = plain_text.substr(i, 8);
        if(sub.length() < 8) sub.append(8 - sub.length(), ' ');
        vec.push_back(bitset<64>(bit_seq(sub)));
    }
    return vec;
}

string bits_to_string(vector<bitset<64>> &vec) {
    string out = "";
    for(auto &bs : vec) {
        string st = "";
        for(int i=7; i>=0; --i) {
            char c = 0x00;
            for(int j=0; j<8; ++j) {
                if(bs.test(8*i+j)) _set(c, j);
            }
            st += c;
        }
        out += st;
    }
    return out;
}

int main() {
    bitset<64> key(bit_seq("ABCDEF12"));
    vector<bitset<64>> vec = string_to_bits("ABCDEFGH12345678");
    for(auto &bs : vec)
        cout<<bs<<" ";
    cout<<"\n";

    vector<bitset<64>> vec_enc;
    for(auto &bs : vec)
        vec_enc.push_back(encrypt(bs, key));
    
    cout<<bits_to_string(vec_enc)<<"\n";
}