#include <iostream>
#include <string>
#include "prime_lib.h"


int main(int argc, char *argv[]) {

	std::string result_str = "False";
	bool result = false;

	if (argc == 2) {
		if (std::string(argv[1]) == "-h") {
			std::cout << "Use: primecheck [opt] number" << std::endl;
			std::cout << "	Options:" << std::endl;
			std::cout << "	 -t (test): aks (AKS), mr (Miller-Rabin)" << std::endl;
			return 0;
		} else {
			NTL::ZZ number(NTL::INIT_VAL, argv[1]);
			result = mr_prime_check(number);
		}
	} else if (argc == 4) {
		std::string argv1(argv[1]);
		std::string argv2(argv[2]);

		if (argv1 == "-t" && argv2 == "aks") {
			NTL::ZZ number(NTL::INIT_VAL, argv[3]);
			result = aks_prime_check(number);
		} else if (argv1 == "-t" && argv2 == "mr") {
			NTL::ZZ number(NTL::INIT_VAL, argv[3]);
			result = mr_prime_check(number);
		} else {
			goto error;
		}

	} else {
error:
		std::cerr << "Invalid syntax" << std::endl;
		std::cout << "Use: primecheck [opt] number" << std::endl;
		std::cout << "	Options:" << std::endl;
		std::cout << "	 -t (test): aks (AKS), mr (Miller-Rabin)" << std::endl;
		return 0;
	}


	if (result) {
		result_str = "True";
	}

	std::cout << result_str << std::endl;

	return 0;
}
