# some simple prime functions

import math;

def computePrimesUpTo(n):
	ret = [];
	isPrime = [True] * (n+1);
	isPrime[0] = False;
	isPrime[1] = False;
	for i in range(n+1)[2:]:
		if isPrime[i]:
			ret.append[i];
		for j in range(n+1)[i*i:n+1:i]:
			isPrime[j] = False;
	return ret
	
def getPrimeFactorsOf(self, n):
	primePowers = {};
		
	i = 2;

	while i <= math.sqrt(n):
		if(n % i == 0):
			power = 0;
			while(n % i == 0):
				n/=i;
				power+= 1;
			primePowers[i] = power;
		i+=1;
	if(n > 1):
		primePowers[n] = 1;
	return primePowers;

		