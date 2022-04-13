#include <iostream>
#include "gmp.h"
#include "gmp-impl.h"
#include <chrono>

using namespace std;
using namespace chrono;

int main(int argc, char **argv)
{
    mpz_t a; 
    mpz_init(a);
    mpz_set_str(a, "283479283784984758749387682739719875849872384798725", 10);

    cout << WOOPB(a) << endl;
    cout << WOOP(a) << endl;

    return 0;
}