/*
 * stm32f401rbt6.h
 *
 *  Created on: Nov 15, 2024
 *      Author: Hitesh
 */
#ifndef STM32F401RBT6_H
#define STM32F401RBT6_H
#include <stdint.h>

/*----------------------------------------------------- Base Addresses Of Peripherals ---------------------------------------------*/

//NVIC
#define NVIC_BASE		0xE000E100UL
						
//SYSTICK_TIMER     	
#define SYSTICK_BASE	0xE000E010UL
						
//RCC               	
#define RCC_BASE 		0x40023800UL
						
//GPIO              	
#define GPIOA_BASE		0x40020000UL
#define GPIOB_BASE		0x40020400UL
#define GPIOC_BASE		0x40020800UL
						
//EXTI              	
#define EXTI_BASE		0x40013C00UL
						
//SYSCFG            	
#define SYSCFG_BASE		0x40013800UL
						
//UART             	
#define UART6_BASEADD	0x40011400UL 
#define UART1_BASEADD	0x40011000UL 
#define UART2_BASEADD	0x40004400UL
						
//I2C               	
#define I2C1_BASE		0x40005400UL

//SPI
#define SPI1_BASE		0x40013000UL 
#define SPI2_BASE		0x40003800UL 

//TIMERS
#define TIM9_BASEADD	0x40014000UL 

//ADC
#define ADC_BASEADD		0x40012000UL 

/*------------------------------------------------ Typedef Structure ------------------------------------------*/

typedef struct
{
	volatile uint32_t MODER;	/*GPIO port mode register,				Address offset: 0x00	*/
	volatile uint32_t OTYPER;	/*GPIO port output type register,		Address offset: 0x04	*/
	volatile uint32_t OSPEEDR;	/*GPIO port output speed register,		Address offset: 0x08	*/
	volatile uint32_t PUPDR;	/*GPIO port pull-up/pull-down register,	Address offset: 0x0C	*/
	volatile uint32_t IDR;		/*GPIO port input data register,		Address offset: 0x10	*/
	volatile uint32_t ODR;		/*GPIO port output data register,		Address offset: 0x14	*/
	volatile uint32_t BSRR;		/*GPIO port bit set/reset register,		Address offset: 0x18	*/
	volatile uint32_t LCKR;		/*GPIO port configuration lock register,Address offset: 0x1C	*/
	volatile uint32_t AFRL;		/*GPIO alternate function,				Address offset: 0x20 */
	volatile uint32_t AFRH;		/*GPIO alternate function,				Address offset: 0x24 */
}GPIO_TypeDef;

typedef struct
{
  volatile uint32_t dummy1[12];
  volatile uint32_t AHB1ENR;	/*RCC AHB1 peripheral clock enable register,	Address offset: 0x30	*/
  volatile uint32_t AHB2ENR;	/*RCC AHB2 peripheral clock enable register,	Address offset: 0x34	*/
  volatile uint32_t dummy2[2];
  volatile uint32_t APB1ENR;	/*RCC APB1 peripheral clock enable register,	Address offset: 0x40	*/
  volatile uint32_t APB2ENR;	/*RCC APB2 peripheral clock enable register,	Address offset: 0x44	*/
}RCC_TypeDef;

typedef struct
{
  volatile uint32_t CTRL;	/*SysTick control and status register,	Address offset: 0x00	*/
  volatile uint32_t LOAD;	/*SysTick reload value register,		Address offset: 0x04	*/
  volatile uint32_t VAL;	/*SysTick current value register ,		Address offset: 0x08	*/
}SysTick_TypeDef;

typedef struct
{
  volatile uint32_t IMR;	/*Interrupt mask register ,				Address offset: 0x00	*/
  volatile uint32_t EMR;	/*Event mask register,					Address offset: 0x04	*/
  volatile uint32_t RTSR;	/*Rising trigger selection register,	Address offset: 0x08	*/
  volatile uint32_t FTSR;	/*Falling trigger selection register,	Address offset: 0x0C	*/
  volatile uint32_t SWIER;	/*Software interrupt event register,	Address offset: 0x10	*/
  volatile uint32_t PR;		/*Pending register,						Address offset: 0x14	*/
}EXTI_TypeDef;

typedef struct
{
  volatile uint32_t ISER0;	/*Interrupt set-enable register 0,	Address offset: 0x00	*/
  volatile uint32_t ISER1;	/*Interrupt set-enable register 1,	Address offset: 0x04	*/
  volatile uint32_t ISER2;	/*Interrupt set-enable register 2,	Address offset: 0x08	*/
}NVIC_TypeDef;

typedef struct
{
  volatile uint32_t dummy[2];
  volatile uint32_t EXTICR1; /*SYSCFG external interrupt configuration register 3,	Address offset: 0x08*/
  volatile uint32_t EXTICR2; /*SYSCFG external interrupt configuration register 3,	Address offset: 0x0C*/
  volatile uint32_t EXTICR3; /*SYSCFG external interrupt configuration register 3,	Address offset: 0x10*/
}SYSCFG_TypeDef;

typedef struct
{
  volatile uint32_t CR1;	/*I2C Control register 1,		Address offset: 0x00	*/
  volatile uint32_t CR2;	/*I2C Control register 2,		Address offset: 0x04	*/
  volatile uint32_t OAR1;	/*I2C Own address register 1,	Address offset: 0x08	*/
  volatile uint32_t OAR2;	/*I2C Own address register 2,	Address offset: 0x0C	*/
  volatile uint32_t DR;		/*I2C Data register,			Address offset: 0x10	*/
  volatile uint32_t SR1;	/*I2C Status register 1,		Address offset: 0x14	*/
  volatile uint32_t SR2;	/*I2C Status register 2,		Address offset: 0x18	*/
  volatile uint32_t CCR;	/*I2C Clock control register,	Address offset: 0x1C	*/
  volatile uint32_t TRISE;	/*I2C TRISE register,			Address offset: 0x20	*/
  volatile uint32_t FLTR;	/*I2C FLTR register,			Address offset: 0x24	*/
}I2C_TypeDef;

