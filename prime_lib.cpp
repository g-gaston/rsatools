#include "prime_lib.h"
#include "prime_math.h"

#include <NTL/RR.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZ_p.h>
#include <gmp.h>

#include <iostream>
#include <sstream>

#define DEBUG 0

#ifndef DEBUG
#define DEBUG 0
#endif
#if DEBUG
#define dout std::cout
#else
#define dout 0 && std::cout
#endif

#define MILLER_RABIN_ROUNDS 40

typedef NTL::RR bigfloat;

using namespace NTL;

const bool smallprimes[] = { 0,
                             0, 1, 1, 0, 1, 0, 1, 0, 0, 0,
                             1, 0, 1, 0, 0, 0, 1, 0, 1, 0,
                             0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
                             1, 0, 0, 0, 0, 0, 1, 0, 0, 0,
                             1, 0, 1, 0, 0, 0, 1, 0, 0, 0,
                             0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
                             1, 0, 0, 0, 0, 0, 1, 0, 0, 0,
                             1, 0, 1, 0, 0, 0, 0, 0, 1, 0,
                             0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
                             0, 0, 0, 0, 0, 0, 1, 0, 0, 0
                           };

bool aks_prime_check(bigint n) {
	// AKS primality test

	dout << "The value of n is " << n << std::endl;


	if (n < 100) {
		// There are some problems with small integers, so handle it with a precomputed table
		return smallprimes[conv<int>(n)];
	} else if (n % 2 == 0) {
		//Even numbers
		return false;
	}

	// Check if n is a power: if n = a^b for integers a > 1 and b > 1, output composite.
	dout << "Step 1" << std::endl;

	if (is_perfect_power(n)) {
		return false; //Composite
	}

	// Find the smallest r such that Or(n) > (log2 n)^2.
	dout << "Step 2" << std::endl;
	bigfloat log2n = log2(n);
	bigint log2n2 = CeilToZZ(power(log2n, 2)); //upper limit

	bigint r, j, k, q, res, n_mod_q, j_mod_q;
	q = log2n2 + 1;
	while (1) {
		bool not_founded = true;
		for (j = 1; j <= log2n2; j++) {
			res = power_mod(n, j, q); //our function reduces before computing modular exponentiation (res = n^j % q)
			if (IsOne(res)) {		  //PowerMod(a, e, n) would dead with 'bad args' because a must be smaller than n
				not_founded = false;
				break;
			}
		}
		if (not_founded) {
			r = q;
			break;
		}
		q++;
	}

	if (r > n) {
		return false;
	}

	dout << "The value of r is " << r << std::endl;

	// For all a ≤ r, check that a is coprime to n: If 1 < gcd(a,n) < n for some a ≤ r, output composite.
	// This step could be integrated in the last one, using the same loop for booth
	dout << "Step 3" << std::endl;
	for (bigint a = r; a > conv<bigint>(1); --a) {
		bigint gcd_an = GCD(a, n);
		if (!IsOne(gcd_an)) {
			return false;
		}
	}


	//Step 5 test
	dout << "Step 5" << std::endl;

	bigfloat sqrt_r_log2n;
	bigint a, a_maxlimit, n_mod_r;
	long bitlength;
	ZZ_pX base, left, right;
	ZZ_p::init(n);

	sqrt_r_log2n = sqrt(conv<bigfloat>(r)) * conv<bigfloat>(log2n);
	a_maxlimit = CeilToZZ(sqrt_r_log2n);

	bitlength = NumBits(n);

	for (a = 0; a < a_maxlimit; ++a) {
		long a_long, leadingCoeff;
		//Due to NTL limitations, "a" can't be bigger than a long, if so
		//throw an error
		if (NumBits(a) > (sizeof(long) * 8)) {
			std::cout << "Error, a is too big: " << NumBits(a)  << " bits." << std::endl;
			return false;
		}
		a_long = conv<long>(a);

		SetCoeff(base, 1, 1);
		SetCoeff(base, 0, a_long);
		// base = (x+a)

		left = 1;

		// Construct left side
		for (long u = bitlength; u != 0; u--) {
			sqr(left, left);

			if (bit(n, u - 1) == 1) {
				left = left * base;
			}
			reduce_exponents(left, r);
		}

		// Build the right side and perform the final comparison
		n_mod_r = n % r;

		//Due to NTL limitations, "leadingCoeff" can't be bigger than a long, if so
		//throw an error
		if (NumBits(n_mod_r) > (sizeof(long) * 8)) {
			std::cout << "Error, n_mod_r is too big: " << NumBits(n_mod_r)  << " bits." << std::endl;
			return false;
		}
		leadingCoeff = conv<long>(n_mod_r);
		SetCoeff(right, 0, a_long);
		SetCoeff(right, leadingCoeff, 1);

		if (left != right) {
			return false;
		}
	}

	return true;
}

bool mr_prime_check(bigint n) {

	// Must have ODD n greater than THREE
	if ( n == 2 || n == 3 ) {
		return true;
	} else if ( n <= 1 || (n & 1) == 0 ) {
		return false;
	}

	bigint d, s, n_minus_one;
	s = 0;
	n_minus_one = n - 1;

	// Write n-1 as d*2^s by factoring powers of 2 from n-1
	for (d = n_minus_one; (d & 1) != 1; d >>= 1) {
		s++;
	}

	for (int k = 0; k < MILLER_RABIN_ROUNDS; ++k) {
		bigint a = random_btwn(conv<bigint>(2), n - 2);
		bigint b = PowerMod(a, d, n);

		if (b == 1 || b == n_minus_one) {
			continue; //Probably prime
		}

		for (int i = 1; i <= s - 1; ++i) {
			b = PowerMod(b, 2, n);
			dout << "b " << b << std::endl;
			if (b == 1) {
				dout << "Not prime because:" << std::endl;
				dout << "d " << d << std::endl;
				dout << "s " << s << std::endl;
				dout << "a " << a << std::endl;
				dout << "i " << i << std::endl;
				dout << "k " << k << std::endl;
				return false;
			} else if (b == n_minus_one) {
				goto next_round; //Probably prime
			}
		}

		return false;
next_round:
		continue;
	}

	return true;
}

bigint generate_prime(bigint length) {
	dout << "length " << length << std::endl;
	bigint lower_limit = conv<bigint>(pow(conv<bigfloat>(2), conv<bigfloat>(length - 1)));
	bigint upper_limit = conv<bigint>(pow(conv<bigfloat>(2), conv<bigfloat>(length)));
	while(true) {
	    bigint start = random_btwn(lower_limit, upper_limit);
	    dout << "start " << start << std::endl;

	    bigint candidate = start;

	    if ((candidate & 1) == 0) {
	    	candidate++;
	    }

	    for (; candidate < upper_limit; candidate += 2) { //Prime should be between start and 2*start by X theorem
	    	if (mr_prime_check(candidate)) {			  //Since 2*start >= upper_limit, we only search until upper_limit
	    		return candidate;
	    	}
	    }
	}
}