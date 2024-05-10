/*
 * stm32f103c6_LQFP48.h
 *
 *  Created on: Sep 8, 2023
 *      Author: Ahmed Ashraf
 */

#ifndef INC_STM32F103C6_LQFP48_H_
#define INC_STM32F103C6_LQFP48_H_


//-----------------------------
//Includes
//-----------------------------

#include <stdint.h>
#include "stdlib.h"
#include "stm32f103c6_RCC_driver.h"
//-----------------------------
//Base addresses for Memories
//-----------------------------

#define FLASH_Memory_BASE  											0x08000000UL
#define SYSTEM_Memory_BASE  										0x1FFFF000UL
#define SRAM_BASE  													0x20000000UL

#define Peripherals_BASE  											0x40000000UL

#define cortex_M3_internal_Peripherals_BASE  						0xE0000000UL

#define NVCI_BASE  													0xE000E100UL

//-------------------------------------------------------------------------
//Base addresses for BUS Peripherals
//-------------------------------------------------------------------------

//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------

#define RCC_BASE  											0x40021000UL

//-----------------------------
//Base addresses for APB2 Peripherals
//-----------------------------

#define GPIOA_BASE  											0x40010800UL  //Fully Included
#define GPIOB_BASE  											0x40010C00UL  //Fully Included
#define GPIOC_BASE  											0x40011000UL  //Partially Included
#define GPIOD_BASE  											0x40011400UL  //Partially Included

#define EXTI_BASE  												0x40010400UL
#define AFIO_BASE  												0x40010000UL

#define USART1_BASE												0x40013800UL

#define SPI1_BASE												0x40013000UL

#define TIM1_BASE												0x40012C00UL

#define ADC1_BASE												0x40012400UL
#define ADC2_BASE												0x40012800UL


//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------
#define USART2_BASE												0x40004400UL
#define USART3_BASE												0x40004800UL


#define SPI2_BASE												0x40003800UL

#define I2C1_BASE												0x40005400UL
#define I2C2_BASE												0x40005800UL

#define TIM2_BASE												0x40000000UL
#define TIM3_BASE												0x40000400UL
#define TIM4_BASE												0x40000800UL
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: NVIC
//-*-*-*-*-*-*-*-*-*-*-*

#define  NVIC_ISER0  			*(volatile unsigned int *)(NVCI_BASE+0x000)//0-31
#define  NVIC_ISER1  			*(volatile unsigned int *)(NVCI_BASE+0x004)//32-63
#define  NVIC_ISER2  			*(volatile unsigned int *)(NVCI_BASE+0x008)//64-67
#define  NVIC_ICER0  			*(volatile unsigned int *)(NVCI_BASE+0x080)
#define  NVIC_ICER1  			*(volatile unsigned int *)(NVCI_BASE+0x084)
#define  NVIC_ICER2  			*(volatile unsigned int *)(NVCI_BASE+0x088)

/*--------------------------------------------Data Type Declaration----------------------------------*/





