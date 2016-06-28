#include "rsa_lib.h"

#define DEBUG 0

#include "debug.h"
#include "prime_math.h"

void print_rsa_key_d(rsa_key &key);


rsa_keys_tuple gen_keys(bigint &p, bigint &q, int e_lower_limit) {

	bigint n = p * q;
	bigint phi = n - (p + q - 1);

	bigint e, d;

	for (e = e_lower_limit; e < phi; ++e) {
		if (GCD(e, phi) == 1) {
			break;
		}
	}

	d = InvMod(e, phi);

	rsa_key private_key, public_key;

	public_key = std::make_tuple(n, e);
	private_key = std::make_tuple(n, d);

	dout << "p	" << p << std::endl;
	dout << "q	" << q << std::endl;
	dout << "n	" << n << std::endl;
	dout << "phi	" << phi << std::endl;
	dout << "e	" << e << std::endl;
	dout << "d	" << d << std::endl;
	print_rsa_key_d(public_key);
	print_rsa_key_d(private_key);


	return std::make_tuple(public_key, private_key);

}

bigint rsa_encrypt(rsa_key &key, bigint &p) {
	dout << "p	" << p << std::endl;
	return power_mod(p, std::get<1>(key), std::get<0>(key));
}

bigint rsa_decrypt(rsa_key &key, bigint &c) {
	dout << "c	" << c << std::endl;
	return power_mod(c, std::get<1>(key), std::get<0>(key));
}

void print_rsa_key_d(rsa_key &key) {
	dout << "(" << std::get<0>(key) << "," << std::get<1>(key) << ")" << std::endl;
}