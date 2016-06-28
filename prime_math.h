#ifndef PRIME_MATH_H
#define PRIME_MATH_H

#include <NTL/RR.h>
#include <NTL/ZZ.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_p.h>
#include <gmp.h>

typedef NTL::ZZ bigint;
typedef NTL::RR bigfloat;

using namespace NTL;

bool is_perfect_power(bigint &n_ZZ);
void reduce_exponents(ZZ_pX &p, const ZZ &r);

bigint gcd(bigint a, bigint b);
bigint phi(bigint n);
bigfloat log2(bigint n);
bool isint(bigfloat b);
void nthroot(ZZ &root, const ZZ &n, const ZZ &e);
bigint random_btwn(bigint a, bigint b);
bigint power_mod(bigint &a, bigint &e, bigint &n);
bigint power_mod(bigint &a, long e, bigint &n);


#endif