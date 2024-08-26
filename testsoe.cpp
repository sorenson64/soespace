#include<iostream>
#include"soe.h"

using namespace std;

int main()
{
  cout << "Enter x1: ";
  uint64_t x1,x2,numprimes=0,numdivs=0;
  uint32_t delta;
  cin >> x1;
  cout << "Enter x2: ";
  cin >> x2;
  cout << "Enter delta: ";
  cin >> delta;

  soe_plain(x1,x2,delta, numprimes, numdivs);

  cout << "# of primes = "<<numprimes << endl;
  cout << "# of divisors = "<<numdivs << endl;
  
  return 0;
}

