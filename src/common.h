#ifndef _COMMON_H_
#define _COMMON_H_

#include "S32K144.h"

#include "adc.h"
#include "buzz.h"
#include "clocks_and_modes.h"
#include "dcmotor.h"
#include "gpio.h"
#include "lcd.h"
#include "ultrasonic.h"

/* register address */
// PCC register
#define PCC_BASE (0x40065000)
#define PCC_LPIT *((volatile unsigned *)(PCC_BASE + 0xDC))
#define PCC_FTM0 *((volatile unsigned *)(PCC_BASE + 0xE0))
#define PCC_FTM2 *((volatile unsigned *)(PCC_BASE + 0xE8))
#define PCC_ADC0 *((volatile unsigned *)(PCC_BASE + 0xEC))
#define PCC_PORTA *((volatile unsigned *)(PCC_BASE + 0x124))
#define PCC_PORTB *((volatile unsigned *)(PCC_BASE + 0x128))
#define PCC_PORTC *((volatile unsigned *)(PCC_BASE + 0x12C))
#define PCC_PORTD *((volatile unsigned *)(PCC_BASE + 0x130))
#define PCC_PORTE *((volatile unsigned *)(PCC_BASE + 0x134))

#define PCS_BITS 24
#define CGC_BIT 30

// FTM0 Register
#define FTM0_BASE (0x40038000)
#define FTM0_SC *((volatile unsigned *)(FTM0_BASE + 0x0))
#define FTM0_MOD *((volatile unsigned *)(FTM0_BASE + 0x8))
#define FTM0_C0SC *((volatile unsigned *)(FTM0_BASE + 0xC))
#define FTM0_C0V *((volatile unsigned *)(FTM0_BASE + 0x10))
#define FTM0_C1SC *((volatile unsigned *)(FTM0_BASE + 0x14))
#define FTM0_C1V *((volatile unsigned *)(FTM0_BASE + 0x18))
#define FTM0_CNTIN *((volatile unsigned *)(FTM0_BASE + 0x4C))

// FTM2 Register
#define FTM2_BASE (0x4003A000)
#define FTM2_SC *((volatile unsigned *)(FTM2_BASE + 0x0))
#define FTM2_MOD *((volatile unsigned *)(FTM2_BASE + 0x8))
#define FTM2_C0SC *((volatile unsigned *)(FTM2_BASE + 0xC))
#define FTM2_C0V *((volatile unsigned *)(FTM2_BASE + 0x10))
#define FTM2_CNTIN *((volatile unsigned *)(FTM2_BASE + 0x4C))

#define PWMEN1_BIT 17
#define PWMEN0_BIT 16
#define PS_BITS 0
#define CLKS_BITS 3
#define MSB_BIT 5
#define ELSB_BIT 3

// ADC0 Register
#define ADC0_BASE (0x4003B000)
#define ADC0_SC1A *((volatile unsigned *)(ADC0_BASE + 0x0))
#define ADC0_CFG1 *((volatile unsigned *)(ADC0_BASE + 0x40))
#define ADC0_CFG2 *((volatile unsigned *)(ADC0_BASE + 0x44))
#define ADC0_RA *((volatile unsigned *)(ADC0_BASE + 0x48))
#define ADC0_SC2 *((volatile unsigned *)(ADC0_BASE + 0x90))
#define ADC0_SC3 *((volatile unsigned *)(ADC0_BASE + 0x94))

#define ADCH_BITS 0
#define COCO_BITS 7
#define MODE_BITS 2
#define ADIV_BITS 5
#define SMPLTS_BITS 0
#define ADTRG_BIT 6
#define ADC0_SE4 4

