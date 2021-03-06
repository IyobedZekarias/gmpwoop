/* mpz_roinit_n -- Initialize mpz with read-only limb array.

Copyright 2013 Free Software Foundation, Inc.

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

#if WOOPING
mpz_srcptr
mpz_roinit_n (mpz_ptr x, mp_srcptr xp, mp_size_t xs, mp_limb_t woopbase)
#else
mpz_srcptr
mpz_roinit_n (mpz_ptr x, mp_srcptr xp, mp_size_t xs)
#endif
{
  mp_size_t xn = ABS(xs);
  MPN_NORMALIZE (xp, xn);

  ALLOC (x) = 0;
  SIZ (x) = xs < 0 ? -xn : xn;
  PTR (x) = (mp_ptr) xp;
  #if WOOPING
  WOOPB(x) = woopbase; 
  WOOP(x) = mpz_get_wv(x); 
  #endif
  return x;
}
