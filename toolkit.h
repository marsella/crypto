/*
 * toolkit.h
 *
 * last modified 6 December 2012
 * by marsella 
 *
 */


#include <gmpxx.h>

// d = gcd(a, b)
// d = Xa + Yb
struct GCDstruct {
    mpz_class d, X, Y;
};

/* gcd with extended euclidean algorithm */
GCDstruct eGCD( mpz_class a, mpz_class b );

/* gcd w/ dijkstra's algorithm */
mpz_class dGCD( mpz_class a, mpz_class b );

/* x = [a^-1 mod N] */
mpz_class modInv( mpz_class N, mpz_class a );

/* x = [a^b mod N] */
mpz_class modExp( mpz_class N, mpz_class a, mpz_class b );

/* naive primality testing */
int isPrime( mpz_class N, int t );




