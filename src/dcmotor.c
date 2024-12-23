#include "common.h"

uint8_t motor_dir;

void FTM0_init_PWM(void) {
  PCC_FTM0 &= ~(1 << CGC_BIT);
  PCC_FTM0 &= ~((0b111) << PCS_BITS);
  PCC_FTM0 |= (0b010 << PCS_BITS);
  PCC_FTM0 |= (1 << CGC_BIT);

  // Prescale=2
  FTM0_SC |= (1 << PWMEN0_BIT) | (1 << PWMEN1_BIT);
  FTM0_SC &= ~((0b111) << PS_BITS);
  FTM0_SC |= (0b001 << PS_BITS);

  FTM0_MOD = 16000 - 1;
  FTM0_CNTIN = 0;

  // CH0, CH1 Edge-aligned, HIGH-true
  FTM0_C0SC = (1 << MSB_BIT) | (1 << ELSB_BIT);
  FTM0_C1SC = (1 << MSB_BIT) | (1 << ELSB_BIT);
  // FTM0_C0SC = (1 << MSB_BIT);
  // FTM0_C1SC = (1 << MSB_BIT);
  // FTM0_C0SC &= ~(1 << ELSB_BIT);
  // FTM0_C1SC &= ~(1 << ELSB_BIT);

  FTM0_C0V = 0;
  FTM0_C1V = 0;

  // System clock 사용
  FTM0_SC &= ~((0b11) << CLKS_BITS);
  FTM0_SC |= (0b01 << CLKS_BITS);
}

void set_motor_direction(int dir) {
  if (dir == 0) {
    // 정방향: CH0=Low, CH1=PWM
    // CH0: PTD15 Low
    DCIN1_PCR &= ~((0b111) << MUX_BITS);
    // DCIN1_PCR |= (1 << MUX_BITS); // GPIO

    // CH1: PTD16 PWM
    DCIN2_PCR &= ~((0b111) << MUX_BITS);
    DCIN2_PCR |= ((0b010) << MUX_BITS); // ALT2 = FTM0_CH1
  } else {
    // 역방향: CH0=PWM, CH1=Low
    // CH0: PTD15 PWM
    DCIN1_PCR &= ~((0b111) << MUX_BITS);
    DCIN1_PCR |= ((0b010) << MUX_BITS); // ALT2 = FTM0_CH1

    // CH1: PTD16 Low
    DCIN2_PCR &= ~((0b111) << MUX_BITS);
    // DCIN2_PCR |= (1 << MUX_BITS); // GPIO
  }
}

void L9110_init(void) {
  motor_dir = 0;
  set_motor_direction(motor_dir);
}

void toggle_motor_dir(void) {
  motor_dir = !motor_dir;
  set_motor_direction(motor_dir);
}

void update_motor_direction(uint8_t dir) {
  motor_dir = dir;
  set_motor_direction(dir);
}

void update_motor_speed(uint32_t adc_val) {
  // adc_val:0~4095
  // 듀티 = (adc_val * 16000) / 4096 ≈ adc_val * 약3.9
  // adc_val 커질수록 듀티 증가(정방향일 때 속도 증가)
  adc_val *= 3;
  adc_val /= 4;
  adc_val += 1024;
  adc_val *= 16000;
  adc_val >>= 12;
  uint32_t cnv = 16000 - adc_val;
  FTM0_C0V = cnv;
  FTM0_C1V = cnv;
  // direction에 따라 실제 PWM 핀은 CH0 또는 CH1
}