#ifndef _DC_H_
#define _DC_H_

void FTM0_init_PWM(void);
void set_motor_direction(int dir);
void L9110_init(void);
void toggle_motor_dir(void);
void update_motor_direction(uint8_t dir);
void update_motor_speed(uint32_t adc_val);

#define DCIN1_BASE GPIOD_BASE
#define DCIN1_PSOR *((volatile unsigned *)(DCIN1_BASE + 0x4))
#define DCIN1_PCOR *((volatile unsigned *)(DCIN1_BASE + 0x8))
#define DCIN1_PDDR *((volatile unsigned *)(DCIN1_BASE + 0x14))
#define DCIN1_PIN PTD15
#define DCIN1_PCR PORTD_PCR15

#define DCIN2_BASE GPIOD_BASE
#define DCIN2_PSOR *((volatile unsigned *)(DCIN2_BASE + 0x4))
#define DCIN2_PCOR *((volatile unsigned *)(DCIN2_BASE + 0x8))
#define DCIN2_PDDR *((volatile unsigned *)(DCIN2_BASE + 0x14))
#define DCIN2_PIN PTD16
#define DCIN2_PCR PORTD_PCR16

#endif
