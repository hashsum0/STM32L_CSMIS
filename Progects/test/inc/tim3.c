#include "stm32l1xx.h"
#include "tim3.h"
void timer3_capture_ch1(void)
{
/*Инициализация таймера TIM3.
  Для измерения периода входного сигнала используется канал 1 (TIM3_CH1)*/
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;//Тактирование GPIOC
  //Вывод PC6 настраивается в качестве входа TIM3_CH2
  GPIOC->MODER |= GPIO_MODER_MODER6_1;//PC6 - AF
  GPIOC->AFR[0] |= 0x02000000;//PC6 - AFIO2 (TIM3_CH1)
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;//Включаем тактирование TIM3
  TIM3->CCMR1 |= TIM_CCMR1_CC1S_0;//Выбор активного входа. Записываем "01" в биты CC1S - связываем регистр TIM3_CCR1 со входом TI1
  TIM3->CCMR1 |= (TIM_CCMR1_IC1F_0 | TIM_CCMR1_IC1F_1| TIM_CCMR1_IC1F_2| TIM_CCMR1_IC1F_3);//Выбор длительнотси действия фильтра - 8 тактов. IC1F = 0011.
  TIM3->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);//По переднему фронту - положительный перепад импульса
  TIM3->CCMR1 &= ~TIM_CCMR1_IC1PSC;//Предделитель отключен
  TIM3->CCER |= TIM_CCER_CC1E;//Разрешен захват значения счетчика в регистр TIM3_CCR1
  TIM3->DIER |= TIM_DIER_CC1IE;//Разрешена генерация прерывания при захвате
  TIM3->CR1 |= TIM_CR1_CEN;//Запускаем счет таймера

}

void timer3_counter(uint16_t arr)
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;//Включаем тактирование TIM3
  TIM3->PSC = 0x2B32;//prescaler fsys_clk/(psc[0xXXXX]+1)
  TIM3->ARR = arr ;//do ckol'ki schitat'
  TIM3->DIER |= TIM_DIER_UIE;// on enterrupt
  TIM3->CR1 |= TIM_CR1_CEN;//start counter
}
void timer3_pwm_ch2(uint16_t procent)
{
//Инициализация вывода на альтернативный выход.
//Тактирование GPIOC
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
//Вывод PC7 настраивается в качестве альтернативной выход TIM3_CH2
  GPIOC->MODER |= GPIO_MODER_MODER7_1;//PC7 - AF
//PC7 находится в AFRL или AFR[0], (TIM3_CH2)= AFO2 или AF=0x02, на каждый вывод приходится по четыре бита т.е. двойку ставить в седьмой четверке битов
//0010 0000 0000 0000 0000 0000 0000 или 0x20000000
  GPIOC->AFR[0] |= 0x20000000;
//Включаем тактирование TIM3
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
//устанавливаем делитель  
  TIM3->PSC = 64;
//включаем предварительную загрузку
  TIM3->CR1 |= TIM_CR1_ARPE;
//устанавливаем режим шим  
  TIM3->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1;
//разрешаем сигнал на выход  
  TIM3->CCER |= TIM_CCER_CC2E;
//активный положительный
  TIM3->CCER &=~ TIM_CCER_CC2P;
//активный отрицательный
//  TIM3->CCER |= TIM_CCER_CC2P;
//предворительно загружаем число. 
  TIM3->ARR = 16000;
//процент заполнения  
  TIM3->CCR2 = procent;
//запускаем  
  TIM3->CR1 |= TIM_CR1_CEN;
}

void timer3_pwm_ch1(uint16_t procent)
{
//Инициализация таймера TIM3.
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;//Тактирование GPIOC
  //Вывод PC7 настраивается в качестве альтернативной выход TIM3_CH2
  GPIOC->MODER |= GPIO_MODER_MODER6_1;//PC7 - AF
  GPIOC->AFR[0] |= 0x02000000;//PC7 [0..7]=AFRL или AFR[0], (TIM3_CH2)= AF-O2 или 0x02, на каждый вывод по четыре бита т.е. двойку ставить в седьмой четверке битоа
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;//Включаем тактирование TIM3
  TIM3->PSC = 64;
  TIM3->CR1 |= TIM_CR1_ARPE;
  TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
  TIM3->CCER |= TIM_CCER_CC1E;
  TIM3->ARR = 16000;
  TIM3->CCR1 = procent;
  TIM3->CR1 |= TIM_CR1_CEN;
}
