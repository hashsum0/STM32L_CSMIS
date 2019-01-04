#include "stm32l1xx.h"
#include "inc/usart1.h"
//#include "inc/tim3.h"
#define SYS_TIC_HSI    (RCC->CFGR |= RCC_CFGR_SW_0)
#define SYS_TIC_HSE    (RCC->CFGR |= RCC_CFGR_SW_1)



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

//~ void TIM3_IRQHandler(void)
  //~ {

    //~ TIM3->SR &=~ TIM_SR_UIF;
    
    //~ usart1_tx("est' perepolnenie\n\r");  
  
  //~ }   
int main()
{
    int adc_channel_0_value;
    unsigned char data_adc[10];
    //unsigned char test[16];
    //~ RCC->CR |= RCC_CR_HSEON;
	//~ while(!(RCC->CR & RCC_CR_HSERDY));
    //~ SYS_TIC_HSE;   //HSE in sysclk

    
        
       
        SYS_TIC_HSI ;
        //тактирование на порта А
        RCC->AHBENR |=  RCC_AHBENR_GPIOAEN;
        //порт на вход
        GPIOA->MODER |=  GPIO_MODER_MODER0;
        //тактирование на АЦП
        RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
        //делитель / 2
        ADC->CCR  |= ADC_CCR_ADCPRE_0;
        //ADC_SQRx_SQy y-номер в очереди на преобразование, х-номер группы из шести номеров в очереди(ADC_SQR5[SQ1...6] ADC_SQR4[SQ7...12] и т.д.)
        ADC1->SQR5 |= ADC_SQR5_SQ1_0 | ADC_SQR5_SQ1_2;
        //запускаем АЦП
        ADC1->CR2 |= ADC_CR2_ADON;
        //ждем установки флага запуска.
        while((ADC1->SR & ADC_SR_ADONS) == (uint32_t)RESET);
        RCC->AHBENR	|= RCC_AHBENR_GPIOAEN;				
        GPIOA->MODER   |= GPIO_MODER_MODER8_1;
        GPIOA->OSPEEDR   |= GPIO_OSPEEDER_OSPEEDR8_1;
        RCC->CFGR &=~ RCC_CFGR_MCOSEL;
        RCC->CFGR |= RCC_CFGR_MCOSEL_1;
        //~ timer3_pwm_ch1(14000);
        usart1_init();
    
 
  while(1)
  {
      usart1_tx("test-Ok\n\r");
      ADC1->CR2 |= ADC_CR2_SWSTART;
        while ((ADC1->SR & ADC_SR_EOC) != ADC_SR_EOC);
      
      adc_channel_0_value = ADC1->DR;
      data_adc[0]=adc_channel_0_value%100000/10000+48;
      data_adc[1]=adc_channel_0_value%10000/1000+48;
      data_adc[2]=adc_channel_0_value%1000/100+48;
      data_adc[3]=adc_channel_0_value%100/10+48;
      data_adc[4]=adc_channel_0_value%10/1+48;
      
      if(adc_channel_0_value>0) usart1_tx(data_adc);
      else usart1_tx("error\n\r");
      _myDelay(10000);

  }
}
