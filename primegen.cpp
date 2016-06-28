#include <iostream>
#include "prime_lib.h"


int main(int argc, char *argv[]) {

	NTL::ZZ number(NTL::INIT_VAL, argv[1]);
	NTL::ZZ prime_number = generate_prime(number);

	std::cout << prime_number << std::endl;

	return 0;
}
