
#include "stm32l1xx.h"
#include "myfunction.h"
void _myDelay(int16_t t)
    {
        int16_t d=0, z=0;

        for(z=0;z<t;z++)
        {
            for(d=0;d<1000;d++)
            {
               __NOP();
            }
        }
    }
void HSI_init(void)
    {
        RCC->CR |= RCC_CR_HSION;
        while(!(RCC->CR&RCC_CR_HSIRDY))
          {
          }
    }
void HSE_init(void)
    {
        RCC->CR |= RCC_CR_HSEON;
        while(!(RCC->CR&RCC_CR_HSERDY))
          {
          }
    }
void PLL_init(void)
    {    
        RCC->CFGR|=RCC_CFGR_PLLDIV;
        RCC->CR|=RCC_CR_PLLON;
        while (!(RCC->CR & RCC_CR_PLLRDY))
        {//PLL>16MHz RESET_CHIP
        }
    }     
void OSC_HSE_outpin(void)
    {
        RCC->AHBENR	|= RCC_AHBENR_GPIOAEN;				
        GPIOA->MODER   |= GPIO_MODER_MODER8_1;
        GPIOA->OSPEEDR   |= GPIO_OSPEEDER_OSPEEDR8_1;
        RCC->CFGR &=~ RCC_CFGR_MCOSEL;
        RCC->CFGR |= RCC_CFGR_MCOSEL_2;
    }
void OSC_HSI_outpin(void)
    {
        RCC->AHBENR	|= RCC_AHBENR_GPIOAEN;				
        GPIOA->MODER   |= GPIO_MODER_MODER8_1;
        GPIOA->OSPEEDR   |= GPIO_OSPEEDER_OSPEEDR8_1;
        RCC->CFGR &=~ RCC_CFGR_MCOSEL;
        RCC->CFGR |= RCC_CFGR_MCOSEL_1;
    }
void OSC_SYS_outpin(void)
    {
        RCC->AHBENR	|= RCC_AHBENR_GPIOAEN;				
        GPIOA->MODER   |= GPIO_MODER_MODER8_1;
        GPIOA->OSPEEDR   |= GPIO_OSPEEDER_OSPEEDR8_1;
        RCC->CFGR &=~ RCC_CFGR_MCOSEL;
        RCC->CFGR |= RCC_CFGR_MCOSEL_0;
    }
void OSC_PLL_outpin(void)
    {
        RCC->AHBENR	|= RCC_AHBENR_GPIOAEN;				
        GPIOA->MODER   |= GPIO_MODER_MODER8;
        GPIOA->OSPEEDR   |= GPIO_OSPEEDER_OSPEEDR8;
        RCC->CFGR &=~ RCC_CFGR_MCOSEL;
        RCC->CFGR |= RCC_CFGR_MCOSEL_0 | RCC_CFGR_MCOSEL_2;
    }
