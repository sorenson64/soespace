#ifndef _FACTORLIST
#define _FACTORLIST

#include<cstdint>
#include<vector>

class Factorlist
{
  public:
  uint64_t list;

  Factorlist(): list(0) {}

  inline void add(uint32_t p, int bitlen)
  // adds the prime p to the list
  // p must be <= than all primes already in the list
  // bitlen is the number of bits in p's binary representation (eg. 3 if p=5)
  {
    list <<= bitlen-1;
    list = list | (p>>1);
  }

  static int bitlength(uint32_t x)
  {
    int len=0;
    while((1ul<<len) < x) len++;
    return len;
  }

  void add(uint32_t p) { return add(p,bitlength(p)); }
  // computing the bitlen once and saving it is much faster

  void getlist(uint64_t n, vector<uint64_t> & plist)
  {
    plist.clear();

    // is n even? 2 is not in list
    if((n&1ul)==0) 
    {
      plist.push_back(2); n>>=1; 
      while((n&1ul)==0) n>>=1;
    }
    // handle case when list==0
    // then n is either a power of 2, or prime, or 2^e*p for a large p
    if(list==0) { if(n>1) plist.push_back(n); return; }

    int64_t listcopy=list;
    int32_t p;
    while(listcopy!=0)
    {
      for(int bitlen=1; ; bitlen++)
      {
        uint64_t mask;
        mask=(1ul<<bitlen)-1;
        p=listcopy & mask;
        p=(p<<1)+1; // put back the trailing 1 bit
        if(p>1 && n%p==0)
        {
          plist.push_back(p); n=n/p;
          while(n%p==0) n=n/p;
          listcopy >>= bitlen;
          break;
        }
      }
    }
    if(n>1) plist.push_back(n);
  }
};

#endif
