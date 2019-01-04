
#include "usart1.h"
#include "stm32l1xx.h"
void usart1_tx(unsigned char *text)
 {
    while(*text)
    {
        while(!(USART1->SR & USART_SR_TC));
		USART1->DR = *text++;
    }
 }

void usart1_init(void)
{
    RCC->APB2ENR	|= RCC_APB2ENR_USART1EN;	//USART1 Clock ON
	USART1->BRR = 0x682;//0x480;		// (sysclk/bodrate)/16 if result=AA,b then BRR=0xAAB when B=(0.b*16) else result=AA then BRR=0xAA0
	USART1->CR1  |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE; // USART1 ON, TX ON, RX ON

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBLPENR_GPIOALPEN;
	GPIOA->AFR[1] |= 0x770; //AF7(USART1..3) to pins 9,10          look at referens_manual page:177/911

	GPIOA->OTYPER &= ~GPIO_OTYPER_ODR_9; // Output push-pull (reset state)
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR9; // No pull-up, pull-down
	GPIOA->MODER |= GPIO_MODER_MODER9_1; // Alternate function mode
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_1; // 40 MHz High speed

	GPIOA->MODER |= GPIO_MODER_MODER10_1; // Alternate function mode
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_1; // 40 MHz High speed
}
