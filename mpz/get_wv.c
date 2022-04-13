/* Copyright 2000-2003, 2005, 2009, 2017 Free Software Foundation, Inc.

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

mp_limb_t mpz_get_wv(mpz_srcptr a){
  return mpz_get_woopval(PTR(a), SIZ(a), WOOPB(a));
}

mp_limb_t
mpz_get_woopval(mp_ptr a, long long size, mp_limb_t base)
{
  if(size == 0){
    return 0; 
  }
#if GMP_NUMB_BITS == 64
  __uint128_t numbbase = (__uint128_t)(UINT64_MAX) + 1;
  numbbase = numbbase % base; 
#else
#if GMP_NUMB_BITS == 32
  uint64_t numbbase = (uint64_t)(UINT32_MAX) + 1;
  numbbase = numbase % base; 
#endif
#endif
  long long sizeabs = size < 0 ? size * -1 : size;
  mp_limb_t s1;
  mp_limb_t val = a[sizeabs - 1] % base;

  for (long long i = sizeabs - 2; i >= 0; i--)
  {
    s1 = ((val % base) * (numbbase % base)) % base;
    val = (s1 + a[i]) % base;
  }

  if (size < 0)
  {
    val = base - val;
  }

  return val;
}
