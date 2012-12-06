/*
 * toolkit.cpp 
 *
 * to compile: ./compile
 * to run:     ./run
 *
 * last modified 6 dec 2012 
 * by marsella
 */

#include "toolkit.h"
#include <iostream>
using namespace std;

gmp_randstate_t rstate;

gmp_randclass r1(gmp_randinit_default);

// gcd with extended euclidean algorithm
GCDstruct eGCD( mpz_class a, mpz_class b ) {
    if(a%b == 0) {
        GCDstruct s = { b, 0, 1 };
        return s;
    }
    else {
        mpz_class q = a/b;
        mpz_class r = a%b;
        GCDstruct tmp = eGCD(b, r);
        GCDstruct s = { tmp.d, tmp.Y, tmp.X-tmp.Y*q };
        return s;
    }
} 

/* gcd w/ dijkstra's algorithm */
mpz_class dGCD( mpz_class a, mpz_class b ) {
    if(a > b)
        return dGCD(a-b, b);
    else if(a < b)
        return dGCD(a, b-a);
    else
        return a;
}

// x = [a^-1 mod N]
mpz_class modInv( mpz_class N, mpz_class a ) {
    GCDstruct aN = eGCD(a, N);
    if(aN.d == 1) {
        mpz_class ret = aN.X % N;
        return (ret < 0)? ret+N : ret;
    }
    else {
        cout << a << "is not invertible mod " << N << endl;
        return -1;
    }
}

// x = [a^b mod N]
mpz_class modExp( mpz_class N, mpz_class a, mpz_class b ) {
    if(b==1)
        return a;
    else{
        if(b%2 == 0) {
            mpz_class t = modExp(N, a, b/2);
            return (t*t) % N;
        }
        else {
            mpz_class t = modExp(N, a, (b-1)/2);
            return (a*t*t) % N;
        }
    }
}

// naive primality testing
int isPrime( mpz_class N, int t ) {
    for(int i=0; i<t; i++) {
        /* random element generator: generates a st 0<a<N */
        mpz_class a; 
        do {
          a = r1.get_z_bits(81) % N;
        } while (a==0);
        cout << "witness: " << a << endl;
        if(eGCD(a, N).d != 1) {
            return 0;
        }
        if(modExp(N, a, N-1) != 1) {
            return 0;
        }
    }
    return 1;
}

