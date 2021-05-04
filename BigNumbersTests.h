#pragma once
#include "BigNumbers.h"

/* Done */
bignum *bignum_fibonnaci(int n);
bignum *bignum_factorial(int n);

void test_addition();
void test_multiplication();
void test_subtraction();

/* TODO */
//tests for all the operations that are yet to be implemented.

/* TODO RSA */
void testRSA(int length);

//Optional Memory deallocation (free)