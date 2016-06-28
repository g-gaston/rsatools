#include <iostream>
#include "rsa_lib.h"

int main(int argc, char *argv[]) {

	NTL::ZZ n(NTL::INIT_VAL, argv[1]);
	NTL::ZZ e(NTL::INIT_VAL, argv[2]);
	NTL::ZZ p;

	if (!isdigit(argv[3][0])) {
		p = (int)(argv[3][0]);
		std::cout << "no digit" << std::endl;
	} else {
		p = bigint(NTL::INIT_VAL, argv[3]);
	}

	rsa_key public_key = std::make_tuple(n, e);

	bigint c = rsa_encrypt(public_key, p);

	std::cout << c << std::endl;


	return 0;
}