// LPIT Register
#define LPIT_BASE (0x40037000)
#define LPIT_MCR *((volatile unsigned *)(LPIT_BASE + 0x8))
#define LPIT_MSR *((volatile unsigned *)(LPIT_BASE + 0xC))
#define LPIT_MIER *((volatile unsigned *)(LPIT_BASE + 0x10))
#define LPIT_TVAL0 *((volatile unsigned *)(LPIT_BASE + 0x20))
#define LPIT_TCTRL0 *((volatile unsigned *)(LPIT_BASE + 0x28))
#define LPIT_TVAL1 *((volatile unsigned *)(LPIT_BASE + 0x30))
#define LPIT_TCTRL1 *((volatile unsigned *)(LPIT_BASE + 0x38))

#define M_CEN_BIT 0
#define TIF0_BIT 0
#define TIE0_BIT 0
#define TIF1_BIT 1
#define TIE1_BIT 1
#define MODE_BITS 2
#define T_EN_BIT 0

// NVIC Register
#define NVIC_ISER_BASE (0xE000E100)
#define NVIC_ISER1 *((volatile unsigned *)(NVIC_ISER_BASE + 0x4))

#define NVIC_ICPR_BASE (0xE000E280)
#define NVIC_ICPR1 *((volatile unsigned *)(NVIC_ICPR_BASE + 0x4))

#define NVIC_IPR_BASE (0xE000E400)
#define NVIC_IPR49 *((volatile unsigned *)(NVIC_IPR_BASE + 0x31))

// PORTA Register
#define PORTA_BASE (0x40049000)
#define PORTA_PCR0 *((volatile unsigned *)(PORTA_BASE + 0x0))
#define PORTA_PCR1 *((volatile unsigned *)(PORTA_BASE + 0x4))
#define PORTA_PCR2 *((volatile unsigned *)(PORTA_BASE + 0x8))
#define PORTA_PCR3 *((volatile unsigned *)(PORTA_BASE + 0xC))
#define PORTA_PCR4 *((volatile unsigned *)(PORTA_BASE + 0x10))
#define PORTA_PCR5 *((volatile unsigned *)(PORTA_BASE + 0x14))
#define PORTA_PCR6 *((volatile unsigned *)(PORTA_BASE + 0x18))
#define PORTA_PCR7 *((volatile unsigned *)(PORTA_BASE + 0x1C))
#define PORTA_PCR8 *((volatile unsigned *)(PORTA_BASE + 0x20))
#define PORTA_PCR9 *((volatile unsigned *)(PORTA_BASE + 0x24))
#define PORTA_PCR10 *((volatile unsigned *)(PORTA_BASE + 0x28))
#define PORTA_PCR11 *((volatile unsigned *)(PORTA_BASE + 0x2C))
#define PORTA_PCR12 *((volatile unsigned *)(PORTA_BASE + 0x30))
#define PORTA_PCR13 *((volatile unsigned *)(PORTA_BASE + 0x34))
#define PORTA_PCR14 *((volatile unsigned *)(PORTA_BASE + 0x38))
#define PORTA_PCR15 *((volatile unsigned *)(PORTA_BASE + 0x3C))
#define PORTA_PCR16 *((volatile unsigned *)(PORTA_BASE + 0x40))
#define PORTA_PCR17 *((volatile unsigned *)(PORTA_BASE + 0x44))

