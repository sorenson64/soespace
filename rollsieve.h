#include "int.h"
#include "stack.h"
#include<cmath>

class Rollsieve
{
  stack *T;
  int32 delta;
  const int32 Tmaxsize=(int32)1e6;

  int64 n, s;
  int32 pos, r;

  public:

  void init(int64 start)
  { // two cases, start<=1000, or start>1000
    if(start<2) start=2;
    int32 sqrtstart = (int64) sqrtl((long double) start);
    r=sqrtstart+1; s=r*r;
    delta=r+2;
    pos=0; n=start;

    T=new stack[Tmaxsize];
    for(int i=0; i<delta; i++) T[i].makeempty();

    // small primes first
    for(int i=0; i<primeslen && primes[i]<=sqrtstart; i++)
    {
      int32 p=primes[i];
      int32 j=(p-(start%p))%p;
      T[j].push(p);
    }
    // now large primes
    if(sqrtstart>primesmax)
    {
      Rollsieve R(primesmax);
      int32 p=R.nextprime();
      while(p<=sqrtstart)
      {
        int32 j=(p-(start%p))%p;
        T[j].push(p);
        p=R.nextprime();
      }
    }
  }

  Rollsieve(int64 start) { init(start); }

  ~Rollsieve()
    { if(T!=0) delete [] T; }

  bool next()
  {
    bool isprime=true;
    while(!T[pos].isempty())
    {
      int32 p=T[pos].pop();
      T[(pos+p)%delta].push(p);
      isprime=false;
    }
    if(n==s)
    {
      if(isprime)
      {
        isprime=false;
        T[(pos+r)%delta].push(r);
      }
      r++; s=r*r;
    }
    n++; pos=(pos+1)%delta;
    if(pos==0) { delta+=2; T[delta-1].makeempty(); T[delta-2].makeempty(); }
    return isprime;
  }
  
  int64 nextprime()
  {
    while(!next()); return n-1;
  }

};
