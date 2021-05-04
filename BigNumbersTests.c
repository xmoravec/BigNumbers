#include "BigNumbersTests.h"

bignum *bignum_fibonnaci(int n) {
    bignum* a = bignum_fromstring("0");
    bignum* b = bignum_fromstring("1");
    bignum* fib = bignum_fromstring("0");
    for (int i = 0; i < n ; i++) {
        fib = bignum_add(a, b);
        a = b;
        b = fib;
    }
    return fib;
}

bignum *bignum_factorial(int n) {
    if (n == 0) {
        return bignum_fromstring("0");
    }
    bignum *result = bignum_fromstring("1");
    for (int i = 1; i <= n; i++) {
        char snum[10];
        sprintf(snum, "%d", i);
        result = bignum_multiply(result, bignum_fromstring(snum));
    }
    return result;
}

/* Currently the free of the allocated memory doesnt work properly due
   to invalid tab pointer bcs of pointer arithmetics/shift in bignum_add/multiply. */

void test_addition() {
    bignum *a = bignum_fromstring("4294966296");
    bignum *b = bignum_fromstring("4294966296");
    bignum *c = bignum_add(a, b);
    printf("Testing bignum addition with a: %s and b: %s\nresult: %s\n", bignum_tostring(a), bignum_tostring(b), bignum_tostring(c));
    printf("Testing bignum_fibonnaci on n: %d\nresult: %s\n", 100, bignum_tostring(bignum_fibonnaci(100)));
    printf("The 101th value of fibonnacci is: %s\n", bignum_tostring(bignum_fibonnaci(101)));
    
    /*bignum_free(a);
    bignum_free(b);
    bignum_free(c);*/
}

void test_multiplication() {
    bignum *a = bignum_fromstring("4291496629");
    bignum *b = bignum_fromstring("15734966296");
    bignum *c = bignum_multiply(a, b);
    printf("Testing bignum multiply with a: %s and b: %s\nc: %s\n", bignum_tostring(a), bignum_tostring(b), bignum_tostring(c));
    printf("Testing bignum_factorial on n: %d, result: %s\n", 30, bignum_tostring(bignum_factorial(30)));
    printf("The value of factorial of 40 is: %s\n", bignum_tostring(bignum_factorial(40)));    
    
    /*bignum_free(a);
    bignum_free(b);
    bignum_free(c);*/
}

void test_subtraction() {
    bignum *a = bignum_fromstring("4294966296");
    bignum *b = bignum_fromstring("4294956296");
    bignum *c = bignum_sub(a, b);
    printf("Testing bignum subtraction with a: %s and b: %s\nresult: %s, should be: 10000\n", bignum_tostring(a), bignum_tostring(b), bignum_tostring(c));
    printf("Testing bignum subtraction with a: 1111 and b: 999\nresult: %s, should be: 112\n", bignum_tostring(bignum_sub(bignum_fromstring("1111"), bignum_fromstring("999"))));
    printf("Testing bignum subtraction with a: 1111 and b: 987\nresult: %s, should be: 124\n", bignum_tostring(bignum_sub(bignum_fromstring("1111"), bignum_fromstring("987"))));
    
    /*bignum_free(a);
    bignum_free(b);
    bignum_free(c);*/
}

int main() {
    test_addition();
    test_multiplication();
    test_subtraction();
    return 0;
}