#ifndef _SOE
#define _SOE

// versions:
// plain 
// factorlist
// cprimes
// factorlist and cprimes

#include"cprimes.h"
#include"factorlist2.h" // the good version
#include"stack.h"
#include"primelist.h"

bool docounts=true;

void soe_seg_plain(uint64_t x1, uint64_t x2, 
                   const vector<uint32_t> & smallprimes,
  /* outputs */    uint64_t & primecount, uint64_t & divisorcount)
{
  uint32_t delta=x2-x1;  // x1<= n < x2
  vector<stack> x(delta);

  // initialize all entries to empty
  for(int i=0; i<delta; i++) x[i].makeempty();

  // main loop to write down primes
  for(int j=0; j<smallprimes.size(); j++)
  {
    uint32_t p=smallprimes[j];
    uint64_t q0=x1+(p-(x1%p))%p;
    for(uint64_t q=q0; q<x2; q+=p) x[q-x1].push(p);
  }

  // count things
  if(docounts){
  for(uint64_t n=x1; n<x2; n++)
  {
    int xpos=n-x1;
    if(x[xpos].isempty()) // n is prime
      { primecount++; divisorcount++; }
    else
    {
       uint64_t n0=n;
       uint32_t p;
       while(!x[xpos].isempty())
       {
         p=x[xpos].pop();
         divisorcount++;
         if(p==n) {primecount++;}
         while(n0%p==0) n0=n0/p;
       }
       if(n0>1) divisorcount++;
    }
  }
  }
}

void soe_plain(uint64_t x1, uint64_t x2, uint32_t delta,
  /* outputs */    uint64_t & primecount, uint64_t & divisorcount)
{
  makeprimelist(sqrt(x2)+1);
  primecount=divisorcount=0;
  for(uint64_t start=x1; start<x2; start+=delta)
  {
    uint64_t stop=start+delta;
    if(stop>x2) stop=x2;
    soe_seg_plain(start, stop, prime, primecount, divisorcount);
  }
}

//** Factorlist version

void soe_seg_fact(uint64_t x1, uint64_t x2, 
                   const vector<uint32_t> & smallprimes,
  /* outputs */    uint64_t & primecount, uint64_t & divisorcount)
{
  uint32_t delta=x2-x1;  // x1<= n < x2
  vector<Factorlist2> x(delta);

  // initialize all entries to empty
  for(int i=0; i<delta; i++) x[i].makeempty();

  // main loop to write down primes
  int bitlen=0;
  for(int j=1; j<smallprimes.size(); j++)  // skip 2, so j=1 to start
  {
    uint32_t p=smallprimes[j];
    //int bitlen=Factorlist2::bitlength(p);
    while((1ul<<bitlen)<p) bitlen++;
    uint64_t q0=x1+(p-(x1%p))%p;
    for(uint64_t q=q0; q<x2; q+=p) x[q-x1].push(p,bitlen);
  }

  // count things
  if(docounts){
  for(uint64_t n=x1; n<x2; n++)
  {

//cout << n <<"=";
    int xpos=n-x1;
    if(x[xpos].isempty() && n&((uint64_t)1)==1) // n is prime, n is odd
      { primecount++; divisorcount++; } //cout << n << endl; }
    else
    {
       uint64_t n0=n;
       uint32_t p;
       // handle p=2 separately
       if(n%2==0) // n is even
       {
         divisorcount++;
         if(n==2) primecount++;
         while(n0%2==0) { n0=n0/2; } // cout << 2 <<" "; }
       }
       // now for odd primes p
       while(!x[xpos].isempty())
       {
         p=x[xpos].pop();
         divisorcount++;
         if(p==n) {primecount++;}
         while(n0%p==0) { n0=n0/p; } //  cout << p <<" "; }
       }
       if(n0>1) { divisorcount++;  } // cout << n0; }
//cout << endl;
    }
  }
  }
}

void soe_fact(uint64_t x1, uint64_t x2, uint32_t delta,
  /* outputs */    uint64_t & primecount, uint64_t & divisorcount)
{
  makeprimelist(sqrt(x2)+1);
  primecount=divisorcount=0;
  for(uint64_t start=x1; start<x2; start+=delta)
  {
    uint64_t stop=start+delta;
    if(stop>x2) stop=x2;
    soe_seg_fact(start, stop, prime, primecount, divisorcount);
  }
}

//** normal stack, compressed primes version