//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;


}GPIO_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
	/*volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;*/
	volatile uint32_t RESERVED0;
	volatile uint32_t MAPR2;

}AFIO_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;

}EXTI_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
}RCC_t;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	//volatile uint32_t SR;
	struct
	{
		uint32_t PE	  : 1;
		uint32_t not_used1 : 4;
		uint32_t RXNE	  : 1;
		uint32_t TC	 	  : 1;
		uint32_t TXE	  : 1;
		uint32_t not_used2 : 2;
		uint32_t Reserved : 22;

	}SR;
	//volatile uint32_t DR;
	struct
	{
		uint32_t DR : 9;
		uint32_t Reserved : 23;
	}DR;
	//volatile uint32_t BRR;
	struct
	{
		uint32_t DIV_Fraction : 4;
		uint32_t DIV_Mantissa : 12;
		uint32_t Reserved : 16;
	}BRR;
	//volatile uint32_t CR1;
	struct
	{
		uint32_t not_used1 : 2;
		uint32_t RE_TE	  : 2;
		uint32_t not_used2 : 1;
		uint32_t RXNEIE_TCIE_TXEIE_PEIE : 4;
		//uint32_t PS 	  : 1 ;
		uint32_t PS_PCE   : 2 ;
		uint32_t WAKE 	  : 1 ;
		uint32_t M 		  : 1 ;
		uint32_t UE 	  : 1 ;
		uint32_t Reserved : 18;

	}CR1;
	//volatile uint32_t CR2;
	struct
	{
		uint32_t not_used : 12;
		//uint32_t PCE 	  : 1 ;
		//uint32_t WAKE 	  : 1 ;
		uint32_t STOP 	  : 2 ;
		//uint32_t UE 	  : 1 ;
		uint32_t Reserved : 18;

	}CR2;
	//volatile uint32_t CR3;
	struct
	{
		uint32_t not_used : 8;
		uint32_t RTS_CTS 	  : 2 ;
		//uint32_t WAKE 	  : 1 ;
		uint32_t not_used2 	  : 4 ;
		//uint32_t UE 	  : 1 ;
		uint32_t Reserved : 18;

	}CR3;
	volatile uint32_t GTPR;

}USART_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	//volatile uint32_t CR1;
	struct
	{
		uint32_t CPHA_CPOL 			: 2;
		//uint32_t CPOL 		: 1;
		uint32_t MSTR 				: 1;
		uint32_t BR   				: 3;
		uint32_t SPE  				: 1;
		uint32_t LSBFIRST  		    : 1;
		uint32_t SSI 				: 1;
		uint32_t SSM 				: 1;
		uint32_t RXONLY 			: 1;
		uint32_t DFF 				: 1;
		uint32_t CRCNEXT 			: 1;
		uint32_t CRCEN 				: 1;
		uint32_t BIDIOE_BIDIMODE 	: 1;
		//uint32_t BIDIMODE 	: 1;
		uint32_t Reserved 			: 16;

	}CR1;
	//volatile uint32_t CR2;
	struct
	{

		uint32_t RXDMAEN 				: 1;
		uint32_t TXDMAEN 				: 1;
		uint32_t SSOE 					: 1;
		uint32_t Reserved1 				: 2;
		uint32_t ERRIE_RXNEIE_TXEIE		: 3;
		//uint32_t RXNEIE 	: 1;
		//uint32_t TXEIE 	: 1;
		uint32_t Reserved2 				: 24;

	}CR2;
	//volatile uint32_t SR;
	struct
	{

		uint32_t RXNE 		: 1;
		uint32_t TXE 		: 1;
		uint32_t CHSIDE 	: 1;
		uint32_t UDR 		: 1;
		uint32_t CRCERR 	: 1;
		uint32_t MODF 		: 1;
		uint32_t OVR 		: 1;
		uint32_t BSY 		: 1;
		uint32_t Reserved 	: 24;

	}SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;

}SPI_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: I2C
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	//volatile uint32_t CR1;
	struct
	{

		uint32_t PE 		: 1;
		uint32_t SMBUS 		: 1;
		uint32_t Reserved 	: 4;
		uint32_t ENGC 		: 1;
		uint32_t NO_STRETCH : 1;
		uint32_t START 		: 1;
		uint32_t STOP 		: 1;
		uint32_t ACK 	    : 1;
		uint32_t POS   		: 1;
		uint32_t PEC 	    : 1;
		uint32_t Reserved1 	: 19;

	}CR1;
	//volatile uint32_t CR2;
	struct
	{

		uint32_t FREQ 		: 6;
		uint32_t Reserved 	: 2;
		uint32_t ITERREN 	: 1;
		uint32_t ITEVTEN 	: 1;
		uint32_t ITBUFEN 	: 1;
		uint32_t DMAEN   	: 1;
		uint32_t LAST 	    : 1;
		uint32_t Reserved1 	: 19;

	}CR2;
	//volatile uint32_t OAR1;
	struct
	{

		uint32_t ADD_0 		: 1;
		uint32_t ADD_1_7 	: 7;
		uint32_t ADD_8_9 	: 2;
		uint32_t Reserved 	: 5;
		uint32_t ADD_MODE 	: 1;
		uint32_t Reserved1 	: 16;

	}OAR1;
	//volatile uint32_t OAR2;
	struct
	{

		uint32_t ENDUAL 	: 1;
		uint32_t ADD2 		: 7;
		uint32_t Reserved 	: 24;

	}OAR2;
	volatile uint32_t DR;
	//volatile uint32_t SR1;
	struct
	{

		uint32_t  SB 		: 1;
		uint32_t  ADDR 		: 1;
		uint32_t  BTF 		: 1;
		uint32_t  ADD10 	: 1;
		uint32_t  STOPF 	: 1;
		uint32_t  Reserved 	: 1;
		uint32_t  RxNE 		: 1;
		uint32_t  TxE 		: 1;
		uint32_t Reserved1 	: 24;

	}SR1;
	//volatile uint32_t SR2;
	struct
	{

		uint32_t MSL 		: 1;
		uint32_t  BUSY 		: 1;
		uint32_t  TRA 		: 1;
		uint32_t Reserved 	: 29;
		//uint32_t Reserved1 	: 16;

	}SR2;
	//volatile uint32_t CCR;
	struct
	{

		uint32_t CCR 		: 12;
		uint32_t Reserved 	: 2;
		uint32_t  DUTY 		: 1;
		uint32_t  F_S 		: 1;
		uint32_t Reserved1 	: 16;

	}CCR;
	//volatile uint32_t TRISE;
	struct
	{

		uint32_t TRISE 		: 6;
		uint32_t Reserved1 	: 26;

	}TRISE;


}I2C_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: TIM			for 2,3,4 general purpose only
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	//volatile uint32_t CR1;
	struct
	{

		uint32_t CEN 		: 1;
		uint32_t UDIS 		: 1;
		uint32_t URS 		: 1;
		uint32_t OPM 		: 1;
		uint32_t DIR 		: 1;
		uint32_t CMS 		: 2;
		uint32_t ARPE 		: 1;
		uint32_t CKD 		: 2;
		uint32_t Reserved1 	: 22;

	}CR1;
	//volatile uint32_t CR2;
	struct
	{

		uint32_t Reserved 	: 3;
		uint32_t CCDS 		: 1;
		uint32_t MMS 		: 3;
		uint32_t TI1S 		: 1;
		uint32_t Reserved1 	: 24;

	}CR2;
	//volatile uint32_t SMCR;
	struct
	{

		uint32_t SMS 		: 3;
		uint32_t Reserved 	: 1;
		uint32_t TS 		: 3;
		uint32_t MSM 		: 1;
		uint32_t ETF 		: 4;
		uint32_t ETPS 		: 2;
		uint32_t ECE 		: 1;
		uint32_t ETP 		: 1;
		uint32_t Reserved1 	: 16;

	}SMCR;
	//volatile uint32_t DIER;
	struct
	{

		uint32_t UIE 		: 1;
		uint32_t CC1IE 		: 1;
		uint32_t CC2IE 		: 1;
		uint32_t CC3IE 		: 1;
		uint32_t CC4IE 		: 1;
		uint32_t Reserved 	: 1;
		uint32_t TIE 		: 1;
		uint32_t Reserved1 	: 1;
		uint32_t UDE 		: 1;
		uint32_t CC1DE 		: 1;
		uint32_t CC2DE 		: 1;
		uint32_t CC3DE 		: 1;
		uint32_t CC4DE 		: 1;
		uint32_t COMDE 		: 1;
		uint32_t TDE 		: 1;
		uint32_t Reserved2 	: 17;

	}DIER;

	//volatile uint32_t SR;
	struct
	{

		uint32_t  UIF 		: 1;
		uint32_t  CC1IF 	: 1;
		uint32_t  CC2IF 	: 1;
		uint32_t  CC3IF 	: 1;
		uint32_t  CC4IF 	: 1;
		uint32_t  Reserved 	: 1;
		uint32_t  TIF 		: 1;
		uint32_t  Reserved1 : 2;
		uint32_t  CC1OF 	: 1;
		uint32_t  CC2OF 	: 1;
		uint32_t  CC3OF 	: 1;
		uint32_t  CC4OF 	: 1;
		uint32_t Reserved2 	: 19;

	}SR;
	//volatile uint32_t EGR;
	struct
	{

		uint32_t UG 		: 1;
		uint32_t CC1G 		: 1;
		uint32_t CC2G 		: 1;
		uint32_t CC3G 		: 1;
		uint32_t CC4G 		: 1;
		uint32_t Reserved 	: 1;
		uint32_t TG 		: 1;
		uint32_t Reserved1 	: 25;

	}EGR;
	//volatile uint32_t CCMR1;
	//struct
	//{

		union {

			struct{
				uint32_t CC1S 		: 2;
				uint32_t OC1FE 		: 1;
				uint32_t OC1PE 		: 1;
				uint32_t OC1M 		: 3;
				uint32_t OC1CE 		: 1;
				uint32_t CC2S 		: 2;
				uint32_t OC2FE 		: 1;
				uint32_t OC2PE 		: 1;
				uint32_t OC2M 		: 3;
				uint32_t OC2CE 		: 1;
				uint32_t Reserved1 	: 16;
			}OutputComparemode;

			struct{
				uint32_t CC1S 		: 2;
				uint32_t IC1PSC 	: 2;
				uint32_t IC1F 		: 4;
				uint32_t CC2S 		: 2;
				uint32_t IC2PSC 	: 2;
				uint32_t IC2F 		: 4;
				uint32_t Reserved1 	: 16;
			}InputCapturemode;

		}CCMR1;//_MODE_;

	//}CCMR1;
	//volatile uint32_t CCMR2;
	struct
	{
		union {

			struct{
				uint32_t CC3S 		: 2;
				uint32_t OC3FE 		: 1;
				uint32_t OC3PE 		: 1;
				uint32_t OC3M 		: 3;
				uint32_t OC3CE 		: 1;
				uint32_t CC4S 		: 2;
				uint32_t OC4FE 		: 1;
				uint32_t OC4PE 		: 1;
				uint32_t OC4M 		: 3;
				uint32_t OC4CE 		: 1;
				uint32_t Reserved1 	: 16;
			}OutputComparemode;

			struct{
				uint32_t CC3S 		: 2;
				uint32_t IC3PSC 	: 2;
				uint32_t IC3F 		: 4;
				uint32_t CC4S 		: 2;
				uint32_t IC4PSC 	: 2;
				uint32_t IC4F 		: 4;
				uint32_t Reserved1 	: 16;
			}InputCapturemode;

		}_MODE_;

	}CCMR2;

	//volatile uint32_t CCER;
	struct
	{

		uint32_t CC1E 		: 1;
		uint32_t CC1P 		: 1;
		uint32_t Reserved1 	: 2;
		uint32_t CC2E 		: 1;
		uint32_t CC2P 		: 1;
		uint32_t Reserved2 	: 2;
		uint32_t CC3E 		: 1;
		uint32_t CC3P 		: 1;
		uint32_t Reserved3 	: 2;
		uint32_t CC4E 		: 1;
		uint32_t CC4P 		: 1;
		uint32_t Reserved 	: 18;

	}CCER;

	//volatile uint32_t CNT;
	struct
	{

		uint32_t CNT 		: 16;
		uint32_t Reserved 	: 16;

	}CNT;

	//volatile uint32_t PSC;
	struct
	{

		uint32_t PSC 		: 16;
		uint32_t Reserved 	: 16;

	}PSC;

	//volatile uint32_t ARR;
	struct
	{

		uint32_t ARR 		: 16;
		uint32_t Reserved 	: 16;

	}ARR;

	uint32_t Reserved;

	//volatile uint32_t CCR1;
	struct
	{

		uint32_t CCR1 		: 16;
		uint32_t Reserved 	: 16;

	}CCR1;

	//volatile uint32_t CCR2;
	struct
	{

		uint32_t CCR2 		: 16;
		uint32_t Reserved 	: 16;

	}CCR2;

	//volatile uint32_t CCR3;
	struct
	{

		uint32_t CCR3 		: 16;
		uint32_t Reserved 	: 16;

	}CCR3;

	//volatile uint32_t CCR4;
	struct
	{

		uint32_t CCR4 		: 16;
		uint32_t Reserved 	: 16;

	}CCR4;

	uint32_t Reserved1;

	//volatile uint32_t DCR;
	struct
	{

		uint32_t DBA 		: 5;
		uint32_t Reserved 	: 3;
		uint32_t DBL 		: 5;
		uint32_t Reserved1 	: 19;

	}DCR;

	//volatile uint32_t DMAR;
	struct
	{

		uint32_t DMAR 		: 16;
		uint32_t Reserved 	: 16;

	}DMAR;


}TIM_t;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: ADC
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{

	//volatile uint32_t SR;
	struct
	{

		uint32_t AWD 		: 1;
		uint32_t EOC 		: 1;
		uint32_t JEOC 		: 1;
		uint32_t JSTRT 		: 1;
		uint32_t STRT 		: 1;
		uint32_t Reserved 	: 27;

	}SR;
	//volatile uint32_t CR1;
	struct
	{

		uint32_t AWDCH 			: 5;
		uint32_t EOCIE 			: 1;
		uint32_t AWDIE 			: 1;
		uint32_t JEOC_IE 		: 1;
		uint32_t SCAN 			: 1;
		uint32_t AWD_SGL 		: 1;
		uint32_t JAUTO 			: 1;
		uint32_t DISCEN 		: 1;
		uint32_t JDISCEN 		: 1;
		uint32_t DISCNUM 		: 3;
		uint32_t DUALMOD 		: 4;
		uint32_t Reserved1 		: 2;
		uint32_t AWDEN_JAWDEN 	: 2;
		//uint32_t AWDEN 			: 1;
		uint32_t Reserved 		: 8;

	}CR1;
	//volatile uint32_t CR2;
	struct
	{

		uint32_t ADON 			: 1;
		uint32_t CONT 			: 1;
		uint32_t CAL 			: 1;
		uint32_t RSTCAL 		: 1;
		uint32_t Reserved1 		: 4;
		uint32_t DMA 			: 1;
		uint32_t Reserved2 		: 2;
		uint32_t ALIGN 			: 1;
		uint32_t JEXTSEL 		: 3;
		uint32_t JEXTTRIG 		: 1;
		uint32_t Reserved3 		: 1;
		uint32_t EXTSEL 		: 3;
		uint32_t EXTTRIG 		: 1;
		uint32_t JSWSTART 		: 1;
		uint32_t SWSTART 		: 1;
		uint32_t TSVREFE 		: 1;
		uint32_t Reserved 		: 8;

	}CR2;
	//volatile uint32_t SMPR1;
	struct
	{
		uint32_t Sample_time 		: 32;
	}SMPR1;

	//volatile uint32_t SMPR2;
	struct
	{
		uint32_t Sample_time 		: 32;
	}SMPR2;

	//volatile uint32_t JOFR1;
	struct
	{

		uint32_t JOFFSET1 	: 12;
		uint32_t Reserved2 	: 20;

	}JOFR1;
	//volatile uint32_t JOFR2;
	struct
	{

		uint32_t JOFFSET2 	: 12;
		uint32_t Reserved2 	: 20;

	}JOFR2;
	//volatile uint32_t JOFR3;
	struct
	{

		uint32_t JOFFSET3 	: 12;
		uint32_t Reserved2 	: 20;

	}JOFR3;
	//volatile uint32_t JOFR4;
	struct
	{

		uint32_t JOFFSET4 	: 12;
		uint32_t Reserved2 	: 20;

	}JOFR4;

	//volatile uint32_t HTR;
	struct
	{

		uint32_t HT 		: 12;
		uint32_t Reserved2 	: 20;

	}HTR;

	//volatile uint32_t LTR;
	struct
	{

		uint32_t LT 		: 12;
		uint32_t Reserved 	: 20;

	}LTR;

	//volatile uint32_t SQR1;
	struct
		{

			uint32_t SQR1;

		}SQR1;
	/*struct
	{

		uint32_t SQ13 		: 5;
		uint32_t SQ14 		: 5;
		uint32_t SQ15 		: 5;
		uint32_t SQ16 		: 5;
		uint32_t L 			: 4;
		uint32_t Reserved 	: 8;

	}SQR1;*/

	//volatile uint32_t SQR2;
		struct
			{

				uint32_t SQR2;

			}SQR2;
	/*struct
	{

		uint32_t SQ7 		: 5;
		uint32_t SQ8 		: 5;
		uint32_t SQ9 		: 5;
		uint32_t SQ10 		: 5;
		uint32_t SQ11 		: 5;
		uint32_t SQ12 		: 5;
		uint32_t Reserved 	: 2;

	}SQR2;*/

	//volatile uint32_t SQR3;
			struct
				{

					uint32_t SQR3;

				}SQR3;
	/*struct
	{

		uint32_t SQ1 		: 5;
		uint32_t SQ2 		: 5;
		uint32_t SQ3 		: 5;
		uint32_t SQ4 		: 5;
		uint32_t SQ5 		: 5;
		uint32_t SQ6 		: 5;
		uint32_t Reserved 	: 2;

	}SQR3;*/

	//volatile uint32_t JSQR;
	struct
	{

		uint32_t JSQ1 		: 5;
		uint32_t JSQ2 		: 5;
		uint32_t JSQ3 		: 5;
		uint32_t JSQ4 		: 5;
		uint32_t JL 		: 2;
		uint32_t Reserved 	: 10;

	}JSQR;

	//volatile uint32_t JDR1;
	struct
	{

		uint32_t JDATA 		: 16;
		uint32_t Reserved 	: 16;

	}JDR1;

	//volatile uint32_t JDR2;
	struct
	{

		uint32_t JDATA 		: 16;
		uint32_t Reserved 	: 16;

	}JDR2;

	//volatile uint32_t JDR3;
	struct
	{

		uint32_t JDATA 		: 16;
		uint32_t Reserved 	: 16;

	}JDR3;

	//volatile uint32_t JDR4;
	struct
	{

		uint32_t JDATA 		: 16;
		uint32_t Reserved 	: 16;

	}JDR4;

	//volatile uint32_t DR;
	struct
	{

		uint32_t Regular_DATA 		: 16;
		uint32_t ADC2DATA 			: 16;

	}DR;

}ADC_t;







