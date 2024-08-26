#include<iostream>
#include"cprimes.h"

int main()
{
  CPrimes cp(3,1000);
  cout << 2 << endl << 3 << endl;
  int p=3;
  for(int i=0; i<cp.hglen; i++)
    cout << (p+=cp.gap(i)) << endl;
  return 0;
}
