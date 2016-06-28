#include <iostream>
#include <ctype.h>
#include "rsa_lib.h"

int main(int argc, char *argv[]) {

	NTL::ZZ n(NTL::INIT_VAL, argv[1]);
	NTL::ZZ d(NTL::INIT_VAL, argv[2]);
	NTL::ZZ c(NTL::INIT_VAL, argv[3]);


	rsa_key private_key = std::make_tuple(n, d);

	bigint p = rsa_decrypt(private_key, c);

	std::cout << p << std::endl;


	return 0;
}