/*--------------------------------------------Data Type Declaration----------------------------------*/




//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*

#define GPIOA  				((GPIO_t *) GPIOA_BASE)
#define GPIOB  				((GPIO_t *) GPIOB_BASE)
#define GPIOC  				((GPIO_t *) GPIOC_BASE)
#define GPIOD  				((GPIO_t *) GPIOD_BASE)

#define RCC  				((RCC_t *) RCC_BASE)

#define EXTI  				((EXTI_t *) EXTI_BASE)

#define AFIO  				((AFIO_t *) AFIO_BASE)

//@ref USART

#define USART1				((USART_t *)USART1_BASE)
#define USART2				((USART_t *)USART2_BASE)
#define USART3				((USART_t *)USART3_BASE)

//@ref SPI

#define SPI1				((SPI_t *)SPI1_BASE)
#define SPI2				((SPI_t *)SPI2_BASE)

//@ref I2C

#define I2C1				((I2C_t *)I2C1_BASE)
#define I2C2				((I2C_t *)I2C2_BASE)

//@ref TIMER

#define TIM2				((TIM_t *)TIM2_BASE)
#define TIM3				((TIM_t *)TIM3_BASE)
#define TIM4				((TIM_t *)TIM4_BASE)

//@ref ADC

#define ADC1				((ADC_t *)ADC1_BASE)
#define ADC2				((ADC_t *)ADC2_BASE)



