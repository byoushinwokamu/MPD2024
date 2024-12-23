#ifndef _ULTRA_H_
#define _ULTRA_H_

uint32_t read_ultrasonic(void);

#define UECHO_BASE GPIOD_BASE
#define UECHO_PDIR *((volatile unsigned *)(UECHO_BASE + 0x10))
#define UECHO_PDDR *((volatile unsigned *)(UECHO_BASE + 0x14))
#define UECHO_PIN PTD1

#define UTRIG_BASE GPIOD_BASE
#define UTRIG_PSOR *((volatile unsigned *)(UTRIG_BASE + 0x4))
#define UTRIG_PCOR *((volatile unsigned *)(UTRIG_BASE + 0x8))
#define UTRIG_PDDR *((volatile unsigned *)(UTRIG_BASE + 0x14))
#define UTRIG_PIN PTD10

#endif