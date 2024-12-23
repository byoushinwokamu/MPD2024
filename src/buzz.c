#include "common.h"

void LPIT1_init(void) {
  // LPIT Clocking
  PCC_LPIT &= ~((0b111) << PCS_BITS);
  PCC_LPIT |= ((0b110) << PCS_BITS);
  PCC_LPIT |= (1 << CGC_BIT);

  // LPIT Initialization
  LPIT_MCR |= (1 << M_CEN_BIT);          // enable module clk
  LPIT_MIER |= (1 << TIE1_BIT);          // timer interrupt enable for ch1`
  LPIT_TVAL1 = 40000;                    // ch0 timeout period
  LPIT_TCTRL1 &= ~((0b11) << MODE_BITS); // 32bit counter mode
  LPIT_TCTRL1 |= (1 << T_EN_BIT);        // timer channel enable
}

volatile uint32_t lpit1_duration;
volatile uint8_t buzzstat;
void LPIT1_setT(uint32_t ms) { lpit1_duration = ms * 40000; }
void LPIT1_start(void) {
  beep_on(), buzzstat = 1, LPIT_TCTRL1 |= (1 << T_EN_BIT);
}
void LPIT1_stop(void) { LPIT_TCTRL1 &= ~(1 << T_EN_BIT); }

void LPIT0_Ch1_IRQHandler(void) {
  // update_motor_direction(0);
  if (buzzstat) {
    buzzstat = 0;
    beep_off();
  } else {
    buzzstat = 1;
    beep_on();
  }
  LPIT_TVAL1 = lpit1_duration;
  LPIT_MSR |= (1 << TIF1_BIT);
}

void FTM2_init(void) {
  // PTE20 ALT3 = FTM2_CH0
  PORTD_PCR0 &= ~((0b111) << MUX_BITS);
  PORTD_PCR0 |= ((0b100) << MUX_BITS); // ALT3 = 0b011

  // FTM2 클럭 인가, PCS=0b010 (SPLL_DIV2등 사용), CGC=1
  PCC_FTM2 &= ~(1 << CGC_BIT);
  PCC_FTM2 &= ~((0b111) << PCS_BITS);
  PCC_FTM2 |= ((0b010) << PCS_BITS);
  PCC_FTM2 |= (1 << CGC_BIT);

  // Prescale=128 (0b111)
  FTM2_SC = 0;
  FTM2_SC |= (0b111 << PS_BITS); // PS=128
  FTM2_CNTIN = 0;

  // MSB=1, ELSB=1 => Edge-Aligned PWM, High true
  FTM2_C0SC = (1 << MSB_BIT) | (1 << ELSB_BIT);

  // 내부 시스템 클록 사용 (CLKS=0b01)
  FTM2_SC &= ~((0b11) << CLKS_BITS);
  FTM2_SC |= (0b01 << CLKS_BITS);
  beep_off();
}

void beep_on(void) { FTM2_SC &= ~(1 << PWMEN0_BIT); }
void beep_off(void) { FTM2_SC |= (1 << PWMEN0_BIT); }