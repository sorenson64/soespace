#ifndef _FACTORLIST2
#define _FACTORLIST2

#include<cstdint>
#include<vector>

class Factorlist2
{
  public:
  static const int maxplen=15;
  uint64_t list;
  char plen;
  char ptr[maxplen];

  Factorlist2(): list(0), plen(0) {}

  inline void clear() { list=0; plen=0; }

  inline uint32_t get(int pos)
  { // assumes 0<=pos<plen
    int left;
    left= (pos>0)?ptr[pos-1]:0;
    uint64_t copy;
    copy=(list >> left);
    return (uint32_t)
      ((copy & ( (1ul<<(ptr[pos]-left) ) -1 ))<<1)|1ul;
  }

  inline int getbitlen(int pos)
  { // assumes 0<=pos<plen
    int left;
    left= (pos>0)?ptr[pos-1]:0;
    return ptr[pos]-left+1;
  }

  inline void add(uint32_t p, int bitlen)
  {
    int pos=plen;
    plen++;
    int left= (pos>0)?ptr[pos-1]:0;
    uint64_t pbits=(p>>1);
    list = list | (pbits<<left);
    ptr[pos]=left+bitlen-1;
  }

  inline void push(uint32_t p, int bitlen) { add(p,bitlen); }
  inline uint32_t pop() { return get( --plen ); }
  inline bool isempty() { return (plen==0); }
  inline uint32_t gettop() { return get(plen-1); }
  inline int gettopbitlen() { return getbitlen(plen-1); }
  inline void makeempty() { plen=0; }

  static int bitlength(uint32_t x)
  {
    int len=0;
    while((1ul<<len) < x) len++;
    return len;
  }

  inline void add(uint32_t p) { add(p,bitlength(p)); }

  void getlist(uint64_t n, vector<uint64_t> & plist)
  {
    plist.clear();

    // is n even? 2 is not in list
    if((n&1ul)==0) 
    {
      plist.push_back(2); n>>=1; 
      while((n&1ul)==0) n>>=1;
    }

    uint32_t p;
    for(int i=0; i<plen; i++)
    {
      p=get(i); 
      plist.push_back(p);
      while(n%p==0) n=n/p;
    }
    if(n>1) plist.push_back(n);
  }

};

#endif