//-*-*-*-*-*-*-*-*-*-*-*-
//EXTI IVT IRQ Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define EXTI0				6
#define EXTI1				7
#define EXTI2				8
#define EXTI3				9
#define EXTI4				10
#define EXTI5				23
#define EXTI6				23
#define EXTI7				23
#define EXTI8				23
#define EXTI9				23
#define EXTI10				40
#define EXTI11				40
#define EXTI12				40
#define EXTI13				40
#define EXTI14				40
#define EXTI15				40

#define USART1_ISR			37
#define USART2_ISR			38
#define USART3_ISR			39

#define SPI1_ISR			35
#define SPI2_ISR			36

#define I2C1_ISR_EV			31
#define I2C1_ISR_ER			32
#define I2C2_ISR_EV			33
#define I2C2_ISR_ER			34

#define TIM2_ISR			28
#define TIM3_ISR			29
#define TIM4_ISR			30

#define ADC1_2_ISR			18







//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC ENABLE  Macros:
//-*-*-*-*-*-*-*-*-*-*-*
//EXTI

#define EXTI0_ENABLE    			(NVIC_ISER0|=(1<<EXTI0));
#define EXTI1_ENABLE    			(NVIC_ISER0|=(1<<EXTI1));
#define EXTI2_ENABLE    			(NVIC_ISER0|=(1<<EXTI2));
#define EXTI3_ENABLE    			(NVIC_ISER0|=(1<<EXTI3));
#define EXTI4_ENABLE    			(NVIC_ISER0|=(1<<EXTI4));
#define EXTI5_ENABLE    			(NVIC_ISER0|=(1<<EXTI5));
#define EXTI6_ENABLE    			(NVIC_ISER0|=(1<<EXTI6));
#define EXTI7_ENABLE    			(NVIC_ISER0|=(1<<EXTI7));
#define EXTI8_ENABLE    			(NVIC_ISER0|=(1<<EXTI8));
#define EXTI9_ENABLE    			(NVIC_ISER0|=(1<<EXTI9));
#define EXTI10_ENABLE    			(NVIC_ISER1|=(1<<(EXTI10-32)));
#define EXTI11_ENABLE    			(NVIC_ISER1|=(1<<(EXTI11-32)));
#define EXTI12_ENABLE    			(NVIC_ISER1|=(1<<(EXTI12-32)));
#define EXTI13_ENABLE    			(NVIC_ISER1|=(1<<(EXTI13-32)));
#define EXTI14_ENABLE    			(NVIC_ISER1|=(1<<(EXTI14-32)));
#define EXTI15_ENABLE    			(NVIC_ISER1|=(1<<(EXTI15-32)));