typedef struct
{
  volatile uint32_t CR1;	/*SPI Control register 1,	Address offset: 0x00	*/
  volatile uint32_t CR2;	/*SPI Control register 2,	Address offset: 0x04	*/
  volatile uint32_t SR;		/*SPI Status register,		Address offset: 0x08	*/
  volatile uint32_t DR;		/*SPI Data register,		Address offset: 0x0C	*/
}SPI_TypeDef;

typedef struct
{
	volatile uint32_t SR;	/*UART Status register ,	Address offset: 0x00	*/
	volatile uint32_t DR;	/*UART Data register ,		Address offset: 0x04	*/
	volatile uint32_t BRR;	/*UART Baud Rate register,	Address offset: 0x08	*/
	volatile uint32_t CR1;	/*UART  Control register 1,	Address offset: 0x0C	*/
	volatile uint32_t CR2;	/*UART  Control register 1,	Address offset: 0x10	*/
}UART_TypeDef;

typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t reserved1;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t reserved2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t reserved3;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
}TIM9_TypeDef;

typedef struct
{
	volatile uint32_t SR;		/*ADC Status register ,							Address offset: 0x00	*/
	volatile uint32_t CR1;      /*ADC control register 1  ,						Address offset: 0x04	*/
	volatile uint32_t CR2;      /*ADC control register 2 ,						Address offset: 0x08	*/
	volatile uint32_t SMPR1;    /*ADC sample time register 1,					Address offset: 0x0C	*/
	volatile uint32_t SMPR2;    /*ADC sample time register 2,					Address offset: 0x10	*/
	volatile uint32_t JOFR1;	/*ADC injected channel data offset register 1,	Address offset: 0x14	*/
	volatile uint32_t JOFR2;    /*ADC injected channel data offset register 2,	Address offset: 0x18	*/
	volatile uint32_t JOFR3;    /*ADC injected channel data offset register 3,	Address offset: 0x1C	*/
	volatile uint32_t JOFR4;    /*ADC injected channel data offset register 4,	Address offset: 0x20	*/
	volatile uint32_t HTR;      /*ADC watchdog higher threshold register,		Address offset: 0x24	*/
	volatile uint32_t LTR;		/*ADC watchdog lower threshold register ,		Address offset: 0x28	*/
	volatile uint32_t SQR1;     /*ADC regular sequence register 1,				Address offset: 0x2C	*/
	volatile uint32_t SQR2;     /*ADC regular sequence register 2,				Address offset: 0x30	*/
	volatile uint32_t SQR3;     /*ADC regular sequence register 3,				Address offset: 0x34	*/
	volatile uint32_t JSQR;     /*ADC injected sequence register,				Address offset: 0x38	*/
	volatile uint32_t JDR1;		/*ADC injected data register 1,					Address offset: 0x3C	*/
	volatile uint32_t JDR2;     /*ADC injected data register 2,					Address offset: 0x40	*/
	volatile uint32_t JDR3;     /*ADC injected data register 3,					Address offset: 0x44	*/
	volatile uint32_t JDR4;     /*ADC injected data register 4,					Address offset: 0x48	*/
	volatile uint32_t DR;       /*ADC regular data register,					Address offset: 0x4C	*/
}ADC_TypeDef;

/*--------------------------------Defined Macros-------------------------------------------*/

#ifndef BIT
#define BIT(x)						(1U << (x))
#endif
#define SUCCESS							0
#define FAIL							-1
#define FOUND							0
#define NOT_FOUND						-2
#define SET_BIT(reg_name,bit_pos)		((reg_name) |= BIT(bit_pos))
#define RESET_BIT(reg_name,bit_pos)		((reg_name) &= ~BIT(bit_pos))
#define TOGGLE_BIT(reg_name,bit_pos)	((reg_name) ^= BIT(bit_pos))
#define CHECK_BIT(reg_name,bit_pos)		((reg_name) & BIT(bit_pos))
//SYSTICK_TIMER
#define SYSTICK		((SysTick_TypeDef*)SYSTICK_BASE)
	
//NVIC	
#define NVIC		((NVIC_TypeDef *)NVIC_BASE)
	
//RCC	
#define RCC			((RCC_TypeDef *)RCC_BASE)
	
//GPIO	
#define GPIOA		((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB		((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC		((GPIO_TypeDef *)GPIOC_BASE)
	
//SYSCFG	
#define SYSCFG		((SYSCFG_TypeDef *)SYSCFG_BASE)
	
//EXTI	
#define EXTI		((EXTI_TypeDef *)EXTI_BASE)

//UART
#define UART6		((UART_TypeDef *)UART6_BASEADD)
#define UART1		((UART_TypeDef *)UART1_BASEADD)
#define UART2		((UART_TypeDef *)UART2_BASEADD)

//I2C	
#define I2C1		((I2C_TypeDef *)I2C1_BASE)
	
//SPI	
#define SPI1		((SPI_TypeDef *)SPI1_BASE)
#define SPI2		((SPI_TypeDef *)SPI2_BASE)

//TIMERS
#define TIM9		((TIM9_TypeDef *)TIM9_BASEADD)

//ADC
#define ADC			((ADC_TypeDef *)ADC_BASEADD)
#endif /* STM32F401RBT6_H */
