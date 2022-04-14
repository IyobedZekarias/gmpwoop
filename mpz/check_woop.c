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
#include <stdio.h>
#include "longlong.h"

void mpz_check_woop(mpz_ptr a){
  #if WOOPING
  mp_limb_t checked_woop_val = WOOP(a); 
  mp_limb_t generated_woop_val = mpz_get_woopval(PTR(a), SIZ(a), WOOPB(a));
  if(checked_woop_val != generated_woop_val){
    printf("WOOP() %lu\nget_wv() %lu\n", checked_woop_val, generated_woop_val);
    FILE *stream = stdout; 
    int base = 10; 
        mp_ptr xp;
    mp_size_t x_size = SIZ(a);
    unsigned char *str;
    size_t str_size;
    size_t i;
    size_t written;
    const char *num_to_text;
    TMP_DECL;

    if (stream == 0)
      stream = stdout;

    num_to_text = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    if (base > 1)
    {
      if (base <= 36)
        num_to_text = "0123456789abcdefghijklmnopqrstuvwxyz";
      else if (UNLIKELY(base > 62))
        return;
    }
    else if (base > -2)
    {
      base = 10;
    }
    else
    {
      base = -base;
      if (UNLIKELY(base > 36))
        return;
    }

    written = 0;

    if (x_size < 0)
    {
      fputc('-', stream);
      x_size = -x_size;
      written = 1;
    }

    TMP_MARK;

    DIGITS_IN_BASE_PER_LIMB(str_size, x_size, base);
    str_size += 3;
    str = (unsigned char *)TMP_ALLOC(str_size);

    xp = PTR(a);
    if (!POW2_P(base))
    {
      xp = TMP_ALLOC_LIMBS(x_size | 1); /* |1 in case x_size==0 */
      MPN_COPY(xp, PTR(a), x_size);
    }

    str_size = mpn_get_str(str, base, xp, x_size);

    /* Convert result to printable chars.  */
    for (i = 0; i < str_size; i++)
      str[i] = num_to_text[str[i]];
    str[str_size] = 0;

    {
      size_t fwret;
      fwret = fwrite((char *)str, 1, str_size, stream);
      written += fwret;
    }

    TMP_FREE;
    printf("\n%lu\n%lu\n\n", WOOPB(a), WOOP(a));
  }
  ASSERT_ALWAYS(checked_woop_val == generated_woop_val);
  #endif
}
