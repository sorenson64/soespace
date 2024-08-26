# soespace
Code for paper on Reducing the Space Used by the Sieve of Eratosthenes when Factoring

FILES
soe.h - sieve of Eratosthenes code
factorlist2.h - for storing prime divisors of each integer in a segment
cprimes.h - for storing a list of primes up to the square root using differences/gaps
rollsieve.h - code from Jon's LMS article on incremental sieves from 2015
*.cpp - main programs for testing and timing
run.* - output files
other *.h files - various utility files borrowed from other projects

TO COMPILE
g++ -O2 timesoe.cpp

this code was written for Linux
