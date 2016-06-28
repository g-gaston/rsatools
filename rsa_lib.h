#ifndef RSA_LIB_H
#define RSA_LIB_H

#include "prime_lib.h"
#include <tuple>

typedef std::tuple <bigint, bigint> rsa_key;
typedef std::tuple <rsa_key, rsa_key> rsa_keys_tuple;

rsa_keys_tuple gen_keys(bigint &p, bigint &q, int e_lower_limit = 2);
bigint rsa_encrypt(rsa_key &key, bigint &p);
bigint rsa_decrypt(rsa_key &key, bigint &c);

#endif