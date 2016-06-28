#ifndef PRIM_LIB_H
#define PRIM_LIB_H

#include <NTL/ZZ.h>
// Compile with g++ prime_lib.cpp -lntl -lgmp -lm

typedef NTL::ZZ bigint;

bool aks_prime_check(bigint n);
bool mr_prime_check(bigint n);

bigint generate_prime(bigint length);

#endif