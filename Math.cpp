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

#include <cmath>

// | X(x1, x2) x Y(y1, y2) |
double cross(double x1, double x2, double y1, double y2)
{
	return x1*y2 - x2*y1;
}

// area of triangle defined by points A, B, C
double triangleArea(double a1, double a2, double b1, double b2, double c1, double c2)
{
	double r =  cross(b1-a1, b2-a2, c1-a1, c2-a2);
	return 0.5*abs(r);
} 

// area of shape defined by points in vector<points>.  n >= 3
struct point_t
{
	double x;
	double y;
};

// doesn't have to be convex, but will return signed area.
double convexArea(vector<point_t> points)
{
	double sum = 0;
	double ox = points[0].x;
	double oy = points[0].y;
	for(int i = 1; i <= points.size()-2; i++)
	{
		sum += cross(points[i+1].x-ox, points[i+1].y - oy, points[i].x - ox, points[i].y - oy);
	}

	return 0.5*abs(sum);
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

// GCD

long long gcd(long long a, long long b)
{
	long long c;
	while(a != 0)
	{
		c = a;
		a = b%a;
		b = c;
	}	

	return b;
}


// the following generates every partition for a set with N elements.  some elements may be ignored
#define N 3

int partition[N];
int pn; // number of partitions currently exist

// return the set representated by bit mask d, note that this is 1-indexed
string setString(int d)
{
	int count = 1;
	string ret = "{";
	while(d != 0)
	{
		if(d%2 == 1)
		{
			ret += to_string(count) + " ";
		}
		count++;
		d/=2;
	}

	ret += "}";
	return ret;
}

void recComputePartition(int d)
{
    if (d == N) 
	{
        // we have generated a partition at this point
		for(int i = 0; i < pn; i++)
		{
			cout << setString(partition[i]);
		}
		cout << endl;
    } 
	else 
	{
        // add to an existing partition ( a partition with 3 elements can be created by
		// adding the third element to a set within a partition of 2 element
		// or by adding the third element as a set of its own)

        for (int i = 0; i < pn; i++) {
            partition[i] ^= (1 << d);
            recComputePartition(d + 1);
            partition[i] ^= (1 << d);
        }

        // add to a new partition
        partition[pn++] = (1 << d);
        recComputePartition(d + 1);
        pn--;
         
        // ignore this d from the partition
        recComputePartition(d + 1);
    }
}