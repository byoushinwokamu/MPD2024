#ifndef _CLOCKS_H_
#define _CLOCKS_H_

void SOSC_init_8MHz(void);
void SPLL_init_160MHz(void);
void NormalRUNMode_80MHz(void);
void LPIT0_init(void);
void delay_100ns(uint32_t ns);
void delay_ms(uint32_t ms);

#endif