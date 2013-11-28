/* Copyright (C) 2000 MySQL AB

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

/*  File   : strnlen.c
    Author : Michael Widenius
    Updated: 20 April 1984
    Defines: strnlen.
    strnlen(s, len) returns the length of s or len if s is longer than len.
*/

#include <my_global.h>
#include "m_string.h"

/* sergey conflict on Linux_x86_64
#ifndef HAVE_STRNLEN

uint strnlen(register const char *s, register uint maxlen)
{
  const char *end= (const char *)memchr(s, '\0', maxlen);
  return end ? (uint) (end - s) : maxlen;
}

#endif
*/