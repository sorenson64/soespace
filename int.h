#ifndef _INT
#define _INT

// Integer utility routines and type definitions

#include<cstdint>
#include<cmath>
#include<cstdint>

#include "bigint.h"

using namespace std;

// types

typedef int16_t int16;
typedef int32_t int32;
typedef uint64_t uint64;
typedef int64_t int64;
typedef char bit;
// we have int128 from bigint.h


const int primeslen = 168;
const int16 primesmax = 1000;
const int16 primes[] = {
   2,   3,   5,   7,  11,  13,  17,  19,  23,  29,
  31,  37,  41,  43,  47,  53,  59,  61,  67,  71,
  73,  79,  83,  89,  97, 101, 103, 107, 109, 113,
 127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
 179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
 283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
 353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
 419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
 467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
 547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
 607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
 661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
 739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
 811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
 877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
 947, 953, 967, 971, 977, 983, 991, 997
};

// testing for squares
bool issquare(int64 x)
{
  int64 root = (int64) llroundl(sqrtl((long double)x));
  return (root*root == x);
}

// GCD and inverse functions
int64 gcd(int64 x, int64 y)
{
  if(x<0) x= -x; if(y<0) y= -y;
  int64 r;
  while(y!=0) { r=x%y; x=y; y=r; }
  return x;
}

inline int64 lcm(int64 a, int64 b)
  { return (a/gcd(a,b))*b; }

int64 extgcd(int64 a, int64 b, int64 &x, int64 &y)
{
  int64 ux=1,uy=0,vx=0,vy=1,u=a,v=b,r,rx,ry,q;
  int64 asign=1, bsign=1;
  if(a<0) { a=-a; asign=-1; }
  if(b<0) { b=-b; bsign=-1; }
  while(v>0)
  {
    q=u/v; r=u-q*v;
    rx=ux-q*vx; ux=vx; vx=rx;  ry=uy-q*vy; uy=vy; vy=ry; 
    u=v; v=r;
  }
  x=asign*ux; y=bsign*uy;
  return u;
}

// returns the inverse of x modulo m
int64 inv(int64 x, int64 m)
{
  int64 a,b,g;
  g=extgcd(x%m,m,a,b);
  if(g!=1) return 0;
  if(a>0 && a<m) return a;
  if(a>0) return a%m;
  if(a>-m) return m+a;
  return m-((-a)%m);
}

// modular exponentiation: 32 and 64-bit versions

int32 powmod(int32 xin, int32 e, int32 m)
{
  int64 y=1;
  int64 x=xin;
  while(e>0)
  {
    if(e%2==1) y=(y*x)%m; // if e is odd
    e >>= 1;  // e = e/2
    x = (x*x)%m;
  }
  return (int32)y;
}

int64 powmod(int64 xin, int64 e, int64 m)
{
  int128 y=1;
  int128 x=xin;
  while(e>0)
  {
    if(e%2==1) y=(y*x)%m; // if e is odd
    e >>= 1;  // e = e/2
    x = (x*x)%m;
  }
  return (int64)y;
}

inline int16 legendre(int32 a, int32 p)
  { return powmod(a, (p-1)/2, p); }
inline int16 legendre(int64 a, int64 p)
  { return powmod(a, (p-1)/2, p); }

#endif
