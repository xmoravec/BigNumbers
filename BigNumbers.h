#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include <math.h>

typedef struct {
    //0 means + and 1 means -
    int sign;
    int size;
    int *tab;
} bignum;

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
bool bignum_isbigger(bignum *a, bignum *b);
bignum *bignum_remainder(bignum *a, bignum *b);
bignum *bignum_addmod(bignum *a, bignum *b, bignum*n);
bignum *bignum_multmod(bignum *a, bignum *b, bignum*n);
bignum *int_tobignum(int num);
bignum *longlong_tobignum(long long num);
int bignum_toint(bignum *num);
bignum *bignum_expmod(bignum *a, bignum *b, bignum*n);
bool fermat(bignum *a, int t);
bignum *bignum_expmod_efficient(bignum *a, bignum *b, bignum *n);

bignum *genrandom(int length);
bignum *genrandom_prime(int length);

void keygen(bignum *n, bignum *e, bignum *d, int length);
bignum* RSAencrypt(bignum *m, bignum *e, bignum *n);
bignum* RSAdecrypt(bignum *c, bignum *d, bignum *n);