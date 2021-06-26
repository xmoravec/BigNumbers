#include "BigNumbers.h"

int B = 10;

#define max(a,b) (((a) > (b)) ? (a) : (b))

bignum *bignum_new() {
    bignum *result = malloc(sizeof(bignum));
    result->size = 1;
    result->sign = 0;
    result->tab = malloc(sizeof(int));
    return result;
}

void bignum_free(bignum *a) {
    free(a->tab);
    free(a);
}

void shift_tab(bignum *a) {
    int i = 0;
    while(a->tab[i] == 0) {
        a->size--;
        i++;
    }
    int *new_tab = malloc(a->size * sizeof(int));
    memcpy(new_tab, a->tab + i, a->size * sizeof(int));
    free(a->tab);
}

void bignum_enlarge_double(bignum *a) {
    a->size *= 2;
    a->tab = realloc(a->tab, a->size * sizeof(int));
}

void bignum_enlarge(bignum *a, int new_size) {
    a->size = new_size;
    a->tab = realloc(a->tab, new_size * sizeof(int));
}

bignum *bignum_copy(bignum *a) {
    bignum *copy = bignum_new();
    copy->size = a->size;
    memcpy(copy->tab, a->tab, a->size * sizeof(int));
    return copy;
}

char *bignum_tostring(bignum * b) {
    int size = b->size;
    char *buffer = malloc(size * sizeof(char) + 1);
    for (int j = 0; j < size; j++) {
        buffer[j] = b->tab[j] + '0';
    }
    buffer[size] = '\0';
    return buffer;
}

bignum *bignum_fromstring(char *str) {
    bignum* num = bignum_new();
    bignum_enlarge(num, strlen(str));
    for (unsigned int i = 0; i < strlen(str); i++) {
        num->tab[i] = str[i] - '0';
    }
    return num;
}

bignum *bignum_add(bignum *a, bignum *b) {
    bignum *c = bignum_new();
    c->size = max(a->size, b->size) + 1;
    c->tab = realloc(c->tab, c->size * sizeof(int));

    int j = a->size;
    int l = b->size;
    int k = c->size;
    int carry = 0;
    int tmp = 0;

    for (int i = 0; i < l; i++) {
        tmp = a->tab[j - i - 1] + b->tab[l - i - 1] + carry;
        carry = tmp / B;
        c->tab[k - i - 1] = tmp % B;
    }
    for (int i = l; i < k - 1; i++) {
        tmp = a->tab[j - i - 1] + carry;
        carry = tmp / B;
        c->tab[k - i - 1] = tmp % B;
    }
    c->tab[0] = carry;
    if(c->tab[0] == 0) {
         c->tab++;
         c->size--;
    }
    return c;
}

bignum* bignum_multiply(bignum *a, bignum *b) {
    bignum *c = bignum_new();
    int k = a->size;
    int l = b->size;
    int kl = k + l;
    c->size = kl;
    c->tab = malloc(c->size * sizeof(int));

    int carry = 0;
    int tmp = 0;

    memset(c->tab, 0, kl*sizeof(int));
    for (int i = 0; i < k; i++) {
        carry = 0;
        for (int j = 0; j < l; j++) {
            tmp = a->tab[k - i - 1] * b->tab[l - j - 1] + c->tab[kl - j - i - 1] + carry;
            carry = tmp / B;
            c->tab[kl - j - i - 1] = tmp % B;
        }
        c->tab[kl - i - l - 1] = carry;
    }
    if(c->tab[0] == 0) {
         c->tab++;
         c->size--;
    }
    return c;
}

bignum *bignum_sub(bignum *a, bignum *b) {
    bignum *c = bignum_new();
    c->size = a->size + 1;
    c->tab = malloc(c->size * sizeof(int));

    int k = a->size;
    int l = b->size;
    int kc = k + 1;
    int carry = 0;
    int tmp = 0;

    for (int i = 0; i < l; i++) {
        tmp = a->tab[k - i - 1] - b->tab[l - i - 1] + carry;
        carry = tmp < 0 ? -1 : 0;
        c->tab[kc - i - 1] = (tmp + B) % B;
    }
    for (int i = l; i <= k - 1; i++) {
        tmp = a->tab[k - i - 1] + carry;
        carry = tmp / B;
        c->tab[kc - i - 1] = (tmp + B) % B;
    }

    c->tab[0] = carry;
    while(c->tab[0] == 0) {
         c->tab++;
         c->size--;
    }
    return c;
}

bool bignum_isbigger(bignum *a, bignum *b) {
    if (a->size > b->size) {
        return true;
    }
    if (b->size > a->size) {
        return false;
    }
    for(int i = 0; i < a->size; i++) {
        if (a->tab[i] >  b->tab[i]) {
            return true;
        }
        if (b->tab[i] > a->tab[i]) {
            return false;
        }
    }
    return false;
}

bignum *bignum_remainder(bignum *a, bignum *b) {
    bignum *remainder = bignum_copy(a);
    if (bignum_isbigger(b, a)) {
        return remainder;
    }
    while (bignum_isbigger(remainder, b)) {
        remainder = bignum_sub(remainder, b);
    }
    return remainder;
}

