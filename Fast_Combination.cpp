#include <iostream>

// 1. FastCombination

// calculates (a^b) % p
long long pow(long long a, long long b, long long p)
{
	long long x = 1, y = a;
	while(b > 0)
	{
		if(b%2 == 1)
		{
			x = x*y;
			if(x > p) x %= p;
		}
		y = y*y;
		if(y > p) y %= p;
		b/=2;
	}

	return x;
}

// calculates modular multiplicative inverse if mod is prime
//
// phi(n) = the number of positive integers less than or equal
//          to n that are relatively prime to n
// Euler's Theorem says if a is coprime to n (true because n is prime)
//	a^(phi(n)) = 1 (mod n)
// since n is a prime,
//	phi(n) = n-1.
// therefore
// 	a^(n-1) = 1 (mod n)
//      a^((n-1)-1) = a^(-1) (mod n)
//	a^(n-2) = a^(-1) (mod n)

long long modularInversePrime(long long a, long long n)
{
	return pow(a, n-2, n);
}

// calculates nCr (mod p)
long long C(long long n, long long r, long long p)
{
	vector<long long> f(n+1, 1);
	for(int i = 2; i <= n; i++)
		f[i] = (f[i-1]*i) % p;
	return (f[n]*((modularInversePrime(f[r], p) * modularInversePrime(f[n-r], p)) % p)) % p;
}
