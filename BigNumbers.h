#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    //0 means + and 1 means -
    int sign;
    int size;
    int *tab;
} bignum;

/* DONE */
bignum *bignum_new();
void bignum_free(bignum *a);
void bignum_enlarge_double(bignum *a);
void bignum_enlarge(bignum *a, int new_size);
char *bignum_tostring(bignum *b);
bignum *bignum_fromstring(char *str);
bignum *bignum_add(bignum *a, bignum *b);
bignum* bignum_multiply(bignum *a, bignum *b);
int int2bin(int b, uint8_t bits[32]);
int power_mod(int a, int b, int n);
bignum *bignum_sub(bignum *a, bignum *b);

/* TODO */
bignum *bignum_remainder(bignum *a, bignum *b);
bignum *addmod(bignum *a, bignum *b, bignum*n);
bignum *multmod(bignum *a, bignum *b, bignum*n);
bignum *expmod(bignum *a, bignum *b, bignum*n);
int fermat(bignum a, int t);
bignum *genrandom(int length);
bignum *genrandom_prime(int length);

/*TODO RSA*/
void keygen(bignum *n, bignum *e, bignum *d, int length);
bignum* RSAencrypt(bignum *m, bignum *e, bignum *n);
bignum* RSAdecrypt(bignum *c, bignum *d, bignum *n);

/* Optional, would be nice to do for convenience*/
bignum *int_tobignum(int num);
bignum *longlong_tobignum(long long num);