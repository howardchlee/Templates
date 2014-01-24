#include <iostream>

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

int main()
{
	cout << gcd(102030405072, 12344) << endl; 
	cout << gcd(299792458, 256964964) << endl;
}	
