#include <iostream>

using namespace std;

#define set_t long long
#define index_t int

set_t set_add(set_t s, index_t e)
{
	return s | (1 << e);
}

set_t set_remove(set_t s, index_t i)
{
	return s & (~(1 << i));
}

int set_count(set_t s)
{
	int count = s & 1 ? 1 : 0;
	while(s = s >> 1)
	{
		if( s & 1)
			count++;
	}
	return count;
}

bool set_contains(set_t s, index_t i)
{
	return (s >> i) & 1;
}

set_t set_union(set_t s1, set_t s2)
{
	return s1 | s2;
}

set_t set_intersect(set_t s1, set_t s2)
{
	return s1 & s2;
}

bool set_full(set_t s1, size_t size)
{
	while(s1)
	{
		if(!(s1&1))
			return false;
		s1>>1;
	}
	return true;
}

int main()
{
	set_t myset = 0;
	myset = set_add(myset, 2);
	myset = set_add(myset, 4);
	myset = set_add(myset, 3);
	myset = set_add(myset, 0);
	myset = set_remove(myset, 7);
	myset = set_remove(myset, 3);
	for(index_t i = 0; i < 8; i++)
	{
		if(set_contains(myset, i))
			cout << "The set contains " << i << endl;
		else
			cout << "The set does not contain " << i << endl;
	}
}