#include "common.h"

void ADC0_init(void) {
  PCC_ADC0 &= ~(1 << CGC_BIT);
  PCC_ADC0 &= ~((0b111) << PCS_BITS);
  PCC_ADC0 |= ((0b001) << PCS_BITS);
  PCC_ADC0 |= (1 << CGC_BIT);

  ADC0_SC1A |= ((0b111111) << ADCH_BITS);
  ADC0_CFG1 &= ~((0b11) << ADIV_BITS);
  ADC0_CFG1 &= ~((0b11) << MODE_BITS);
  ADC0_CFG1 |= ((0b01) << MODE_BITS); // 12bit resolution
  ADC0_CFG2 &= ~(255 << SMPLTS_BITS);
  ADC0_CFG2 |= (12 << SMPLTS_BITS);
  ADC0_SC2 &= ~(1 << ADTRG_BIT);
}

void adc_start(void) {
  ADC0_SC1A &= ~((0b111111) << ADCH_BITS);
  ADC0_SC1A |= (ADC0_SE4 << ADCH_BITS);
}

uint32_t read_adc_chx(void) {
  while ((ADC0_SC1A & (1 << COCO_BITS)) == 0)
    ;
  return ADC0_RA;
}
