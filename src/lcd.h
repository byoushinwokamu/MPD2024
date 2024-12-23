#ifndef LCD1602A_H_
#define LCD1602A_H_

typedef unsigned short uint16_t;

void LCD_init(void);
void LCD_op(uint16_t data);
void LCD_writechar(char data);
void LCD_writestring(char *str);
void LCD_clear(void);

// Control Pin Register
#define LCDRS_BASE GPIOB_BASE
#define LCDRS_PSOR *((volatile unsigned *)(LCDRS_BASE + 0x4))
#define LCDRS_PCOR *((volatile unsigned *)(LCDRS_BASE + 0x8))
#define LCDRS_PDDR *((volatile unsigned *)(LCDRS_BASE + 0x14))
#define LCDRS_PIN PTB5

#define LCDRW_BASE GPIOB_BASE
#define LCDRW_PSOR *((volatile unsigned *)(LCDRW_BASE + 0x4))
#define LCDRW_PCOR *((volatile unsigned *)(LCDRW_BASE + 0x8))
#define LCDRW_PDDR *((volatile unsigned *)(LCDRW_BASE + 0x14))
#define LCDRW_PIN PTB4

#define LCDEN_BASE GPIOB_BASE
#define LCDEN_PSOR *((volatile unsigned *)(LCDEN_BASE + 0x4))
#define LCDEN_PCOR *((volatile unsigned *)(LCDEN_BASE + 0x8))
#define LCDEN_PDDR *((volatile unsigned *)(LCDEN_BASE + 0x14))
#define LCDEN_PIN PTB3

#define LCDCODE_BASE GPIOB_BASE
#define LCDCODE_PSOR *((volatile unsigned *)(LCDCODE_BASE + 0x4))
#define LCDCODE_PCOR *((volatile unsigned *)(LCDCODE_BASE + 0x8))
#define LCDCODE_PDDR *((volatile unsigned *)(LCDCODE_BASE + 0x14))
#define LCDCODE_PIN PTB8

#endif
