using namespace std;

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

long long lcm(long long a, long long b)
{
	return b * a / gcd(a, b);
}

struct frac_t
{
	long long num;
	long long denom;
};

frac_t frac_multiply(frac_t a, frac_t b)
{
	frac_t c;
	c.num = a.num*b.num;
	c.denom = a.denom*b.denom;
	return c;
}

frac_t frac_add(frac_t a, frac_t b)
{
	frac_t c;
	long long dn = lcm(a.denom, b.denom);
	c.denom = dn;
	c.num = dn / a.denom * a.num + dn / b.denom * b.num;
	return c;
}

frac_t frac_reduced(frac_t a)
{
	long long g = gcd(a.denom, a.num);
	a.num /= g;
	a.denom /= g;
	return a;
}

void frac_reduce(frac_t &a)
{
	a = frac_reduced(a);
}