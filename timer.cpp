#include <iostream>
#include <iomanip>
#include "gmp.h"
#include <chrono>
#include <thread>
#include <unistd.h>

using namespace std;
using namespace chrono;

int go = 1;
mpz_t *ans = (mpz_t *)malloc(100 * sizeof(mpz_t));
mpz_t *op = (mpz_t *)malloc(100 * sizeof(mpz_t));
mpz_t tot, rem;

void sleeper(){
    sleep(6);
    go = 0;
}

void runner(int func, unsigned long long size)
{   
    int i = 0;
    auto start = high_resolution_clock::now();
    while(go){
        if (func == 0)
            mpz_sub(tot, ans[i % 100], op[i % 100]);
        else if(func == 1)
            mpz_add(tot, ans[i % 100], op[i % 100]);
        else if(func == 2)
            mpz_mul(tot, ans[i % 100], op[i % 100]);
        else if(func == 3)
            mpz_tdiv_qr(tot, rem, ans[i % 100], op[i%100]);
        i++;
    }
    auto stop = high_resolution_clock::now();
    #if WOOPING
        mpz_check_woop(tot);
    #endif

    auto duration = duration_cast<nanoseconds>(stop - start);
    if (func == 0)
        cout << "sub: \n";
    if (func == 1)
        cout << "add: \n";
    if (func == 2)
        cout << "mul: \n";
    if (func == 3)
        cout << "div: \n";
    cout << "    time: " << duration.count() / i << endl
         << "   count: " << i << endl;
}

void initvars(int size){
    go = 1; 
    mpz_t a;

#if WOOPING
    mp_limb_t wb = mpz_initwb(0, a);
#else
    mpz_init(a);
#endif

    gmp_randstate_t r;

    // SUBTRACTION ---------------
    gmp_randinit_mt(r);

    mpz_set_str(a, "3874598374983743987582937423878754", 10);

    gmp_randseed(r, a);
    mpz_init(rem);

#if WOOPING
    mp_limb_t wbt = mpz_initwb(0, tot);
    // mpz_initswb(0, ans, op, NULL);
    for (int il = 0; il < 100; il++)
    {
        mpz_initwb(wbt, ans[il]);
        mpz_initwb(wbt, op[il]);
        mpz_urandomb(ans[il], r, size);
        mpz_urandomb(op[il], r, size);
    }
#else
    mpz_init(tot);
    for (int il = 0; il < 100; il++)
    {
        mpz_init(ans[il]);
        mpz_init(op[il]);
        mpz_urandomb(ans[il], r, size);
        mpz_urandomb(op[il], r, size);
    }
#endif
}

void initvarsdiv(int size)
{
    go = 1;
    mpz_t a;

#if WOOPING
    mp_limb_t wb = mpz_initwb(0, a);
#else
    mpz_init(a);
#endif

    gmp_randstate_t r;

    // SUBTRACTION ---------------
    gmp_randinit_mt(r);

    mpz_set_str(a, "3874598374983743987582937423878754", 10);

    gmp_randseed(r, a);
    mpz_init(rem);

#if WOOPING
    mp_limb_t wbt = mpz_initwb(0, tot);
    // mpz_initswb(0, ans, op, NULL);
    for (int il = 0; il < 100; il++)
    {
        mpz_initwb(wbt, ans[il]);
        mpz_initwb(wbt, op[il]);
        mpz_urandomb(ans[il], r, size*3);
        mpz_urandomb(op[il], r, size);
    }
#else
    mpz_init(tot);
    for (int il = 0; il < 100; il++)
    {
        mpz_init(ans[il]);
        mpz_init(op[il]);
        mpz_urandomb(ans[il], r, size*3);
        mpz_urandomb(op[il], r, size);
    }
#endif
}

void runthreads(int size)
{
    initvars(size);
    thread run1(runner, 0, size);
    thread slp1(sleeper);
    run1.join(); 
    slp1.join();
    go = 1; 
    thread run2(runner, 1, size);
    thread slp2(sleeper);
    run2.join();
    slp2.join();
    go = 1; 
    thread run3(runner, 2, size);
    thread slp3(sleeper);
    run3.join();
    slp3.join();
    go = 1;
    initvarsdiv(size);
    thread run4(runner, 3, size);
    thread slp4(sleeper);
    run4.join();
    slp4.join();
    go = 1; 
}

int main(int argc, char **argv)
{
    #if WOOPING
    cout << "WOOPING" << endl;
#else
    cout << "NOT WOOPING" << endl;
    #endif
    int size; 
    cin >> size; 
    
    runthreads(size); 
}