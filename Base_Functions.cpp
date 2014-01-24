/*
 *	Base Functions:  These functions are used to translate numbers of
 *			 base 10 to base numbers from 2 to 35, or vice versa.
 *
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string toBase(int a, int b)
{
	if(a == 0)
		return "0";
	string ret = "";
	while(a != 0)
	{
		int d = a % b;
		char c;
		if(d < 10)
			c = '0'+d;
		else
			c = 'A' + d - 10;
		string t = "";
		t += c;
		ret = t + ret;
		a/=b;
	}

	return ret;
}

// returns base^exp for positive integer base and exp
long long pow(int base, int exp)
{
	long long ret = 1;
	for(int i = 0; i < exp; i++)
	{
		ret *= base;
	}	
	
	return ret;
}

long long toBase10(const string &s, int base)
{
	long long res = 0;
	for(size_t i = 0; i < s.size(); i++)
	{
		size_t dig = s.size() - i - 1;
		if(isdigit(s[dig]))
		{
			res += (s[dig]-'0')*pow(base, i);
		}
		else
		{
			res += (s[dig]-'A'+10)*pow(base, i);
		}
	}
	
	return res;
}

int main()
{
	cout << toBase(1033, 14) << endl;
	cout << toBase10("123ABC", 15) << endl;
	cout << toBase10("23FG", 23) << endl;
	return 0;	
}
