#include<iostream>
#include<bitset>

using namespace std; 

/* Bit Manipulation */
#define _isSet(n, i) ((n) & (1u<<(i)))
#define _set(n, i) n = (n | (1u<<(i))) 
#define _reset(n, i) n = (n & (~(1u<<(i))))
#define _flip(n, i) n = (n ^ (1u<<(i)))
#define _rset(n, i, cnt) n = n | (((1u<<(cnt))-1)<<i)
#define _rreset(n, i, cnt) n = n & ~(((1u<<(cnt))-1)<<i)
#define _ffzi(n, i) __builtin_ffs(~(((1u<<i+1)-1) | n))

inline void set(uint8_t *arr, int n, int i) {
    _set(arr[n-(i/8)-1], i%8);
}

inline void reset(uint8_t *arr, int n, int i) {
    _reset(arr[n-(i/8)-1], i%8);
}

void print(uint8_t *arr, int n) {
    for(int i=0; i<n; ++i) {
        cout<<(int)arr[i]<<" ";
    }
    cout<<"\n";
}

/*
    * The array must be non empty
    * k must not exceed the total number of bits in the array 
*/
void sl(uint8_t *arr, int n, int k) {
    int q = k/8;
    int r = k%8;
    /* do q 8 bit shift */
    for(int i=0; i+q<n; ++i)
        arr[i] = arr[i+q];
    for(int i=0; i<q; ++i)
        arr[n-i-1] = 0x00;
    
    /* do r bit shift */
    uint8_t lsb = 0x00;
    for(int i=n-1; i>=0; --i) {
        uint8_t msb = arr[i]>>(8-r);
        arr[i] <<= r;
        arr[i] |= lsb;
        lsb = msb;
    }
}

void csl(uint8_t *arr, int n, int k) {
    int q = (k/8)%n;
    int r = k%8;
    /* circular shift by 8 bits q times */
    while(q--) {
        uint8_t temp = arr[0];
        for(int i=0; i<n-1; ++i)
            arr[i] = arr[i+1];
        arr[n-1] = temp;
    }

    /* circular shift by r bits */
    uint8_t lsb = 0x00;
    for(int i=n-1; i>=0; --i) {
        uint8_t msb = arr[i]>>(8-r);
        arr[i] <<= r;
        arr[i] |= lsb;
        lsb = msb;
    }
    arr[n-1] |= lsb;
}

void sr(uint8_t *arr, int n, int k) {
    int q = k/8;
    int r = k%8;
    /* do q 8 bit shift */
    for(int i=n-1; i-q>=0; --i)
        arr[i] = arr[i-q];
    for(int i=0; i<q; ++i)
        arr[i] = 0x00;
    
    /* do r bit shift */
    uint8_t msb = 0x00;
    for(int i=0; i<n; ++i) {
        uint8_t lsb = arr[i]<<(8-r);
        arr[i] >>= r;
        arr[i] |= msb;
        msb = lsb;
    }
}

void csr(uint8_t *arr, int n, int k) {
    int q = (k/8)%n;
    int r = k%8;
    /* circular shift by 8 bits q times */
    while(q--) {
        uint8_t temp = arr[n-1];
        for(int i=n-1; i>0; --i)
            arr[i] = arr[i-1];
        arr[0] = temp;
    }

    /* circular shift by r bits */
    uint8_t msb = 0x00;
    for(int i=0; i<n; ++i) {
        uint8_t lsb = arr[i]<<(8-r);
        arr[i] >>= r;
        arr[i] |= msb;
        msb = lsb;
    }
    arr[0] |= msb;
}

int main() {
    uint8_t arr[] = {0b11111110u, 0b1111100u, 0b11111110u, 0b11111111u};
    int n = sizeof(arr)/sizeof(arr[0]);
    print(arr, n);
    // reset(arr, n, 31);
    // reset(arr, n, 29);
    // print(arr, n);
    // set(arr, n, 31);
    // set(arr, n, 29);
    // print(arr, n);

    // for(int i=0; i<8; ++i) {
    //     sl(arr, n, 1);
    //     cout<<i<<" : ";
    //     print(arr, n);
    // }

    // sl(arr, n, 32);
    // print(arr, n);

    // sr(arr, n, 32);
    // print(arr, n);

    // csl(arr, n, 32);
    // print(arr, n);

    // csr(arr, n, 32);
    // print(arr, n);
}