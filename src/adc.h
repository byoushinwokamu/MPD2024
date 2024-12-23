#ifndef _ADC_H_
#define _ADC_H_

void ADC0_init(void);
void adc_start(void);
uint32_t read_adc_chx(void);

#define ADC_PIN PTB0

#endif