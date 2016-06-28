#include "prime_math.h"

#include <iostream>
#include <sstream>

bigint gcd(bigint a, bigint b) {
	return b == 0 ? a : gcd(b, (a % b));
}

bigint phi(bigint n) {
	bigint coprimes = conv<bigint>(0);
	for (bigint i = conv<bigint>(0); i < n - 1; ++i) {
		if (NTL::GCD(n, i) == 1) {
			coprimes++;
		}
	}
	return coprimes;
}

bigfloat log2(bigint n) {
	return (NTL::log(conv<bigfloat>(n)) / NTL::log(conv<bigfloat>(2)));
}

bool isint(bigfloat b) {
	return (b - trunc(b) == 0);
}



void nthroot(ZZ &root, const ZZ &n, const ZZ &e) {
	ZZ y;
	RR ll = conv<RR>(NumBits(n)) / conv<RR>(e);
	root = CeilToZZ(pow(conv<RR>(2), ll));
	while (true) {
		y = (e - 1) * root + n / CeilToZZ(pow(conv<RR>(root), conv<RR>(e - 1)))	;
		y /= e;
		if (y >= root)
			return;
		else root = y;
	}
}

bool is_perfect_power(bigint &n_ZZ) {
	// NTL doesn't have the perfect power function but GMP has
	// So convert from NTL_ZZ to string and create a mpz_t from string
	// Then, call GMP perfect power function
	static char n_str[2048];
	mpz_t n_gmp;
	mpz_init(n_gmp);
	memset(n_str, 0, (sizeof(char)));

	std::ostringstream outs;
	outs << n_ZZ;
	std::istringstream ins(outs.str());
	ins >> n_str;

	mpz_set_str(n_gmp, n_str, 10); //n_gmp = to_big_int(n_str in base 10)

	return mpz_perfect_power_p(n_gmp);
}

void reduce_exponents(ZZ_pX &p, const ZZ &r) {
	// Reduction of the exponents mod r

	long i = deg(p);
	long rl;
	long i_mod_r;
	ZZ_p coef;			// current (high-order) coeff
	ZZ_p newcoef;		// put into new (low-order) coeff


	//Due to NTL limitations, "r" can't be bigger than a long, if so
	//throw an error
	if (NumBits(r) > (sizeof(long) * 8)) {
		std::cerr << "Error, r is too big: " << NumBits(r)  << " bits." << std::endl;
		exit(-1);
		return;
	}
	rl = conv<long>(r);

	while (i >= rl) {
		coef = coeff(p, i);
		if (!IsZero(coef)) {
			i_mod_r = i % rl;

			// Add the value of the high-order coefficient to that of the
			// equivalent (mod r) low-order coefficient
			newcoef = coeff(p, i_mod_r);
			add(newcoef, newcoef, coef);

			// Update the value of the low-order coefficient and clear the high-order one
			SetCoeff(p, i % rl, newcoef);
			SetCoeff(p, i, 0);
		}
		i--;
	}
}

bigint random_btwn(bigint a, bigint b) {
	return (RandomBnd(b + 1 - a) + a);
}

bigint power_mod(bigint &a, bigint &e, bigint &n) {
	bigint a_mod_n = a % n;
	bigint e_mod_n = e % n;
	return PowerMod(a_mod_n, e_mod_n, n);
}

bigint power_mod(bigint &a, long e, bigint &n) {
	return PowerMod((a % n), (conv<bigint>(e) % n), n);
}