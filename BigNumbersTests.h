#pragma once
#include "BigNumbers.h"

bignum *bignum_fibonnaci(int n);
bignum *bignum_factorial(int n);

void test_addition();
void test_multiplication();
void test_subtraction();

void test_isbigger();
void test_remainder();
void test_addmod();
void test_multmod();
void test_expmod();

void test_int2bignum();
void test_longlong2bignum();
void test_fermat();
void test_bignum_toint();
void test_expmod_efficient();

void testRSA(int length);
