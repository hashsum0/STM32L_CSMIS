#include "src/stm32l1xx.h"
#include "src/myfunction.h"

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
    HSI_init();
  
    SYS_TIC_HSI;

    InitGPIO();
    OSC_SYS_outpin();
        
while(1)
	{
       
	   GPIOB->BSRR |= (GPIO_BSRR_BS_7);
       _myDelay(100);
	   GPIOB->BSRR |= (GPIO_BSRR_BR_7);
       _myDelay(100);
	}
} 


