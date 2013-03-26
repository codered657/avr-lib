// This file contains functions to work with prime numbers and factors

// Prevent duplicate loadings
#ifndef __FACTOR__
#define __FACTOR__

#include <math.h>
#include <vector>
#include "typedefs.h"

using namespace std;

// returns true/false if a number is prime or not
bool is_prime(const ulong num)
{
    // handle negatives, 0, and 1
    if (num <= 1) {return false;}
    // handle division by 2 separately
    if (!(num & 1)) {return false;}
    // handle remaining possibilities for factors
    for (int i = 3; i <= sqrt((double)num); i+=2)    {if (num % i == 0) {return false;}}
    // otherwise is prime
    return true;
}

// Computes Euler's totient formula, number of relatively coprime numbers
ulong euler_totient(ulong num, vector<ulong>& p_fact)
{
    for (uint i = 0; i < p_fact.size(); i++)  {num /= p_fact[i]; num *= p_fact[i]-1;}
    return num;
}

// returns the first prime greater than the given number
ulong next_prime(ulong num)
{
    num += (num & 1) + 1;  // Adds 1 to even, 2 to odd to start search
    while (!is_prime(num))  {num += 2;} // Search for prime
    return num;
}

// takes number, populates p_fact with prime factors and mult with multiplicities
// OVERLOADED FUNCTION, can be called without mult vector
// buggy????
void prime_factor(ulong num, vector<ulong>& p_fact, vector<uint>& mult)
{
    // reset lists
    p_fact.clear();
    mult.clear();
    // allocate counters
    ulong curr_num = num;
    ulong curr_factor = 3;
    ulong sqrt_num;
    uint idx = 0;
    // handle 2 separately
    if (curr_num % 2 == 0)
    {
        p_fact.push_back(2);
        mult.push_back(1);
        curr_num /= 2; // remove first 2 factor
        // handle remaining 2 factors
        while (curr_num % 2 == 0)
        {
            curr_num /= 2;
            mult[0]++;
        }
        idx++; // ensure indexing correctly
    }
    // handle remaining factors
    sqrt_num = (ulong)sqrt(double(num));
    while (curr_num != 1)
    {
        // found new factor
        if (curr_num % curr_factor == 0)
        {
            p_fact.push_back(curr_factor);
            mult.push_back(1);
            curr_num /= curr_factor;
            // handle multiplicites
            while (curr_num % curr_factor == 0)
            {
                curr_num /= curr_factor;
                mult[idx]++;
            }
            idx++;
            sqrt_num = (ulong)sqrt(double(curr_num));
        }
        else if (curr_factor > sqrt_num)
        {
            p_fact.push_back(curr_num);
            curr_num = 1;
            mult.push_back(1);
        }
        else    {curr_factor += 2;}
    }
    // nothing to return
    return;
}

// takes number, populates p_fact with prime factors and mult with multiplicities
// OVERLOADED FUNCTION, can be called with mult vector
void prime_factor(ulong num, vector<ulong>& p_fact)
{
    // reset list
    p_fact.clear();
    // allocate counters
    ulong curr_num = num;
    ulong curr_factor = 3;
    ulong sqrt_num;
    // handle 2 separately
    if ((curr_num & 1) == 0)
    {
        p_fact.push_back(2);
        curr_num /= 2; // remove first 2 factor
        // handle remaining 2 factors
        while ((curr_num & 1) == 0)   {curr_num >>= 1;}
    }
    // handle remaining factors
    sqrt_num = (ulong)sqrt(double(num));
    while (curr_num != 1)
    {
        // found new factor
        if (curr_num % curr_factor == 0)
        {
            p_fact.push_back(curr_factor);
            curr_num /= curr_factor;
            // handle multiplicites
            while (curr_num % curr_factor == 0) {curr_num /= curr_factor;}
            sqrt_num = (ulong)sqrt(double(curr_num));
        }
        else if (curr_factor > sqrt_num)
        {
            p_fact.push_back(curr_num);
            curr_num = 1;
        }
        else    {curr_factor += 2;}
    }
    // nothing to return
    return;
}

// returns the total possible factors for a number
int num_factor(ulong num, vector<ulong>& p_fact, vector<uint>& mult)
{
    prime_factor(num, p_fact, mult);
    uint ans = 1;
    for (uint i = 0; i < mult.size(); i++) {ans *= mult[i] + 1;}
    return ans;
}

void factors(const ulong num, vector<ulong>& fact_list)
{
    // reset list
    fact_list.clear();
    // initialize lists and iteration
    fact_list.push_back(1);
    ulong max_check = (ulong)sqrt(double(num));
    ulong curr_fact = 2;
    // populate first half of factors
    while (curr_fact < max_check+1)
    {
        if (num % curr_fact == 0)   {fact_list.push_back(curr_fact);}
        curr_fact++;
    }
    // set up number of factors
    int j = fact_list.size();
    // correct for square numbers
    j = ((fact_list[j-1]*fact_list[j-1] == num) ? j-1 : j);
    // populate second half
    for (int i = j-1; i > 0; i--) {fact_list.push_back(num/fact_list[i]);}
    fact_list.push_back(num);
    // end
    return;
}

vector<ulong> abundent_num(const ulong max_num)
{
    // Allocate fact_list array and reserve space
    vector<ulong> fact_list;
    vector<ulong> abun_list;
    fact_list.reserve(512);

    ulong sum;
    for (ulong num = 1; num < max_num; num++)
    {
        // obtain factors
        factors(num, fact_list);
        // sum factors and obtain new list
        sum = 0;
        for (uint i = 0; i < fact_list.size()-1; i++) {sum += fact_list[i];}
        if (sum > num) {abun_list.push_back(num);}
    }

    return abun_list;
}

#endif //__FACTOR__