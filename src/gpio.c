#include "common.h"

void printInteger(uint32_t n) {
#define FLICKER 600
  uint16_t a = FLICKER;

  displayDigitClear();
  displayDigit1(n % 10);
  while (a--)
    ;
  a = FLICKER;
  displayDigitClear();
  displayDigit2(n / 10 % 10);
  while (a--)
    ;
  a = FLICKER;
  displayDigitClear();
  displayDigit3(n / 100);
  while (a--)
    ;
  a = FLICKER;
  displayDigitClear();
}

void set7segmentNumClear() {
  SEGGPIO_PCOR |= (1 << SEGA_PIN) | (1 << SEGB_PIN) | (1 << SEGC_PIN) |
                  (1 << SEGD_PIN) | (1 << SEGE_PIN) | (1 << SEGF_PIN) |
                  (1 << SEGG_PIN);
}

void set7segmentNum0() {
  SEGGPIO_PSOR |= (1 << SEGA_PIN) | (1 << SEGB_PIN) | (1 << SEGC_PIN) |
                  (1 << SEGD_PIN) | (1 << SEGE_PIN) | (1 << SEGF_PIN);
  SEGGPIO_PCOR |= (1 << SEGG_PIN);
}

void set7segmentNum1() {
  SEGGPIO_PSOR |= (1 << SEGB_PIN) | (1 << SEGC_PIN);
  SEGGPIO_PCOR |= (1 << SEGA_PIN) | (1 << SEGD_PIN) | (1 << SEGE_PIN) |
                  (1 << SEGF_PIN) | (1 << SEGG_PIN);
}

void set7segmentNum2() {
  SEGGPIO_PSOR |= (1 << SEGA_PIN) | (1 << SEGB_PIN) | (1 << SEGD_PIN) |
                  (1 << SEGG_PIN) | (1 << SEGE_PIN);
  SEGGPIO_PCOR |= (1 << SEGC_PIN) | (1 << SEGF_PIN);
}

void set7segmentNum3() {
  SEGGPIO_PSOR |= (1 << SEGA_PIN) | (1 << SEGB_PIN) | (1 << SEGC_PIN) |
                  (1 << SEGD_PIN) | (1 << SEGG_PIN);
  SEGGPIO_PCOR |= (1 << SEGE_PIN) | (1 << SEGF_PIN);
}

void set7segmentNum4() {
  SEGGPIO_PSOR |=
      (1 << SEGB_PIN) | (1 << SEGC_PIN) | (1 << SEGF_PIN) | (1 << SEGG_PIN);
  SEGGPIO_PCOR |= (1 << SEGA_PIN) | (1 << SEGD_PIN) | (1 << SEGE_PIN);
}

void set7segmentNum5() {
  SEGGPIO_PSOR |= (1 << SEGA_PIN) | (1 << SEGC_PIN) | (1 << SEGD_PIN) |
                  (1 << SEGF_PIN) | (1 << SEGG_PIN);
  SEGGPIO_PCOR |= (1 << SEGB_PIN) | (1 << SEGE_PIN);
}
//
void set7segmentNum6() {
  SEGGPIO_PSOR |= (1 << SEGC_PIN) | (1 << SEGD_PIN) | (1 << SEGE_PIN) |
                  (1 << SEGF_PIN) | (1 << SEGG_PIN);
  SEGGPIO_PCOR |= (1 << SEGA_PIN) | (1 << SEGB_PIN);
}

void set7segmentNum7() {
  SEGGPIO_PSOR |= (1 << SEGA_PIN) | (1 << SEGB_PIN) | (1 << SEGC_PIN);
  SEGGPIO_PCOR |=
      (1 << SEGD_PIN) | (1 << SEGE_PIN) | (1 << SEGF_PIN) | (1 << SEGG_PIN);
}
void set7segmentNum8() {
  SEGGPIO_PSOR |= (1 << SEGA_PIN) | (1 << SEGB_PIN) | (1 << SEGC_PIN) |
                  (1 << SEGD_PIN) | (1 << SEGE_PIN) | (1 << SEGF_PIN) |
                  (1 << SEGG_PIN);
}
void set7segmentNum9() {
  SEGGPIO_PSOR |= (1 << SEGA_PIN) | (1 << SEGB_PIN) | (1 << SEGC_PIN) |
                  (1 << SEGD_PIN) | (1 << SEGF_PIN) | (1 << SEGG_PIN);
  SEGGPIO_PCOR |= (1 << SEGE_PIN);
}

void set7segmentNum(int num) {
  switch (num) {
  case 0:
    set7segmentNum0();
    break;
  case 1:
    set7segmentNum1();
    break;
  case 2:
    set7segmentNum2();
    break;
  case 3:
    set7segmentNum3();
    break;
  case 4:
    set7segmentNum4();
    break;
  case 5:
    set7segmentNum5();
    break;
  case 6:
    set7segmentNum6();
    break;
  case 7:
    set7segmentNum7();
    break;
  case 8:
    set7segmentNum8();
    break;
  case 9:
    set7segmentNum9();
    break;
  default:
    set7segmentNumClear();
  }
}

void displayDigitClear() {
  set7segmentNumClear();
  SEGPORT_PCOR |=
      (1 << SEGPORT1_PIN) | (1 << SEGPORT2_PIN) | (1 << SEGPORT3_PIN);
}

void displayDigit1(int num) {
  SEGPORT_PSOR |= (1 << SEGPORT1_PIN);
  set7segmentNum(num);
}

void displayDigit2(int num) {
  SEGPORT_PSOR |= (1 << SEGPORT2_PIN);
  set7segmentNum(num);
}

void displayDigit3(int num) {
  SEGPORT_PSOR |= (1 << SEGPORT3_PIN);
  set7segmentNum(num);
}