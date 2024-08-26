#ifndef _C_PRIMES
#define _C_PRIMES

#include<iostream>
#include<vector>
#include"int.h"
#include"bigint.h"
#include"rollsieve.h"

using namespace std;

class CPrimes
{
  public:
  int64_t pstart;
  int64_t pstop;
  vector<unsigned char> halfgaps;
  int64_t hglen;

  CPrimes(int64_t start, int64_t stop)
  {
    if(start<3) start=3;
    Rollsieve R(start);
    pstart=R.nextprime();
    hglen=0;
    int64_t pprev=pstart,p;
    while((p=R.nextprime())<=stop)
    {
      //halfgaps[hglen++]=(p-pprev)/2;
      halfgaps.push_back((p-pprev)/2); hglen++;
      pprev=p;
    }
    pstop=pprev;
  }

  inline uint16_t gap(int i) { return ((uint16_t)halfgaps[i])<<1; }

};

#endif
