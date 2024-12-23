#include "common.h"

void PORT_init(void);
void NVIC_init_IRQs(void);
void textmask(int pos, int len, char *s);
char lcdtext[33] = "                                ";

int main(void) {
  // clock configuration
  SOSC_init_8MHz();
  SPLL_init_160MHz();
  NormalRUNMode_80MHz();

  LPIT0_init();
  PORT_init();
  LCD_init();      // 1602A LCD
  L9110_init();    // DC Motor
  FTM0_init_PWM(); // DC Motor
  FTM2_init();     // Buzzer
  ADC0_init();     // Variable resistor
  NVIC_init_IRQs();

  int state = 0;
  uint32_t adcval = 0;

  GPIOD_PSOR |= (1 << PTD0);

  // final
#define EMER_DURA 15000
  volatile enum { P, R, N, D } gear = P;
  volatile uint32_t velocity = 0;
  volatile uint32_t accel = 0;
  volatile uint32_t back_dist = 10000;
  volatile uint8_t emer_flag = 0;
  volatile uint32_t emer_cnt = EMER_DURA;
  textmask(0, 14, "Flow Different");
  textmask(16, 7, "Parking");
  textmask(31, 1, "P");
  LCD_writestring(lcdtext);
  LPIT1_init();

#define CYCLE 80
  for (uint32_t cnt = CYCLE;; cnt--) {
    if (emer_flag) {
      while (emer_cnt--) {
        printInteger(0);
      }
      emer_cnt = EMER_DURA;
      emer_flag = 0;
      gear = P;
      LPIT1_stop(), beep_off();
      textmask(16, 7, "Parking");
      textmask(31, 1, "P");
      LCD_writestring(lcdtext);
    }

    if (!cnt)
      cnt = CYCLE; //, update_motor_direction(1);
    // Gear Button Polling
    if (gear != P && !(SWGPIO_PDIR & (1 << SW1_PIN))) {
      // PARKING
      gear = P;
      LPIT1_stop(), beep_off();
      textmask(16, 7, "Parking");
      textmask(31, 1, "P");
      LCD_writestring(lcdtext);

    } else if (gear != R && !(SWGPIO_PDIR & (1 << SW2_PIN))) {
      // REVERSE
      gear = R;
      update_motor_direction(1);
      LPIT1_setT(500), LPIT1_start();
      textmask(16, 7, "Reverse");
      textmask(31, 1, "R");
      LCD_writestring(lcdtext);

    } else if (gear != N && !(SWGPIO_PDIR & (1 << SW3_PIN))) {
      // NEUTRAL
      gear = N;
      LPIT1_stop(), beep_off();
      textmask(16, 7, "Neutral");
      textmask(31, 1, "N");
      LCD_writestring(lcdtext);

    } else if (gear != D && !(SWGPIO_PDIR & (1 << SW4_PIN))) {
      // DRIVING
      gear = D;
      update_motor_direction(0);
      LPIT1_stop(), beep_off();
      textmask(16, 7, "Driving");
      textmask(31, 1, "D");
      LCD_writestring(lcdtext);
    }

    // ADC read & update motor speed
    adc_start();
    adcval = read_adc_chx();
    if (gear == R || gear == D)
      update_motor_speed(adcval), velocity = adcval * 120 >> 12;
    else
      update_motor_speed(0), velocity = 0;

    // Ultrasonic
    if (gear == R && cnt == 1) {
      // sound && emergency
      back_dist = read_ultrasonic();
      if (back_dist > 12000)
        LPIT1_setT(500);
      else if (back_dist > 8000)
        LPIT1_setT(300);
      else if (back_dist > 5000)
        LPIT1_setT(150);
      else if (back_dist > 1500)
        LPIT1_setT(60);
      else {
        update_motor_speed(0);
        LCD_writestring(" EMRGENCY BREAK  EMRGENCY BREAK");
        LPIT1_setT(1);
        emer_flag = 1;
      }
    }

    // 7seg
    printInteger(velocity);
  }

  return 0;
}

void NVIC_init_IRQs(void) {
  NVIC_ICPR1 |= (1 << (49 % 32));
  NVIC_ISER1 |= (1 << (49 % 32));
  NVIC_IPR49 = 10;
}

