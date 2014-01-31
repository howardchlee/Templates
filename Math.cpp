

#include <iostream>
#include <vector>

using namespace std;

double fast_pow(double a, int n)
{
	double ret = 1;
	while(n)
	{
		if(n%2 == 1) ret *= a;
		a *= a;
		n/= 2;
	}

	return ret;
}


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

/*
 *   Fast Combination:  This is used to compute C(n, r) % p, where p is prime, 
 *                      quickly using Euler's Theorem to calculate modular
 *			inverses in the Zp group.
 */

// calculates nCr (mod p), where p is prime 
// since Zp is cyclic, 
// 	n! / (r! (n-r)!) = n! (r!)^(-1) ((n-r)!)^(-1) (mod p)
long long FC(long long n, long long r, long long p) 
{
 	vector<long long> f(n+1, 1);

	// calculates factorials
	for(int i = 2; i <= n; i++)
		f[i] = (f[i-1]*i) % p;
	long long invfrp = modularInversePrime(f[r], p);
	long long invfnrp = modularInversePrime(f[n-r], p);
	return (f[n]*((invfrp * invfnrp) % p)) % p;
}

void makeTestCase(long long a1, long long a2, long long p)
{
	cout << "C(" << a1 << ", " << a2 << ") % " << p << " = " << FC(a1, a2, p) << endl;
}

int main()
{
	makeTestCase(25, 23, 1000000007);
	makeTestCase(27, 21, 1000000007);
	makeTestCase(5, 2, 13);
}
