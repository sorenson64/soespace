#ifndef _SMALLPRIMES
#define _SMALLPRIMES

#include<iostream>
#include<vector>
#include "int.h"

// small primes routines

vector<bool> isprime;
vector<int32> prime;

int32 primelen; // length of prime array
int32 maxprime; // largest prime found

void makesmallprimes(int32 limit=10000)
{
  isprime.clear();
  isprime.resize(limit+1,true);
  isprime[0]=isprime[1]=false;
  // sieve of Eratosthenes
  prime.clear();
  int q;
  for(q=2; q*q<=limit; q++)
    if(isprime[q])
    {
      prime.push_back(q);
      for(int x=2*q; x<=limit; x+=q) isprime[x]=false;
    }
  for( ; q<=limit; q++)
    if(isprime[q]) prime.push_back(q);
  //prime.shrink_to_fit();
  maxprime=prime.back();
  primelen=prime.size();
}

void testsmallprimes()
{
  makesmallprimes(1000);

  for(int i=0; i<isprime.size(); i++)
    cout << ( isprime[i]?'1':'0' );
  cout << endl;

  for(int i=0; i<primelen; i++)
    cout << prime[i] << ( (i%10==9)? '\n':' ' );
  cout << endl;
}

#endif
