#ifndef _GPIO_H_
#define _GPIO_H_

void printInteger(uint32_t n);
void set7segmentNumClear(void);
void set7segmentNum0(void);
void set7segmentNum1(void);
void set7segmentNum2(void);
void set7segmentNum3(void);
void set7segmentNum4(void);
void set7segmentNum5(void);
void set7segmentNum6(void);
void set7segmentNum7(void);
void set7segmentNum8(void);
void set7segmentNum9(void);
void set7segmentNum(int num);
void displayDigitClear(void);
void displayDigit1(int num);
void displayDigit2(int num);
void displayDigit3(int num);

#define SWGPIO_PDDR GPIOC_PDDR
#define SWGPIO_PDIR GPIOC_PDIR
#define SEGGPIO_PDDR GPIOE_PDDR
#define SEGGPIO_PSOR GPIOE_PSOR
#define SEGGPIO_PCOR GPIOE_PCOR
#define SEGPORT_PSOR GPIOB_PSOR
#define SEGPORT_PCOR GPIOB_PCOR
#define SEGPORT_PDDR GPIOB_PDDR

// SW define
#define SW1_PIN PTC8
#define SW2_PIN PTC9
#define SW3_PIN PTC16
#define SW4_PIN PTC17

// 7segment define
#define SEGA_PIN PTE3
#define SEGB_PIN PTE4
#define SEGC_PIN PTE5
#define SEGD_PIN PTE12
#define SEGE_PIN PTE14
#define SEGF_PIN PTE15
#define SEGG_PIN PTE16

#define SEGPORT1_PIN PTB14
#define SEGPORT2_PIN PTB13
#define SEGPORT3_PIN PTB16

#endif