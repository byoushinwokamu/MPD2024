#ifndef _BUZZ_H_
#define _BUZZ_H_

void LPIT1_init(void);
void LPIT1_setT(uint32_t ms);
void LPIT1_start(void);
void LPIT1_stop(void);
void LPIT0_Ch1_IRQHandler(void);
void FTM2_init(void);
void beep_on(void);
void beep_off(void);

#endif