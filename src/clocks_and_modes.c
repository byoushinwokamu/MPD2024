#include "common.h"

void SOSC_init_8MHz(void) {
  SCG->SOSCDIV = SCG_SOSCDIV_SOSCDIV1(1) | SCG_SOSCDIV_SOSCDIV2(1);
  SCG->SOSCCFG = SCG_SOSCCFG_RANGE(2) | SCG_SOSCCFG_EREFS_MASK;
  while (SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK)
    ;
  SCG->SOSCCSR = SCG_SOSCCSR_SOSCEN_MASK;
  while (!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK))
    ;
}

void SPLL_init_160MHz(void) {
  while (SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK)
    ;
  SCG->SPLLCSR &= ~SCG_SPLLCSR_SPLLEN_MASK;
  SCG->SPLLDIV |= SCG_SPLLDIV_SPLLDIV1(2) | SCG_SPLLDIV_SPLLDIV2(3);
  SCG->SPLLCFG = SCG_SPLLCFG_MULT(24);
  while (SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK)
    ;
  SCG->SPLLCSR |= SCG_SPLLCSR_SPLLEN_MASK;
  while (!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK))
    ;
}

void NormalRUNMode_80MHz(void) {
  SCG->SIRCDIV = SCG_SIRCDIV_SIRCDIV1(1) | SCG_SIRCDIV_SIRCDIV2(1);
  SCG->RCCR = SCG_RCCR_SCS(6) | SCG_RCCR_DIVCORE(0b01) | SCG_RCCR_DIVBUS(0b01) |
              SCG_RCCR_DIVSLOW(0b10);
  while (((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT) != 6)
    ;
}

void LPIT0_init(void) {
  // LPIT Clocking
  PCC_LPIT &= ~((0b111) << PCS_BITS);
  PCC_LPIT |= ((0b110) << PCS_BITS);
  PCC_LPIT |= (1 << CGC_BIT);

  // LPIT Initialization
  LPIT_MCR |= (1 << M_CEN_BIT); // enable module clk
  // LPIT_MIER |= (1 << TIE0_BIT);          // timer interrupt enable for ch0
  LPIT_TVAL0 = 40000;                    // ch0 timeout period
  LPIT_TCTRL0 &= ~((0b11) << MODE_BITS); // 32bit counter mode
  LPIT_TCTRL0 |= (1 << T_EN_BIT);        // timer channel enable
}

void delay_100ns(uint32_t ns) {
  LPIT_TVAL0 = ns * 4;
  LPIT_MCR |= (1 << M_CEN_BIT); // enable module clk
  while (0 == (LPIT_MSR & (1 << TIF0_BIT)))
    ;
  LPIT_MSR |= (1 << TIF0_BIT);
}

void delay_ms(uint32_t ms) {
  LPIT_TVAL0 = ms * 40000;
  LPIT_MCR |= (1 << M_CEN_BIT); // enable module clk
  while (0 == (LPIT_MSR & (1 << TIF0_BIT)))
    ;
  LPIT_MSR |= (1 << TIF0_BIT);
}