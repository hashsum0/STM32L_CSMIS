#include "stm32l1xx.h"
#ifndef __MYFUNCTION_H
#define __MYFUNCTION_H

#define SYS_TIC_HSE    (RCC->CFGR |= RCC_CFGR_SW_1)
#define SYS_TIC_HSI    (RCC->CFGR |= RCC_CFGR_SW_0)
#define SYS_TIC_MSI    (RCC->CFGR &=~ RCC_CFGR_SW_1 | RCC_CFGR_SW_0)
#define SYS_TIC_PLL    (RCC->CFGR |= RCC_CFGR_SW_1 | RCC_CFGR_SW_0)

void _myDelay(int16_t t);
void HSI_init(void);
void HSE_init(void);
void PLL_init(void);     
void OSC_HSE_outpin(void);
void OSC_HSI_outpin(void);
void OSC_SYS_outpin(void);
void OSC_PLL_outpin(void);
                  
#endif /*__MYFUNCTION_H */
