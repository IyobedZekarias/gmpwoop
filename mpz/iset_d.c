/* mpz_init_set_d(integer, val) -- Initialize and assign INTEGER with a double
   value VAL.

Copyright 1996, 2000, 2001, 2012, 2015 Free Software Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of either:

  * the GNU Lesser General Public License as published by the Free
    Software Foundation; either version 3 of the License, or (at your
    option) any later version.

or

  * the GNU General Public License as published by the Free Software
    Foundation; either version 2 of the License, or (at your option) any
    later version.

or both in parallel, as here.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received copies of the GNU General Public License and the
GNU Lesser General Public License along with the GNU MP Library.  If not,
see https://www.gnu.org/licenses/.  */

#include "gmp-impl.h"

mp_limb_t mpz_initwb_set_d(mp_limb_t base, mpz_ptr dest, double val)
{
  #if WOOPING
  if (!base)
    base = mpz_gen_woopbase();

  mpz_init_set_d(dest, val);

  WOOP(dest) = mpz_get_woopval(PTR(dest), SIZ(dest), base);
  WOOPB(dest) = base;
  return base;
  #else
  return 0; 
  #endif
}

void
mpz_init_set_d (mpz_ptr dest, double val)
{
  static const mp_limb_t dummy_limb=0xc1a0;

  ALLOC (dest) = 0;
  SIZ (dest) = 0;
  PTR (dest) = (mp_ptr) &dummy_limb;
  mpz_set_d (dest, val);
  #if WOOPING
  WOOPB(dest) = mpz_gen_woopbase(); 
  WOOP(dest) = mpz_get_wv(dest); 
  #endif
}
