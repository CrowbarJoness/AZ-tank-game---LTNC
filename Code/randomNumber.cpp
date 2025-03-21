#include "randomNumber.h"
#include <cstdlib> // rand()
#include <iostream>

long long randomNumber() {
	long long r1 = rand();
	long long r2 = rand();
	return r1 * (RAND_MAX + 1) + r2;
}

int randomNumberInRange(const int &a, const int &b) {
	long long randomLimit = (long long)RAND_MAX * (long long)(RAND_MAX + 1) + RAND_MAX;
	int randomRange = b - a + 1;
	long long randomUpperBound = randomLimit - (randomLimit + 1) % randomRange;
	while (1) {
		long long r = randomNumber();
		if (r <= randomUpperBound) return a + r % randomRange;
	}
}