#define USART1_ENABLE_ISR    		(NVIC_ISER1|=(1<<(USART1_ISR-32)));
#define USART2_ENABLE_ISR   		(NVIC_ISER1|=(1<<(USART2_ISR-32)));
#define USART3_ENABLE_ISR    		(NVIC_ISER1|=(1<<(USART3_ISR-32)));

#define SPI1_ENABLE_ISR    			(NVIC_ISER1|=(1<<(SPI1_ISR-32)));
#define SPI2_ENABLE_ISR    			(NVIC_ISER1|=(1<<(SPI2_ISR-32)));

#define SPI_ENABLE_ISR(NUM)    		(NVIC_ISER1|=(1<<(NUM-32)));

#define I2C1_ENABLE_ISR_EV    		(NVIC_ISER0|=(1<<(I2C1_ISR_EV)));//31  ->31
#define I2C1_ENABLE_ISR_ER    		(NVIC_ISER1|=(1<<(I2C1_ISR_ER-32)));
#define I2C2_ENABLE_ISR_EV    		(NVIC_ISER1|=(1<<(I2C2_ISR_EV-32)));//33  ->1
#define I2C2_ENABLE_ISR_ER    		(NVIC_ISER1|=(1<<(I2C2_ISR_ER-32)));

#define I2C_ENABLE_ISR_EV(NUM , ref)    		(NVIC_ISER1|=(1<<(NUM-ref)));
#define I2C_ENABLE_ISR_ER(NUM)    				(NVIC_ISER1|=(1<<(NUM-32)));

