#include<iostream>

using namespace std;

#include "factorlist2.h"

#include "smallprimes.h"

void binprint(uint64_t x)
{
  for(int i=63; i>=0; i--)
    cout << (((x&(1ul<<i))==0)?'0':'1');
}


const int PLIMIT=25;
const int LIMIT=PLIMIT*PLIMIT;
Factorlist2 x[LIMIT+1];

int main()
{
  makesmallprimes(PLIMIT);
  for(int i=prime.size()-1; i>0; i--)
  {
    int32_t p=prime[i];
    int bitlen=Factorlist2::bitlength(p);
    for(int j=p; j<=LIMIT; j=j+p)
      x[j].add(p,bitlen);
  }

  vector<uint64_t> flist;
  for(int i=1; i<=LIMIT; i++)
  {
    cout << i << ": ";
    cout << x[i].list << " ";
    binprint(x[i].list);
    cout.flush();
    x[i].getlist(i,flist);
    for(int j=0; j<flist.size(); j++)
      cout << " " << flist[j];
    cout << endl;
  }
  
}
