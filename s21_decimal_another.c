#include "s21_decimal.h"

s21_decimal s21_round(s21_decimal dst) {
    s21_decimal result = dst;
    if (result.value_type == s21_NORMAL_VALUE) {
        result = s21_truncate(dst);
        s21_decimal ten, res;
        res = s21_truncate(dst);
        s21_from_int_to_decimal(10, &ten);
        int exp = (dst.bits[3] << 1) >> 17;
        int sign = dst.bits[3];
        dst.bits[3] = res.bits[3] = 0;
        for (int i = 0; i < exp; i++) res = s21_mul(res, ten);
        res = s21_sub(dst, res);
        sDecimal sRes, sTen, sFinal;
        from_decimal_to_sDecimal(ten, &sTen);
        from_decimal_to_sDecimal(res, &sRes);
        for (int i = 0; i < exp - 1; i++) sRes = sDiv(sRes, sTen);
        if (sRes.bits[0] >= 5) sRes.bits[0] = 1;
        else
            sRes.bits[0] = 0;
        from_decimal_to_sDecimal(result, &sFinal);
        sFinal = sPlus(sFinal, sRes);
        result = normalize(sFinal);
        if (sign < 0) result.bits[3] |= SIGN;
    }
    return result;
}

s21_decimal s21_floor(s21_decimal dst) {
    s21_decimal result = dst;
    if (result.value_type == s21_NORMAL_VALUE) {
        result = s21_truncate(dst);
        s21_decimal res, ten;
        s21_from_int_to_decimal(10, &ten);
        int exp = (dst.bits[3] << 1) >> 17;
        int sign = (dst.bits[3] >> 31) << 31;
        res = s21_truncate(dst);
        for (int i = 0; i < exp; i++) res = s21_mul(res, ten);
        res = s21_sub(dst, res);
        sDecimal sRes, sOne, sZero, sFinal;
        zero_sDecimal(&sOne);
        zero_sDecimal(&sZero);
        sOne.bits[0] = 1;
        from_decimal_to_sDecimal(result, &sFinal);
        from_decimal_to_sDecimal(res, &sRes);
        if (sign < 0) {
            if (sDecimal_is_not_equal(sRes, sZero) == TRUE) sFinal = sPlus(sFinal, sOne);
            result = normalize(sFinal);
            result.bits[3] |= SIGN;
        }
    }
    return result;
}

s21_decimal s21_truncate(s21_decimal dst) {
    s21_decimal result = dst;
    if (result.value_type == s21_NORMAL_VALUE) {
        sDecimal ten, zero, sResult;
        zero_sDecimal(&ten);
        ten.bits[0] = 10;
        zero_sDecimal(&zero);
        int exp = (dst.bits[3] << 1) >> 17;
        int sign = dst.bits[3];
        result.bits[3] = 0;
        from_decimal_to_sDecimal(result, &sResult);
        for (int i = 0; i < exp; i++) {
            if (sDecimal_is_equal(sResult, zero) == TRUE) break;
            sResult = sDiv(sResult, ten);
        }
        result = normalize(sResult);
        if (sign < 0) result.bits[3] |= SIGN;
    }
    return result;
}

s21_decimal s21_negate(s21_decimal src) {
    if (src.value_type == s21_INFINITY)
        src.value_type = s21_NEGATIVE_INFINITY;
    else if (src.value_type == s21_NEGATIVE_INFINITY)
        src.value_type = s21_INFINITY;
    else if (src.value_type != s21_NAN)
        src.bits[3] ^= SIGN;
    return src;
}