#define TIM2_ENABLE_ISR    			(NVIC_ISER0|=(1<<(TIM2_ISR)));
#define TIM3_ENABLE_ISR   			(NVIC_ISER0|=(1<<(TIM3_ISR)));
#define TIM4_ENABLE_ISR    			(NVIC_ISER0|=(1<<(TIM4_ISR)));

#define TIM_ENABLE_ISR(NUM)    		(NVIC_ISER0|=(1<<(NUM)));

#define ADC1_2_ENABLE_ISR    		(NVIC_ISER0|=(1<<(ADC1_2_ISR)));

//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC DISABLE  Macros:
//-*-*-*-*-*-*-*-*-*-*-*
//EXTI

#define EXTI0_DISABLE    			(NVIC_ICER0|=(1<<EXTI0));
#define EXTI1_DISABLE    			(NVIC_ICER0|=(1<<EXTI1));
#define EXTI2_DISABLE    			(NVIC_ICER0|=(1<<EXTI2));
#define EXTI3_DISABLE    			(NVIC_ICER0|=(1<<EXTI3));
#define EXTI4_DISABLE    			(NVIC_ICER0|=(1<<EXTI4));
#define EXTI5_DISABLE    			(NVIC_ICER0|=(1<<EXTI5));
#define EXTI6_DISABLE    			(NVIC_ICER0|=(1<<EXTI6));
#define EXTI7_DISABLE    			(NVIC_ICER0|=(1<<EXTI7));
#define EXTI8_DISABLE    			(NVIC_ICER0|=(1<<EXTI8));
#define EXTI9_DISABLE    			(NVIC_ICER0|=(1<<EXTI9));
#define EXTI10_DISABLE    			(NVIC_ICER1|=(1<<(EXTI10-32)));
#define EXTI11_DISABLE    			(NVIC_ICER1|=(1<<(EXTI11-32)));
#define EXTI12_DISABLE    			(NVIC_ICER1|=(1<<(EXTI12-32)));
#define EXTI13_DISABLE    			(NVIC_ICER1|=(1<<(EXTI13-32)));
#define EXTI14_DISABLE    			(NVIC_ICER1|=(1<<(EXTI14-32)));
#define EXTI15_DISABLE    			(NVIC_ICER1|=(1<<(EXTI15-32)));


