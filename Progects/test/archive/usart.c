#include "stm32l1xx.h"
#define SYS_TIC_HSI    (RCC->CFGR |= RCC_CFGR_SW_0)
#define SYS_TIC_HSE    (RCC->CFGR |= RCC_CFGR_SW_1)

void SystemInit()
{

}
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
int main(void)
{
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY));
    SYS_TIC_HSE;   //HSE in sysclk
	RCC->APB2ENR	|= RCC_APB2ENR_USART1EN;	//USART1 Clock ON
	USART1->BRR = 0x480;		// (sysclk/bodrate)/16 if result=AA,b then BRR=0xAAB when B=(0.b*16) else result=AA then BRR=0xAA0
	USART1->CR1  |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE; // USART1 ON, TX ON, RX ON

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBLPENR_GPIOALPEN;
	GPIOA->AFR[1] |= 0x770; //AF7(USART1..3) to pins 9,10          look at referens_manual page:177/911

	GPIOA->OTYPER &= ~GPIO_OTYPER_ODR_9; // Output push-pull (reset state)
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR9; // No pull-up, pull-down
	GPIOA->MODER |= GPIO_MODER_MODER9_1; // Alternate function mode
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_1; // 40 MHz High speed

	GPIOA->MODER |= GPIO_MODER_MODER10_1; // Alternate function mode
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_1; // 40 MHz High speed

	USART1->CR1 |= USART_CR1_RXNEIE; // RXNE Int ON
	NVIC_EnableIRQ (USART1_IRQn);
	__enable_irq ();

	while (1) {
        //~ while(!(USART1->SR & USART_SR_TC));
		//~ USART1->DR = 't';
        //~while(!(USART1->SR & USART_SR_TC));
		//~USART1->DR = '\n';
        //~ _myDelay(1000);
	}
}

void USART1_IRQHandler(void) {
	if (USART1->SR & USART_SR_RXNE) {
		while(!(USART1->SR & USART_SR_TC));
		USART1->DR = USART1->DR;
	}
}



