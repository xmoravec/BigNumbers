#include "BigNumbersTests.h"
#include "inttypes.h"

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

void test_addition() {
    bignum *a = bignum_fromstring("4294966296");
    bignum *b = bignum_fromstring("4294966296");
    bignum *c = bignum_add(a, b);
    printf("Testing bignum addition with a: %s and b: %s\nresult: %s\n", bignum_tostring(a), bignum_tostring(b), bignum_tostring(c));
    printf("Testing bignum_fibonnaci on n: %d\nresult: %s\n", 100, bignum_tostring(bignum_fibonnaci(100)));
    printf("The 101th value of fibonnacci is: %s\n", bignum_tostring(bignum_fibonnaci(101)));
}

void test_multiplication() {
    bignum *a = bignum_fromstring("4291496629");
    bignum *b = bignum_fromstring("15734966296");
    bignum *c = bignum_multiply(a, b);
    printf("Testing bignum multiply with a: %s and b: %s\nc: %s\n", bignum_tostring(a), bignum_tostring(b), bignum_tostring(c));
    printf("Testing bignum_factorial on n: %d, result: %s\n", 30, bignum_tostring(bignum_factorial(30)));
    printf("The value of factorial of 40 is: %s\n", bignum_tostring(bignum_factorial(40)));    
}

void test_subtraction() {
    bignum *a = bignum_fromstring("4294966296");
    bignum *b = bignum_fromstring("4294956296");
    bignum *c = bignum_sub(a, b);
    printf("Testing bignum subtraction with a: %s and b: %s\nresult: %s, should be: 10000\n", bignum_tostring(a), bignum_tostring(b), bignum_tostring(c));
    printf("Testing bignum subtraction with a: 1111 and b: 999\nresult: %s, should be: 112\n", bignum_tostring(bignum_sub(bignum_fromstring("1111"), bignum_fromstring("999"))));
    printf("Testing bignum subtraction with a: 1111 and b: 987\nresult: %s, should be: 124\n", bignum_tostring(bignum_sub(bignum_fromstring("1111"), bignum_fromstring("987"))));
}

void test_isbigger() {
    bignum *a = bignum_fromstring("4294966296");
    bignum *b = bignum_fromstring("4294956296");
    printf("Testing bignum isbigger with a: 100000 and b: 99999\nresult: %s, should be: true\n", bignum_isbigger(bignum_fromstring("100000"), bignum_fromstring("99999")) ? "true" : "false");
    printf("Testing bignum isbigger with a: 74569 and b: 8585858585\nresult: %s, should be: false\n", bignum_isbigger(bignum_fromstring("74569"), bignum_fromstring("8585858585")) ? "true" : "false");
    printf("Testing bignum isbigger with a: %s and b: %s\nresult: %s, should be: true\n", bignum_tostring(a), bignum_tostring(b), bignum_isbigger(a, b) ? "true" : "false");
}

void test_remainder() {
    bignum *a = bignum_fromstring("4295034142");
    bignum *b = bignum_fromstring("1295030142");
    printf("Testing bignum remainder with a: %s and b: %s\nresult: %s, should be: 409943716\n", bignum_tostring(a), bignum_tostring(b), bignum_tostring(bignum_remainder(a, b)));
}

void test_addmod() {
    bignum *a = bignum_fromstring("4295034142");
    bignum *b = bignum_fromstring("100000000");
    bignum *n = bignum_fromstring("1295030142");
    printf("Testing addmod with a: %s and b: %s and n: %s\nresult: %s, should be: 509943716\n", bignum_tostring(a), bignum_tostring(b), bignum_tostring(n), bignum_tostring(bignum_addmod(a, b, n)));
}

void test_multmod() {
    bignum *a = bignum_fromstring("4295034142");
    bignum *b = bignum_fromstring("2");
    bignum *n = bignum_fromstring("1295030142");
    printf("Testing multmod with a: %s and b: %s and n: %s\nresult: %s, should be: 819887432\n", bignum_tostring(a), bignum_tostring(b), bignum_tostring(n), bignum_tostring(bignum_multmod(a, b, n)));
}

void test_expmod() {
    bignum *a = bignum_fromstring("47");
    bignum *b = bignum_fromstring("6");
    bignum *n = bignum_fromstring("10000000000");
    printf("Testing expmod with a: %s and b: %s and n: %s\nresult: %s, should be: 779215329\n", bignum_tostring(a), bignum_tostring(b), bignum_tostring(n), bignum_tostring(bignum_expmod(a, b, n)));
}

void test_int2bignum() {
    int i = rand();
    bignum *b = int_tobignum(i);
    printf("Testing int: %d, to bignum b: %s\n", i, bignum_tostring(b));
}

void test_longlong2bignum() {
    long long a = 1123456789876543210;
    bignum *b = longlong_tobignum(a);
    printf("Testing long long: %"PRId64", to bignum b: %s\n", a, bignum_tostring(b));
}

void test_fermat() {
    bignum *a = int_tobignum(7);
    printf("Testing fermat, bignum a: %s, is a prime number: %s\n", bignum_tostring(a), fermat(a, 1) ? "true" : "false");
}

void test_bignum_toint() {
    bignum *test = int_tobignum(2147483647);
    printf("Testing bignum to int, bignum: %s, to int: %d\n", bignum_tostring(test), bignum_toint(test));
}

void test_expmod_efficient() {
    bignum *a = int_tobignum(47);
    bignum *b = int_tobignum(15);
    bignum *n = bignum_fromstring("10000000000");
    printf("Testing efficient expmod with a: %s and b: %s and n: %s\nresult: %s, should be: 779215329\n", bignum_tostring(a), bignum_tostring(b), bignum_tostring(n), bignum_tostring(bignum_expmod_efficient(a, b, n)));
}

int main() {
    test_addition();
    test_multiplication();
    test_subtraction();
    test_isbigger();
    test_remainder();
    test_addmod();
    test_multmod();
    test_expmod();
    test_int2bignum();
    test_longlong2bignum();
    //test_fermat();
    test_bignum_toint();
   // test_expmod_efficient();
    return 0;
}