#define USART1_DISABLE_IRQ    		(NVIC_ICER1|=(1<<(USART1_ISR-32)));
#define USART2_DISABLE_IRQ   		(NVIC_ICER1|=(1<<(USART2_ISR-32)));
#define USART3_DISABLE_IRQ    		(NVIC_ICER1|=(1<<(USART3_ISR-32)));

#define SPI1_DISABLE_IRQ    		(NVIC_ICER1|=(1<<(SPI1_ISR-32)));
#define SPI2_DISABLE_IRQ    		(NVIC_ICER1|=(1<<(SPI2_ISR-32)));

#define I2C1_DISABLE_IRQ_EV    		(NVIC_ICER0|=(1<<(I2C1_ISR_EV)));
#define I2C1_DISABLE_IRQ_ER    		(NVIC_ICER1|=(1<<(I2C1_ISR_ER-32)));
#define I2C2_DISABLE_IRQ_EV    		(NVIC_ICER1|=(1<<(I2C2_ISR_EV-32)));
#define I2C2_DISABLE_IRQ_ER    		(NVIC_ICER1|=(1<<(I2C2_ISR_ER-32)));

#define TIM2_DISABLE_IRQ    		(NVIC_ICER0|=(1<<(TIM2_ISR)));
#define TIM3_DISABLE_IRQ   			(NVIC_ICER0|=(1<<(TIM3_ISR)));
#define TIM4_DISABLE_IRQ    		(NVIC_ICER0|=(1<<(TIM4_ISR)));


#define ADC1_2_DISABLE_IRQ    		(NVIC_ICER0|=(1<<(ADC1_2_ISR)));

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define Rest_controller















#endif /* INC_STM32F103C6_LQFP48_H_ */
