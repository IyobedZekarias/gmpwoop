/* mpz_init() -- Make a new multiple precision number with value 0.

Copyright 1991, 1993-1995, 2000-2002, 2012, 2015 Free Software
Foundation, Inc.

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

mp_limb_t mpz_initwb(mp_limb_t base, mpz_ptr x) __GMP_NOTHROW
{
  #if WOOPING
  mpz_init(x);
  if (!base)
  {
    base = mpz_gen_woopbase();
  }
  WOOP(x) = 0;
  WOOPB(x) = base;
  return base;
  #else
  return 0;
  #endif
}

void
mpz_init (mpz_ptr x) __GMP_NOTHROW
{
  static const mp_limb_t dummy_limb=0xc1a0;
  ALLOC (x) = 0;
  PTR (x) = (mp_ptr) &dummy_limb;
  SIZ (x) = 0;
  #if WOOPING
  WOOP(x) = 0; 
  WOOPB(x) = mpz_gen_woopbase(); 
  #endif
}
