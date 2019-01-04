#include "src/stm32l1xx.h"
#include "inc/myfunction.h"
#include "inc/USART1.h"
void SystemInit()
{

}

void InitGPIO(void)
{
   
   //GPIOA->PUPDR  &=~  GPIO_PUPDR_PUPDR7_0 | GPIO_PUPDR_PUPDR7_1;
   
   RCC->AHBENR	|= RCC_AHBENR_GPIOBEN;
   GPIOB->MODER   |= GPIO_MODER_MODER7_0;
   GPIOB->PUPDR  |=  GPIO_PUPDR_PUPDR7_1;
   //GPIOB->CRH	&= ~GPIO_CRH_CNF8;
   //GPIOB->CRH   |= GPIO_CRH_MODE8_0;
}

int main(void)
{
    HSE_init();
    InitGPIO();
    USART1_init();
    SYS_TIC_HSE;
    OSC_HSE_outpin();

    USART1->CR1 |= USART_CR1_RXNEIE; // RXNE Int ON
	NVIC_EnableIRQ (USART1_IRQn);
	__enable_irq ();
while(1)
	{
       
	   GPIOB->BSRR |= (GPIO_BSRR_BS_7);
       _myDelay(100);
	   GPIOB->BSRR |= (GPIO_BSRR_BR_7);
       _myDelay(100);
	}
} 
void USART1_IRQHandler(void) {
	if (USART1->SR & USART_SR_RXNE) {
		while(!(USART1->SR & USART_SR_TC));
		USART1->DR = USART1->DR;
	}
}