void PORT_init(void) {
  PCC_PORTB |= (1 << CGC_BIT);
  PCC_PORTC |= (1 << CGC_BIT);
  PCC_PORTD |= (1 << CGC_BIT);
  PCC_PORTE |= (1 << CGC_BIT);

  /* ========== LCD ========== */
  // LCD data pins
  PORTB_PCR8 &= ~(0b111 << MUX_BITS);
  PORTB_PCR8 |= (1 << MUX_BITS);
  PORTB_PCR9 &= ~(0b111 << MUX_BITS);
  PORTB_PCR9 |= (1 << MUX_BITS);
  PORTB_PCR10 &= ~(0b111 << MUX_BITS);
  PORTB_PCR10 |= (1 << MUX_BITS);
  PORTB_PCR11 &= ~(0b111 << MUX_BITS);
  PORTB_PCR11 |= (1 << MUX_BITS);
  GPIOB_PDDR |= (1 << PTB8 | 1 << PTB9 | 1 << PTB10 | 1 << PTB11);

  // LCD control pins
  PORTB_PCR3 &= ~(0b111 << MUX_BITS);
  PORTB_PCR3 |= (1 << MUX_BITS);
  PORTB_PCR4 &= ~(0b111 << MUX_BITS);
  PORTB_PCR4 |= (1 << MUX_BITS);
  PORTB_PCR5 &= ~(0b111 << MUX_BITS);
  PORTB_PCR5 |= (1 << MUX_BITS);
  GPIOB_PDDR |= (1 << PTB3 | 1 << PTB4 | 1 << PTB5);

  /* ========== SW ========== */
  // SW1
  PORTC_PCR12 &= ~(0b111 << MUX_BITS);
  PORTC_PCR12 |= (1 << MUX_BITS);
  GPIOC_PDDR &= ~(1 << PTC12);
  // SW2
  PORTC_PCR13 &= ~(0b111 << MUX_BITS);
  PORTC_PCR13 |= (1 << MUX_BITS);
  GPIOC_PDDR &= ~(1 << PTC13);

  /* ========== DC MOTOR ========== */
  // DCIN1_PDDR |= (1 << DCIN1_PIN);
  // DCIN1_PCOR |= (1 << DCIN1_PIN);
  // DCIN2_PDDR |= (1 << DCIN2_PIN);
  // DCIN2_PCOR |= (1 << DCIN2_PIN);

  /* ========== ULTRASONIC ========== */
  PORTD_PCR10 &= ~(0b111 << MUX_BITS);
  PORTD_PCR10 |= (1 << MUX_BITS);
  GPIOD_PCOR |= (1 << UTRIG_PIN);
  GPIOD_PDDR |= (1 << UTRIG_PIN);

  PORTD_PCR1 &= ~(0b111 << MUX_BITS);
  PORTD_PCR1 |= (1 << MUX_BITS);
  GPIOD_PDDR &= ~(1 << UECHO_PIN);

  /* ========== Switch ========== */
  PORTC_PCR8 &= ~(0b111 << MUX_BITS);
  PORTC_PCR8 |= (1 << MUX_BITS);
  PORTC_PCR9 &= ~(0b111 << MUX_BITS);
  PORTC_PCR9 |= (1 << MUX_BITS);
  PORTC_PCR16 &= ~(0b111 << MUX_BITS);
  PORTC_PCR16 |= (1 << MUX_BITS);
  PORTC_PCR17 &= ~(0b111 << MUX_BITS);
  PORTC_PCR17 |= (1 << MUX_BITS);
  SWGPIO_PDDR &= ~(1 << SW1_PIN | 1 << SW2_PIN | 1 << SW3_PIN | 1 << SW4_PIN);

  /* ========== 7-Segment ========== */
  PORTB_PCR14 &= ~(0b111 << MUX_BITS);
  PORTB_PCR14 |= (1 << MUX_BITS);
  PORTB_PCR13 &= ~(0b111 << MUX_BITS);
  PORTB_PCR13 |= (1 << MUX_BITS);
  PORTB_PCR16 &= ~(0b111 << MUX_BITS);
  PORTB_PCR16 |= (1 << MUX_BITS);
  GPIOB_PDDR |= (1 << SEGPORT1_PIN | 1 << SEGPORT2_PIN | 1 << SEGPORT3_PIN);

  PORTE_PCR3 &= ~(0b111 << MUX_BITS);
  PORTE_PCR3 |= (1 << MUX_BITS);
  PORTE_PCR4 &= ~(0b111 << MUX_BITS);
  PORTE_PCR4 |= (1 << MUX_BITS);
  PORTE_PCR5 &= ~(0b111 << MUX_BITS);
  PORTE_PCR5 |= (1 << MUX_BITS);
  PORTE_PCR12 &= ~(0b111 << MUX_BITS);
  PORTE_PCR12 |= (1 << MUX_BITS);
  PORTE_PCR14 &= ~(0b111 << MUX_BITS);
  PORTE_PCR14 |= (1 << MUX_BITS);
  PORTE_PCR15 &= ~(0b111 << MUX_BITS);
  PORTE_PCR15 |= (1 << MUX_BITS);
  PORTE_PCR16 &= ~(0b111 << MUX_BITS);
  PORTE_PCR16 |= (1 << MUX_BITS);
  GPIOE_PDDR |= (1 << SEGA_PIN | 1 << SEGB_PIN | 1 << SEGC_PIN | 1 << SEGD_PIN |
                 1 << SEGE_PIN | 1 << SEGF_PIN | 1 << SEGG_PIN);
}

void textmask(int pos, int len, char *s) {
  uint8_t i;
  for (i = 0; i < len; i++)
    lcdtext[i + pos] = s[i];
}