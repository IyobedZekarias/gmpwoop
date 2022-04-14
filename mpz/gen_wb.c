#include "gmp-impl.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define false 0
#define true 1
typedef int bool;
typedef __uint128_t ll;

ll mulmod(ll a, ll b, ll m)
{ // It returns true if number is prime otherwise false {
    ll x = 0, y = a % m;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            x = (x + y) % m;
        }
        y = (y * 2) % m;
        b /= 2;
    }
    return x % m;
}

ll modulo(ll base, ll e, ll m)
{
    ll x = 1;
    ll y = base;
    while (e > 0)
    {
        if (e % 2 == 1)
            x = (x * y) % m;
        y = (y * y) % m;
        e = e / 2;
    }
    return x % m;
}

bool Miller(uint64_t p, int iteration)
{
    if (p < 2)
    {
        return false;
    }
    if (p != 2 && p % 2 == 0)
    {
        return false;
    }
    ll s = p - 1;
    while (s % 2 == 0)
    {
        s /= 2;
    }
    for (int i = 0; i < iteration; i++)
    {
        ll a = rand() % (p - 1) + 1, temp = s;
        ll mod = modulo(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0)
        {
            return false;
        }
    }
    return true;
}

mp_limb_t
mpz_gen_woopbase()
{
    #if WOOPING
    mp_limb_t r;
    FILE *fp;
    fp = fopen("/dev/urandom", "r");
    size_t ret = fread(&r, 4, 1, fp);
    fclose(fp);

    if (!(r & 1))
        r += 1;

    while (true)
    {
        if (Miller(r, 40) == true)
            break;
        else
            r += 2;
    }

    return r;
    #else 
    return 0; 
    #endif
}
