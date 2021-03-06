/*===-- mempcpy.c ---------------------------------------------------------===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===*/

#include <stdlib.h>

void *mempcpy(void *destaddr, void const *srcaddr, size_t len) {
  char *dest = (char *)destaddr;
  char const *src = (char *)srcaddr;

  while (len-- > 0)
    *dest++ = *src++;
  return dest;
}
