#include "common.h"

#define LCD_enable() LCDEN_PSOR |= (1 << LCDEN_PIN)
#define LCD_disable() LCDEN_PCOR |= (1 << LCDEN_PIN)

void LCD_init(void) {
  // LCD function set 3 times
  LCD_op(0x28), delay_100ns(70000);
  LCD_op(0x28), delay_100ns(70000);
  LCD_op(0x28), delay_100ns(70000);

  // LCD off
  LCD_op(0x08), delay_100ns(700);

  // LCD clear
  LCD_op(0x01), delay_100ns(20000);

  // LCD Modeset
  LCD_op(0x06), delay_100ns(700);

  // LCD Display cursor
  LCD_op(0x0F), delay_100ns(20000);

  // DDRAM Address
  LCD_op(0x80), delay_100ns(700);

  // Return home
  LCD_op(0x02), delay_100ns(20000);
}

void LCD_op(uint16_t op) {
  uint16_t upper = (op & 0xF0) >> 4;
  uint16_t lower = (op & 0x0F);
  LCDRW_PCOR |= (1 << LCDRW_PIN);

  // transmit upper data
  LCD_enable();
  LCDCODE_PCOR |= (0x0F << LCDCODE_PIN);
  LCDCODE_PSOR |= (upper << LCDCODE_PIN);
  delay_100ns(5);
  LCD_disable();

  // clear
  delay_100ns(2);
  LCDCODE_PCOR |= (0x0F << LCDCODE_PIN);
  delay_100ns(30);

  // transmit lower data
  LCD_enable();
  LCDCODE_PCOR |= (0x0F << LCDCODE_PIN);
  LCDCODE_PSOR |= (lower << LCDCODE_PIN);
  delay_100ns(5);
  LCD_disable();

  // clear
  delay_100ns(2);
  LCDCODE_PCOR |= (0x0F << LCDCODE_PIN);
  LCDRS_PCOR |= (1 << LCDRS_PIN);
  delay_100ns(30);
}

void LCD_writechar(char ch) {
  uint16_t upper = (ch & 0xF0) >> 4;
  uint16_t lower = (ch & 0x0F);

  LCDRS_PSOR |= (1 << LCDRS_PIN);

  // transmit upper data
  LCD_enable();
  LCDCODE_PCOR |= (0x0F << LCDCODE_PIN);
  LCDCODE_PSOR |= (upper << LCDCODE_PIN);
  delay_100ns(5);
  LCD_disable();

  // clear
  delay_100ns(2);
  LCDCODE_PCOR |= (0x0F << LCDCODE_PIN);
  delay_100ns(30);

  // transmit lower data
  LCD_enable();
  LCDCODE_PCOR |= (0x0F << LCDCODE_PIN);
  LCDCODE_PSOR |= (lower << LCDCODE_PIN);
  delay_100ns(5);
  LCD_disable();

  // clear
  delay_100ns(2);
  LCDCODE_PCOR |= (0x0F << LCDCODE_PIN);
  LCDRS_PCOR |= (1 << LCDRS_PIN);
  delay_100ns(30);
}

void LCD_writestring(char *str) {
  uint8_t i = 0;
  LCD_op(0x01), delay_100ns(20000); // clear LCD
  LCD_op(0x80), delay_100ns(700);   // DDRAM: first line
  LCD_op(0x02), delay_100ns(20000); // return home

  delay_ms(10);

  // write first line
  for (i; str[i] != '\0' && i < 16; i++)
    LCD_writechar(str[i]), delay_100ns(500);
  if (str[i] == '\0')
    return;

  // DDRAM Address: second line
  LCD_op(0xC0), delay_100ns(400);

  // write second line
  for (i; str[i] != '\0'; i++)
    LCD_writechar(str[i]), delay_100ns(500);
}

void LCD_clear(void) {
  LCD_op(0x08); // lcd display off
  delay_ms(400);
  LCD_op(0x01); // Clear display
  delay_ms(200);
}