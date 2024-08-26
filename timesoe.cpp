#include<iostream>
#include"soe.h"

#include<ctime>

using namespace std;

int main()
{
  uint64_t x1,x2,numprimes=0,numdivs=0;
  uint32_t delta;

  x2=(uint64_t)1e16;
  x1=(uint64_t)(x2-1e9);

  uint32_t deltalist[]={ 1ul<<21, 1ul<<23, 1ul<<25, 1ul<<27 };
  int deltalistlen=4;


  for(int d=0; d<deltalistlen; d++)
  {

  delta=deltalist[d];

  //cout << "x1 = "<<x1;
  //cout << "  x2 = "<<x2;
  //cout << "  delta = "<<delta << endl;
  cout << delta << " & \t";

    double starttime=clock();
    soe_plain(x1,x2,delta, numprimes, numdivs);
    double stoptime=clock();

    //cout << "PLAIN: ";
    //cout <<"Time in sec: " << (stoptime-starttime)/CLOCKS_PER_SEC; // << endl;
    //cout << "  # of primes   = "<<numprimes; // << endl;
    //cout << "  # of divisors = "<<numdivs << endl;
    cout << (stoptime-starttime)/CLOCKS_PER_SEC << " & \t";


    starttime=clock();
    soe_fact(x1,x2,delta, numprimes, numdivs);
    stoptime=clock();

    //cout << "FACT: ";
    //cout <<"Time in sec: " << (stoptime-starttime)/CLOCKS_PER_SEC; // << endl;
    //cout << "  # of primes   = "<<numprimes; // << endl;
    //cout << "  # of divisors = "<<numdivs << endl;
    cout << (stoptime-starttime)/CLOCKS_PER_SEC << " & \t";


    starttime=clock();
    soe_cp(x1,x2,delta, numprimes, numdivs);
    stoptime=clock();

    //cout << "CP: ";
    //cout <<"Time in sec: " << (stoptime-starttime)/CLOCKS_PER_SEC; // << endl;
    //cout << "  # of primes   = "<<numprimes; // << endl;
    //cout << "  # of divisors = "<<numdivs << endl;
    cout << (stoptime-starttime)/CLOCKS_PER_SEC << " & \t";

    starttime=clock();
    soe_all(x1,x2,delta, numprimes, numdivs);
    stoptime=clock();

    //cout << "ALL: ";
    //cout <<"Time in sec: " << (stoptime-starttime)/CLOCKS_PER_SEC; // << endl;
    //cout << "  # of primes   = "<<numprimes; // << endl;
    //cout << "  # of divisors = "<<numdivs << endl;
    cout << (stoptime-starttime)/CLOCKS_PER_SEC << "\\\\" << endl;

  }
  
  return 0;
}

