/* set the woop base for an mpz

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
#include <stdio.h>

mp_limb_t mpz_set_woopbase(mp_limb_t a, mpz_ptr b) __GMP_NOTHROW
{
  #if WOOPING
  if (!a)
    a = mpz_gen_woopbase();
  WOOPB(b) = a;
  return a;
  #else
  return 0;
#endif
}
