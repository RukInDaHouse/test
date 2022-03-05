#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIGN 0x80000000
#define SCALE 0xFF0000

#define FALSE 1
#define TRUE 0

#define BITS_COUNT 4
#define SBITS_COUNT 7

typedef unsigned long long uint64;
typedef unsigned int uint32;

typedef union {
    uint32 _int;
    float _float;
} val;

typedef enum {
    s21_NORMAL_VALUE = 0,
    s21_INFINITY = 1,
    s21_NEGATIVE_INFINITY = 2,
    s21_NAN = 3
} value_type_t;

typedef struct {
    int bits[BITS_COUNT];
    value_type_t value_type;
} s21_decimal;

typedef struct {
    int bits[SBITS_COUNT];
} sDecimal;

// MATH //
s21_decimal s21_add(s21_decimal src1, s21_decimal src2);
s21_decimal s21_negate(s21_decimal src);
s21_decimal s21_sub(s21_decimal src1, s21_decimal src2);
s21_decimal s21_mul(s21_decimal src1, s21_decimal src2);
s21_decimal s21_div(s21_decimal src1, s21_decimal src2);
s21_decimal s21_mod(s21_decimal src1, s21_decimal src2);
s21_decimal s21_truncate(s21_decimal dst);
s21_decimal s21_floor(s21_decimal dst);
s21_decimal s21_round(s21_decimal dst);

// CONVERTERS AND PARSERS //
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// COMPARE FUNCTIONS //
int s21_is_equal(s21_decimal src1, s21_decimal src2);
int s21_is_not_equal(s21_decimal src1, s21_decimal src2);
int s21_is_less(s21_decimal src1, s21_decimal src2);
int s21_is_greater(s21_decimal src1, s21_decimal src2);
int s21_is_less_or_equal(s21_decimal src1, s21_decimal src2);
int s21_is_greater_or_equal(s21_decimal src1, s21_decimal src2);
int s21_is_(int(c)(int *, int *), s21_decimal a, s21_decimal b);
int _less(int *a, int *b);
int _greater(int *a, int *b);

// SUBSIDIARY FUNCTIONS //
s21_decimal *cpy_dec(s21_decimal *dst, s21_decimal src);
void increase_degree(s21_decimal *dec, char deg);
void equate_degree(s21_decimal *a, s21_decimal *b);

int _cmp_vt(s21_decimal a, s21_decimal b);
int dec_types(s21_decimal a, value_type_t t1, s21_decimal b, value_type_t t2);
int dec_type(s21_decimal a, s21_decimal b, value_type_t t);
int _is_infinity(s21_decimal a, s21_decimal b);
int _is_normal(s21_decimal a, s21_decimal b);

int get_float_sign(float *src);
int get_float_exp(float *src);
int _sum(s21_decimal *a, s21_decimal *b);
int get_sign(int *bits);
int get_degree(int *bits);


// NEW DECIMAL //

int check_bit(s21_decimal dst, int bit_number);
void set_bit(s21_decimal *dst, int bit_number);
int sCheck_bit(sDecimal dst, int bit_number);
void sSet_bit(sDecimal *dst, int bit_number);

void sDecimal_shift_right(sDecimal *dst);
void sDecimal_shift_left(sDecimal *dst);

void plus(s21_decimal *src1, s21_decimal *src2);
sDecimal sPlus(sDecimal dst, sDecimal src);
void mul(s21_decimal *src1, s21_decimal *src2);
void sMul(sDecimal *src1, sDecimal *src2);
void minus(s21_decimal *src1, s21_decimal *src2);
sDecimal sMinus(sDecimal src1, sDecimal src2);
sDecimal sDiv(sDecimal src1, sDecimal src2);
sDecimal sMod(sDecimal src1, sDecimal src2);

int elder_bit(s21_decimal dst);
int elder_sBit(sDecimal dst);

void zero_sDecimal(sDecimal *src);
void zero_decimal(s21_decimal *src);
void from_decimal_to_sDecimal(s21_decimal src, sDecimal *result);

void norm_exp(sDecimal *tmp11, sDecimal *tmp2);
s21_decimal normalize(sDecimal src);

int sDecimal_is_less(sDecimal src1, sDecimal src2);
int sDecimal_is_less_or_equal(sDecimal src1, sDecimal src2);
int sDecimal_is_greater(sDecimal src1, sDecimal src2);
int sDecimal_is_greater_or_equal(sDecimal src1, sDecimal src2);
int sDecimal_is_equal(sDecimal src1, sDecimal src2);
int sDecimal_is_not_equal(sDecimal src1, sDecimal src2);

#endif  //  SRC_S21_DECIMAL_H_