bignum *bignum_addmod(bignum *a, bignum *b, bignum*n) {
    return bignum_remainder(bignum_add(a, b), n);
}

bignum *bignum_multmod(bignum *a, bignum *b, bignum*n) {
    return bignum_remainder(bignum_multiply(a, b), n);
}

bignum *bignum_expmod(bignum *a, bignum *b, bignum*n) {
    bignum *exponent = bignum_copy(b);
    bignum *result = bignum_copy(a);
    while(bignum_isbigger(exponent, bignum_fromstring("1"))) {
        result = bignum_multiply(result, a);
        exponent = bignum_sub(exponent, bignum_fromstring("1"));
    }
    return bignum_remainder(result, n);
}

int int2bin(int b, uint8_t bits[32]) {
    int i = 0;
    while(b > 0) {
        bits[i] = b % 2;
		b = b / 2;
		i++;
	}
    return i;
}

/* This function is probably unnecessary for the project */
int power_mod(int a, int b, int n) {
	unsigned long long r = a;
	uint8_t bits[32];
	int i = int2bin(b, bits) - 1;

	while(i > 0) {
		r = (r * r) % n;
		if (bits[--i] == 1){
			r = (r * a) % n;
		}
	}
	return r;
}

// Also unnecessary but convenient
bignum *int_tobignum(int num) {
    int bignumSize = 1, copy = num;
    while (copy / B != 0) {
        bignumSize++;
        copy /= B;
    }
    bignum *result = bignum_new();
    result->size = bignumSize;
    result->tab = realloc(result->tab, result->size * sizeof(int));
    copy = num;
    for (int i = 0; i < result->size; i++) {
        *(result->tab+i) = copy % B;
        copy /= B;
    }
    int i = result->size / 2, tmp = 0, k = result->size-1;
    for(int l = 0; l < i; l++) {
        tmp = result->tab[l];
        result->tab[l] = result->tab[k];
        result->tab[k--] = tmp;
    }
    return result;
}

bignum *longlong_tobignum(long long num) {
    int bignumSize = 1; long long copy = num, B = 10;
    while (copy / B != (long long) 0) {
        bignumSize++;
        copy /= B;
    }
    bignum *result = bignum_new();
    result->size = bignumSize;
    result->tab = realloc(result->tab, result->size * sizeof(int));
    copy = num;
    for (int i = 0; i < result->size; i++) {
        *(result->tab+i) = (int) (copy % B);
        copy /= B;
    }
    int i = result->size / 2, tmp = 0, k = result->size-1;
    for(int l = 0; l < i; l++) {
        tmp = result->tab[l];
        result->tab[l] = result->tab[k];
        result->tab[k--] = tmp;
    }
    return result;
}

bool fermat(bignum *a, int t) {
    bignum *test = bignum_new();
    bignum *max = bignum_new();
    max = bignum_sub(a, bignum_fromstring("1"));
    bignum *min = bignum_new();
    min = int_tobignum(2);
    bignum *random = bignum_new();
    random = int_tobignum(rand());
    printf("Our random: %s\n", bignum_tostring(random));
    bignum *res = bignum_new();
    bignum *mem = bignum_new();
    for(int i = 1; i <= t; i++) {
        bignum *r = bignum_new();
        res = bignum_sub(max, min);
        printf("res: %s\n", bignum_tostring(res));
        mem = bignum_remainder(random, res);
        printf("mem: %s\n", bignum_tostring(mem));
        test = bignum_add(mem, min);
        printf("test: %s\n", bignum_tostring(test));
        r = bignum_expmod(test, max, a); // All lines are fine but this one, it should be right, but whenever we call expmod it will stop
        shift_tab(r);
        printf("r: %s\n", bignum_tostring(r));
        if(r->size != 1 && r->tab[0] != 1)
            bignum_free(r);
            return false;
        bignum_free(r);
    }
    return true;
}

int bignum_toint(bignum *num) {
    int r = 0;
    int multiplier = 1;
    if(num->size > 1)
        multiplier *= power_mod(B, num->size - 1, INT32_MAX);
    for(int i = 0; i<num->size; i++) {
        r += multiplier * num->tab[i];
        multiplier /= B;
    }
    return r;
}

bignum *bignum_expmod_efficient(bignum *a, bignum *b, bignum *n) {
    char *bin;
    bin = calloc(32, sizeof(char));
    int b_int = bignum_toint(b), i;
    printf("b_int: %d, from b: %s\n", b_int, bignum_tostring(b));
    for(i = 0; b_int > 0; i++) {
        bin[i] = b_int % 2;
        printf("%d", bin[i]);
        b_int /= 2;
    }
    printf("\n");
    bignum *c = bignum_remainder(a, n);
    printf("first c: %s\n", bignum_tostring(c));
    for(i = i-2; i >= 0; i--) {
        c = bignum_multiply(c, c);
        c = bignum_remainder(c, n);
        printf("c: %s\n", bignum_tostring(c));
        if(bin[i] == 1) {
            c = bignum_multiply(c, a);
            c = bignum_remainder(c, n);
            printf("binary number was 1: c: %s\n", bignum_tostring(c));
        }
        printf("\n");
    }
    free(bin);
    return c;
}