// PORTB Register
#define PORTB_BASE (0x4004A000)
#define PORTB_PCR0 *((volatile unsigned *)(PORTB_BASE + 0x0))
#define PORTB_PCR1 *((volatile unsigned *)(PORTB_BASE + 0x4))
#define PORTB_PCR2 *((volatile unsigned *)(PORTB_BASE + 0x8))
#define PORTB_PCR3 *((volatile unsigned *)(PORTB_BASE + 0xC))
#define PORTB_PCR4 *((volatile unsigned *)(PORTB_BASE + 0x10))
#define PORTB_PCR5 *((volatile unsigned *)(PORTB_BASE + 0x14))
#define PORTB_PCR6 *((volatile unsigned *)(PORTB_BASE + 0x18))
#define PORTB_PCR7 *((volatile unsigned *)(PORTB_BASE + 0x1C))
#define PORTB_PCR8 *((volatile unsigned *)(PORTB_BASE + 0x20))
#define PORTB_PCR9 *((volatile unsigned *)(PORTB_BASE + 0x24))
#define PORTB_PCR10 *((volatile unsigned *)(PORTB_BASE + 0x28))
#define PORTB_PCR11 *((volatile unsigned *)(PORTB_BASE + 0x2C))
#define PORTB_PCR12 *((volatile unsigned *)(PORTB_BASE + 0x30))
#define PORTB_PCR13 *((volatile unsigned *)(PORTB_BASE + 0x34))
#define PORTB_PCR14 *((volatile unsigned *)(PORTB_BASE + 0x38))
#define PORTB_PCR15 *((volatile unsigned *)(PORTB_BASE + 0x3C))
#define PORTB_PCR16 *((volatile unsigned *)(PORTB_BASE + 0x40))
#define PORTB_PCR17 *((volatile unsigned *)(PORTB_BASE + 0x44))

// PORTC Register
#define PORTC_BASE (0x4004B000)
#define PORTC_PCR0 *((volatile unsigned *)(PORTC_BASE + 0x0))
#define PORTC_PCR1 *((volatile unsigned *)(PORTC_BASE + 0x4))
#define PORTC_PCR2 *((volatile unsigned *)(PORTC_BASE + 0x8))
#define PORTC_PCR3 *((volatile unsigned *)(PORTC_BASE + 0xC))
#define PORTC_PCR4 *((volatile unsigned *)(PORTC_BASE + 0x10))
#define PORTC_PCR5 *((volatile unsigned *)(PORTC_BASE + 0x14))
#define PORTC_PCR6 *((volatile unsigned *)(PORTC_BASE + 0x18))
#define PORTC_PCR7 *((volatile unsigned *)(PORTC_BASE + 0x1C))
#define PORTC_PCR8 *((volatile unsigned *)(PORTC_BASE + 0x20))
#define PORTC_PCR9 *((volatile unsigned *)(PORTC_BASE + 0x24))
#define PORTC_PCR10 *((volatile unsigned *)(PORTC_BASE + 0x28))
#define PORTC_PCR11 *((volatile unsigned *)(PORTC_BASE + 0x2C))
#define PORTC_PCR12 *((volatile unsigned *)(PORTC_BASE + 0x30))
#define PORTC_PCR13 *((volatile unsigned *)(PORTC_BASE + 0x34))
#define PORTC_PCR14 *((volatile unsigned *)(PORTC_BASE + 0x38))
#define PORTC_PCR15 *((volatile unsigned *)(PORTC_BASE + 0x3C))
#define PORTC_PCR16 *((volatile unsigned *)(PORTC_BASE + 0x40))
#define PORTC_PCR17 *((volatile unsigned *)(PORTC_BASE + 0x44))

// PORTD Register
#define PORTD_BASE (0x4004C000)
#define PORTD_PCR0 *((volatile unsigned *)(PORTD_BASE + 0x0))
#define PORTD_PCR1 *((volatile unsigned *)(PORTD_BASE + 0x4))
#define PORTD_PCR2 *((volatile unsigned *)(PORTD_BASE + 0x8))
#define PORTD_PCR3 *((volatile unsigned *)(PORTD_BASE + 0xC))
#define PORTD_PCR4 *((volatile unsigned *)(PORTD_BASE + 0x10))
#define PORTD_PCR5 *((volatile unsigned *)(PORTD_BASE + 0x14))
#define PORTD_PCR6 *((volatile unsigned *)(PORTD_BASE + 0x18))
#define PORTD_PCR7 *((volatile unsigned *)(PORTD_BASE + 0x1C))
#define PORTD_PCR8 *((volatile unsigned *)(PORTD_BASE + 0x20))
#define PORTD_PCR9 *((volatile unsigned *)(PORTD_BASE + 0x24))
#define PORTD_PCR10 *((volatile unsigned *)(PORTD_BASE + 0x28))
#define PORTD_PCR11 *((volatile unsigned *)(PORTD_BASE + 0x2C))
#define PORTD_PCR12 *((volatile unsigned *)(PORTD_BASE + 0x30))
#define PORTD_PCR13 *((volatile unsigned *)(PORTD_BASE + 0x34))
#define PORTD_PCR14 *((volatile unsigned *)(PORTD_BASE + 0x38))
#define PORTD_PCR15 *((volatile unsigned *)(PORTD_BASE + 0x3C))
#define PORTD_PCR16 *((volatile unsigned *)(PORTD_BASE + 0x40))
#define PORTD_PCR17 *((volatile unsigned *)(PORTD_BASE + 0x44))

