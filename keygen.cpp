#include <iostream>
#include "rsa_lib.h"

void print_rsa_key(rsa_key key);


int main(int argc, char *argv[]) {

	NTL::ZZ p(NTL::INIT_VAL, argv[1]);
	NTL::ZZ q(NTL::INIT_VAL, argv[2]);

	rsa_keys_tuple keys;

	if (argc == 5) {
		keys = gen_keys(p, q, atoi(argv[4]));
	} else {
		keys = gen_keys(p, q);
	}


	rsa_key private_key, public_key;

	public_key = std::get<0>(keys);
	private_key = std::get<1>(keys);

	std::cout << "Public Key: ";
	print_rsa_key(public_key);

	std::cout << "Private Key: ";
	print_rsa_key(private_key);

	return 0;
}

void print_rsa_key(rsa_key key) {
	std::cout << "(" << std::get<0>(key) << "," << std::get<1>(key) << ")" << std::endl;
}
