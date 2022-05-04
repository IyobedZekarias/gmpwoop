/* Test mpz_add, mpz_sub, mpz_add_ui, mpz_sub_ui, and mpz_ui_sub.

Copyright 2002 Free Software Foundation, Inc.

This file is part of the GNU MP Library test suite.

The GNU MP Library test suite is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 3 of the License,
or (at your option) any later version.

The GNU MP Library test suite is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License along with
the GNU MP Library test suite.  If not, see https://www.gnu.org/licenses/.  */

#include <stdio.h>
#include <stdlib.h>

#include "gmp-impl.h"
#include "longlong.h"
#include "tests.h"

void debug_mp (mpz_t, int);
void dump_abort (int, const char *, mpz_t, mpz_t);

int
main (int argc, char **argv)
{
#if WOOPING
    mpz_t a, b, c, d, rseed, ans;
    mpz_initswb(0, a, b, c, d, ans, NULL);
    mpz_initwb(0, rseed);
    gmp_randstate_t r;

    // SUBTRACTION ---------------
    gmp_randinit_mt(r);

    mpz_set_str(rseed, "3874598374983743987582937423878754", 10);
    mpz_check_woop(rseed);

    gmp_randseed(r, rseed);

    mpz_urandomb(b, r, 5 * 64);
    mpz_urandomb(c, r, 5 * 64);
    mpz_urandomb(d, r, 5 * 64);
    mpz_urandomb(a, r, 5 * 64);

    mpz_check_woop(a);
    mpz_check_woop(b);
    mpz_check_woop(c);
    mpz_check_woop(d);

    mpz_add(ans, a, b);
    mpz_check_woop(ans);
    mpz_add(ans, c, d);
    mpz_check_woop(ans);

    printf("add passed\n"); 

    mpz_add_ui(ans, d, 2342123114); 
    mpz_check_woop(ans); 
    mpz_sub_ui(ans, d, 2384982); 
    mpz_check_woop(ans);

    printf("add ui passed\n");

    mpz_neg(ans, ans);
    mpz_check_woop(ans); 
    mpz_neg(ans, ans); 
    mpz_check_woop(ans);

    printf("neg passed\n");

    mpz_addmul(ans, b, c);
    mpz_check_woop(ans);
    mpz_submul(ans, b, c); 
    mpz_check_woop(ans);
    mpz_addmul_ui(ans, d, 12314123214);
    mpz_check_woop(ans);
    mpz_submul_ui(ans, d, 1231241231343233423);
    mpz_check_woop(ans); 

    printf("addmul passed\n");

    // mpz_neg(a, a);
    // mpz_check_woop(a); 
    // mpz_abs(ans, a);
    // mpz_check_woop(ans);

    // printf("abs passed\n");

    mpz_mul(ans, a, b);
    mpz_check_woop(ans);
    printf("mul passed\n");

    mpz_mul_ui(ans, a, 3243423435);
    mpz_check_woop(ans); 

    printf("mului passed\n");

    mpz_nextprime(ans, d);
    mpz_check_woop(ans);

    printf("nextprime passed\n");

    mpz_mul_2exp(ans, ans, 45);
    mpz_check_woop(ans);

    printf("mul2exp passed\n");

    mpz_mod(ans, c, d);
    mpz_check_woop(ans);
    mpz_mod_ui(ans, c, 123);
    mpz_check_woop(ans);
    mpz_mod_2exp(ans, c, 231);
    mpz_check_woop(ans);

    printf("mod functions passed\n");

    mpz_set_str(a, "9872304987049587209384750298743897938479280719438752039487508970298374509287345874398023984752", 10);
    mpz_set_str(b, "2", 10);

    mpz_divexact(ans, a, b);
    mpz_check_woop(ans); 

    mpz_divexact_ui(ans, a, 2);
    mpz_check_woop(ans);

    printf("divexact passed\n");
#else 
    return 1; 
#endif
}