// PORTE Register
#define PORTE_BASE (0x4004D000)
#define PORTE_PCR0 *((volatile unsigned *)(PORTE_BASE + 0x0))
#define PORTE_PCR1 *((volatile unsigned *)(PORTE_BASE + 0x4))
#define PORTE_PCR2 *((volatile unsigned *)(PORTE_BASE + 0x8))
#define PORTE_PCR3 *((volatile unsigned *)(PORTE_BASE + 0xC))
#define PORTE_PCR4 *((volatile unsigned *)(PORTE_BASE + 0x10))
#define PORTE_PCR5 *((volatile unsigned *)(PORTE_BASE + 0x14))
#define PORTE_PCR6 *((volatile unsigned *)(PORTE_BASE + 0x18))
#define PORTE_PCR7 *((volatile unsigned *)(PORTE_BASE + 0x1C))
#define PORTE_PCR8 *((volatile unsigned *)(PORTE_BASE + 0x20))
#define PORTE_PCR9 *((volatile unsigned *)(PORTE_BASE + 0x24))
#define PORTE_PCR10 *((volatile unsigned *)(PORTE_BASE + 0x28))
#define PORTE_PCR11 *((volatile unsigned *)(PORTE_BASE + 0x2C))
#define PORTE_PCR12 *((volatile unsigned *)(PORTE_BASE + 0x30))
#define PORTE_PCR13 *((volatile unsigned *)(PORTE_BASE + 0x34))
#define PORTE_PCR14 *((volatile unsigned *)(PORTE_BASE + 0x38))
#define PORTE_PCR15 *((volatile unsigned *)(PORTE_BASE + 0x3C))
#define PORTE_PCR16 *((volatile unsigned *)(PORTE_BASE + 0x40))
#define PORTE_PCR17 *((volatile unsigned *)(PORTE_BASE + 0x44))

#define MUX_BITS 8
#define IRQC_BITS 16
#define ISF_BIT 24

// gpioa
#define GPIOA_BASE (0x400FF000)
#define GPIOA_PSOR *((volatile unsigned *)(GPIOA_BASE + 0x4))
#define GPIOA_PCOR *((volatile unsigned *)(GPIOA_BASE + 0x8))
#define GPIOA_PTOR *((volatile unsigned *)(GPIOA_BASE + 0xC))
#define GPIOA_PDIR *((volatile unsigned *)(GPIOA_BASE + 0x10))
#define GPIOA_PDDR *((volatile unsigned *)(GPIOA_BASE + 0x14))

// gpiob
#define GPIOB_BASE (0x400FF040)
#define GPIOB_PSOR *((volatile unsigned *)(GPIOB_BASE + 0x4))
#define GPIOB_PCOR *((volatile unsigned *)(GPIOB_BASE + 0x8))
#define GPIOB_PTOR *((volatile unsigned *)(GPIOB_BASE + 0xC))
#define GPIOB_PDIR *((volatile unsigned *)(GPIOB_BASE + 0x10))
#define GPIOB_PDDR *((volatile unsigned *)(GPIOB_BASE + 0x14))

