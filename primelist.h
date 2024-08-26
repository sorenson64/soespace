#ifndef _PRIMELIST
#define _PRIMELIST

#include<iostream>
#include<vector>
#include<cstdint>
// #include "int.h"

using namespace std;

// makes list of primes potentially up to 2^32

vector<bool> isprime; // we are expecting bit packing here
vector<uint32_t> prime;

uint32_t primelen; // length of prime array
uint32_t maxprime; // largest prime found

void makeprimelist(uint64_t limit=0xFFFFFFFF)
// default limit is all 32-bit primes
{
  isprime.clear();
  isprime.resize(limit+1,true);
  isprime[0]=isprime[1]=false;
  // sieve of Eratosthenes
  prime.clear();
  uint64_t q;
  for(q=2; q*q<=limit; q++) 
    if(isprime[q])
    {
      prime.push_back(q);
      for(int64_t x=2*q; x<=limit; x+=q) isprime[x]=false;
    }
  for( ; q<=limit; q++) 
    if(isprime[q]) prime.push_back(q);
  //prime.shrink_to_fit();
  maxprime=prime.back();
  primelen=prime.size();
}

void testprimelist()
{
  makeprimelist(1000);

  for(int i=0; i<isprime.size(); i++)
    cout << ( isprime[i]?'1':'0' );
  cout << endl;

  for(int i=0; i<primelen; i++)
    cout << prime[i] << ( (i%10==9)? '\n':' ' );
  cout << endl;

  // now testing 2^32.  Takes about a minute on my desktop.

  makeprimelist();
  cout << maxprime << endl;
  cout << primelen << endl;
  // should print out 4294967291, pi(2^32)=203280221

}

#endif
