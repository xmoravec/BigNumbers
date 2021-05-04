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