// gpioc
#define GPIOC_BASE (0x400FF080)
#define GPIOC_PSOR *((volatile unsigned *)(GPIOC_BASE + 0x4))
#define GPIOC_PCOR *((volatile unsigned *)(GPIOC_BASE + 0x8))
#define GPIOC_PTOR *((volatile unsigned *)(GPIOC_BASE + 0xC))
#define GPIOC_PDIR *((volatile unsigned *)(GPIOC_BASE + 0x10))
#define GPIOC_PDDR *((volatile unsigned *)(GPIOC_BASE + 0x14))

// gpiod
#define GPIOD_BASE (0x400FF0C0)
#define GPIOD_PSOR *((volatile unsigned *)(GPIOD_BASE + 0x4))
#define GPIOD_PCOR *((volatile unsigned *)(GPIOD_BASE + 0x8))
#define GPIOD_PTOR *((volatile unsigned *)(GPIOD_BASE + 0xC))
#define GPIOD_PDIR *((volatile unsigned *)(GPIOD_BASE + 0x10))
#define GPIOD_PDDR *((volatile unsigned *)(GPIOD_BASE + 0x14))

// gpioe
#define GPIOE_BASE (0x400FF100)
#define GPIOE_PSOR *((volatile unsigned *)(GPIOE_BASE + 0x4))
#define GPIOE_PCOR *((volatile unsigned *)(GPIOE_BASE + 0x8))
#define GPIOE_PTOR *((volatile unsigned *)(GPIOE_BASE + 0xC))
#define GPIOE_PDIR *((volatile unsigned *)(GPIOE_BASE + 0x10))
#define GPIOE_PDDR *((volatile unsigned *)(GPIOE_BASE + 0x14))

#define PTA0 0
#define PTA1 1
#define PTA2 2
#define PTA3 3
#define PTA4 4
#define PTA5 5
#define PTA6 6
#define PTA7 7
#define PTA8 8
#define PTA9 9
#define PTA10 10
#define PTA11 11
#define PTA12 12
#define PTA13 13
#define PTA14 14
#define PTA15 15
#define PTA16 16
#define PTA17 17

#define PTB0 0
#define PTB1 1
#define PTB2 2
#define PTB3 3
#define PTB4 4
#define PTB5 5
#define PTB6 6
#define PTB7 7
#define PTB8 8
#define PTB9 9
#define PTB10 10
#define PTB11 11
#define PTB12 12
#define PTB13 13
#define PTB14 14
#define PTB15 15
#define PTB16 16
#define PTB17 17

#define PTC0 0
#define PTC1 1
#define PTC2 2
#define PTC3 3
#define PTC4 4
#define PTC5 5
#define PTC6 6
#define PTC7 7
#define PTC8 8
#define PTC9 9
#define PTC10 10
#define PTC11 11
#define PTC12 12
#define PTC13 13
#define PTC14 14
#define PTC15 15
#define PTC16 16
#define PTC17 17

#define PTD0 0
#define PTD1 1
#define PTD2 2
#define PTD3 3
#define PTD4 4
#define PTD5 5
#define PTD6 6
#define PTD7 7
#define PTD8 8
#define PTD9 9
#define PTD10 10
#define PTD11 11
#define PTD12 12
#define PTD13 13
#define PTD14 14
#define PTD15 15
#define PTD16 16
#define PTD17 17

#define PTE0 0
#define PTE1 1
#define PTE2 2
#define PTE3 3
#define PTE4 4
#define PTE5 5
#define PTE6 6
#define PTE7 7
#define PTE8 8
#define PTE9 9
#define PTE10 10
#define PTE11 11
#define PTE12 12
#define PTE13 13
#define PTE14 14
#define PTE15 15
#define PTE16 16
#define PTE17 17

#endif
