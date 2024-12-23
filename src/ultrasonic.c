#include "common.h"

uint32_t read_ultrasonic(void) {
  uint32_t t = 0;
  uint32_t out = 80;

  UTRIG_PSOR |= (1 << UTRIG_PIN);
  while (out--)
    ;
  UTRIG_PCOR |= (1 << UTRIG_PIN);

  out = 10000;
  while (!(UECHO_PDIR & (1 << UECHO_PIN)) && out--)
    ;

  if (!out)
    return (1U << 31) - 1;

  out = 10000;
  while ((UECHO_PDIR & (1 << UECHO_PIN)) && out--)
    t++;

  if (!out)
    return (1U << 31) - 1;

  return t;
}