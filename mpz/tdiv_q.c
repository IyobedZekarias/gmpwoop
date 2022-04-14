/* mpz_tdiv_q -- divide two integers and produce a quotient.

Copyright 1991, 1993, 1994, 1996, 2000, 2001, 2005, 2010, 2012 Free Software
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
#include "longlong.h"

void
mpz_tdiv_q (mpz_ptr quot, mpz_srcptr num, mpz_srcptr den)
{
  mp_size_t ql;
  mp_size_t ns, ds, nl, dl;
  mp_ptr np, dp, qp, tp;
#if WOOPING
  mp_limb_t denwoop = WOOP(den);
  mp_limb_t numwoop = WOOP(num);
#endif
  TMP_DECL;

  ns = SIZ (num);
  ds = SIZ (den);
  nl = ABS (ns);
  dl = ABS (ds);
  ql = nl - dl + 1;

  if (UNLIKELY (dl == 0))
    DIVIDE_BY_ZERO;

  if (ql <= 0)
    {
      SIZ (quot) = 0;
      return;
    }

  qp = MPZ_REALLOC (quot, ql);

  TMP_MARK;
  dp = PTR (den);

  /* Copy denominator to temporary space if it overlaps with the quotient.  */
  if (dp == qp)
    {
      mp_ptr tp;
      tp = TMP_ALLOC_LIMBS (dl);
      MPN_COPY (tp, dp, dl);
      dp = tp;
    }

  tp = TMP_ALLOC_LIMBS (nl + 1);
  np = PTR (num);
  /* Copy numerator to temporary space if it overlaps with the quotient.  */
  if (np == qp)
    {
      MPN_COPY (tp, np, nl);
      /* Overlap dividend and scratch.  */
      np = tp;
    }
#if WOOPING
    static const mp_limb_t dummy_limb = 0xc1a0;
    mp_ptr rp = (mp_ptr)&dummy_limb;
    rp = TMP_ALLOC_LIMBS(dl);

    mpn_tdiv_qr(qp, rp, 0L, np, nl, dp, dl);
    MPN_NORMALIZE(rp, dl);
#else
    mpn_div_q(qp, np, nl, dp, dl, tp);
#endif

    ql -= qp[ql - 1] == 0;

    SIZ(quot) = (ns ^ ds) >= 0 ? ql : -ql;

#if WOOPING
    ASSERT(WOOPB(num) == WOOPB(den));
    WOOP(quot) = mpz_get_woopval(PTR(quot), SIZ(quot), WOOPB(num));
    WOOPB(quot) = WOOPB(num);
    long long sizer = ns >= 0 ? dl : -dl;
    mp_limb_t r = mpz_get_woopval(rp, sizer, WOOPB(num));
    // printf("test: %d\n", ((mp_limb_t)(((__uint128_t)WOOP(quot) * (__uint128_t)denwoop + (__uint128_t)r) % WOOPB(num)) == numwoop % WOOPB(num)));
#if GMP_LIMB_BITS == 64
    // if (!((mp_limb_t)(((__uint128_t)WOOP(quot) * (__uint128_t)denwoop + (__uint128_t)r) % WOOPB(num)) == numwoop % WOOPB(num))){
    //   printf("q: %lu\nr: %lu\nn: %lu\nd: %lu\nbase: %lu\n", WOOP(quot), r, numwoop, denwoop, WOOPB(num));
    // }
    ASSERT((mp_limb_t)(((__uint128_t)WOOP(quot) * (__uint128_t)denwoop + (__uint128_t)r) % WOOPB(num)) == numwoop % WOOPB(num));
#else
    ASSERT((mp_limb_t)(((uint64_t)WOOP(quot) * (uint64_t)denwoop + (uint64_t)r) % WOOPB(num)) == numwoop % WOOPB(num));
#endif
#endif
    TMP_FREE;
}
