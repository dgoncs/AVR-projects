#ifndef LIB_MACROS_H
#define LIB_MACROS_H

#define bitSet(r, n) (r |= (1 << n))
#define bitClear(r, n) (r &= (~(1 << n)))
#define bitToggle(r,n) (r ^= (1 << n))
#define bitRead(r, n) ((r & (1 << n)) >> n)

#endif