void soe_seg_cp(uint64_t x1, uint64_t x2, 
                   CPrimes & smallprimes,
  /* outputs */    uint64_t & primecount, uint64_t & divisorcount)
{
  uint32_t delta=x2-x1;  // x1<= n < x2
  vector<stack> x(delta);

  // initialize all entries to empty
  for(int i=0; i<delta; i++) x[i].makeempty();

  // main loops to write down primes
  // p=2
  for(uint64_t q=x1+(x1%2); q<x2; q+=2) x[q-x1].push(2);
  // p=3
  uint32_t p=3;
  uint64_t q0=x1+(p-(x1%p))%p;
  for(uint64_t q=q0; q<x2; q+=p) x[q-x1].push(p);
  // p=5,7,11, etc.
  for(int j=0; j<smallprimes.hglen; j++)
  {
    p=p+smallprimes.gap(j);
    uint64_t q0=x1+(p-(x1%p))%p;
    for(uint64_t q=q0; q<x2; q+=p) x[q-x1].push(p);
  }

  // count things
  if(docounts){
  for(uint64_t n=x1; n<x2; n++)
  {
    int xpos=n-x1;
    if(x[xpos].isempty()) // n is prime
      { primecount++; divisorcount++; }
    else
    {
       uint64_t n0=n;
       uint32_t p;
       while(!x[xpos].isempty())
       {
         p=x[xpos].pop();
         divisorcount++;
         if(p==n) {primecount++;}
         while(n0%p==0) n0=n0/p;
       }
       if(n0>1) divisorcount++;
    }
  }
  }
}

void soe_cp(uint64_t x1, uint64_t x2, uint32_t delta,
  /* outputs */    uint64_t & primecount, uint64_t & divisorcount)
{
  CPrimes cp(3,sqrt(x2)+1);
  primecount=divisorcount=0;
  for(uint64_t start=x1; start<x2; start+=delta)
  {
    uint64_t stop=start+delta;
    if(stop>x2) stop=x2;
    soe_seg_cp(start, stop, cp, primecount, divisorcount);
  }
}

//** BOTH compressed primes and factorlist

void soe_seg_all(uint64_t x1, uint64_t x2, 
                   CPrimes & smallprimes,
  /* outputs */    uint64_t & primecount, uint64_t & divisorcount)
{
  uint32_t delta=x2-x1;  // x1<= n < x2
  vector<Factorlist2> x(delta);

  // initialize all entries to empty
  for(int i=0; i<delta; i++) x[i].makeempty();

  // main loops to write down primes
  // p=2 -- skip 2!
  //for(uint64_t q=x1+(x1%2); q<x2; q+=2) x[q-x1].push(2);
  // p=3
  uint32_t p=3;
  uint64_t q0=x1+(p-(x1%p))%p;
  // 3's bitlength is 2
  for(uint64_t q=q0; q<x2; q+=p) x[q-x1].push(3,2);
  // p=5,7,11, etc.
  int bitlen=0;
  for(int j=0; j<smallprimes.hglen; j++)
  {
    p=p+smallprimes.gap(j);
    //int bitlen=Factorlist2::bitlength(p);
    while((1ul<<bitlen)<p) bitlen++;
    uint64_t q0=x1+(p-(x1%p))%p;
    for(uint64_t q=q0; q<x2; q+=p) x[q-x1].push(p,bitlen);
  }

  // count things
  if(docounts){
  for(uint64_t n=x1; n<x2; n++)
  {

//cout << n <<"=";
    int xpos=n-x1;
    if(x[xpos].isempty() && n&((uint64_t)1)==1) // n is prime, n is odd
      { primecount++; divisorcount++; } //cout << n << endl; }
    else
    {
       uint64_t n0=n;
       uint32_t p;
       // handle p=2 separately
       if(n%2==0) // n is even
       {
         divisorcount++;
         if(n==2) primecount++;
         while(n0%2==0) { n0=n0/2; } // cout << 2 <<" "; }
       }
       // now for odd primes p
       while(!x[xpos].isempty())
       {
         p=x[xpos].pop();
         divisorcount++;
         if(p==n) {primecount++;}
         while(n0%p==0) { n0=n0/p; } //  cout << p <<" "; }
       }
       if(n0>1) { divisorcount++;  } // cout << n0; }
//cout << endl;
    }
  }
  }
}

void soe_all(uint64_t x1, uint64_t x2, uint32_t delta,
  /* outputs */    uint64_t & primecount, uint64_t & divisorcount)
{
  CPrimes cp(3,sqrt(x2)+1);
  primecount=divisorcount=0;
  for(uint64_t start=x1; start<x2; start+=delta)
  {
    uint64_t stop=start+delta;
    if(stop>x2) stop=x2;
    soe_seg_all(start, stop, cp, primecount, divisorcount);
  }
}

#endif
