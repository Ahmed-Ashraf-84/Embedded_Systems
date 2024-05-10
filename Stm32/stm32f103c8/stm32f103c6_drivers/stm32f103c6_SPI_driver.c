/*
 * stm32f103c6_SPI_driver.c
 *
 *  Created on: Oct 4, 2023
 *      Author: Ahmed Ashraf
 */

#include "stm32f103c6_SPI_driver.h"

SPI_config_t (*G_ISR_config[2]) ;


#define Bit_Mask    		0b1
#define SPI_enabled    		1
#define SPI_disabled    	0
#define SPI_Index			SPIx_temp-35

#define SPI_Pin_config(port , pin , mode , speed)				pinconfig.GPIO_PIN_Number = pin;\
																pinconfig.GPIO_MODE = mode ;\
																pinconfig.GPIO_OUTPUT_SPEED = speed ;\
																GPIO_init(port, &pinconfig);


// %10 -> *2 -> +2

void SPI_init(SPI_config_t * SPI)
{
	uint8_t SPIx_temp ;
	if(SPI->SPIx == SPI1)
	{
		SPIx_temp = SPI1_ISR;//35
		CLK_SPI1_EN
	}
	else
	{
		SPIx_temp = SPI2_ISR;//36
		CLK_SPI2_EN
	}

	// SPI_Device_Mode
	SPI->SPIx->CR1.MSTR = SPI->Device_Mode;
	// SPI_CLK_Frequency
	SPI->SPIx->CR1.BR = SPI->CLK_Frequency;
	// SPI_CLK_polarity_phase
	SPI->SPIx->CR1.CPHA_CPOL = SPI->CLK_polarity_phase;
	// SPI_Communication_Mode
	SPI->SPIx->CR1.BIDIOE_BIDIMODE = ((SPI->Communication_Mode)>>1 ) & 0b11;
	SPI->SPIx->CR1.RXONLY = (SPI->Communication_Mode) & Bit_Mask;
	// SPI_Data_size
	SPI->SPIx->CR1.DFF  = SPI->Data_size;
	// SPI_LSB_MSB
	SPI->SPIx->CR1.LSBFIRST = SPI->LSB_MSB;
	// SPI_NSS_HW_SW
	SPI->SPIx->CR1.SSM  = ((SPI->NSS_HW_SW)>>2) & Bit_Mask;
	SPI->SPIx->CR2.SSOE = ((SPI->NSS_HW_SW)>>1) & Bit_Mask;
	SPI->SPIx->CR1.SSI  = (SPI->NSS_HW_SW) & Bit_Mask;
	// SPI_enable
	SPI->SPIx->CR1.SPE  = SPI_enabled ;
	//interrupt
	if(SPI->Interrupt_Enable != interrupt_DISABLED)
	{
		SPI->SPIx->CR2.ERRIE_RXNEIE_TXEIE = SPI->Interrupt_Enable ;
		SPI_ENABLE_ISR(SPIx_temp)
		G_ISR_config[SPI_Index] = SPI ;
	}
}


void SPI_RST(SPI_config_t * SPI)
{
	if(SPI->SPIx == SPI1)
	{
		SPI1_DISABLE_IRQ
		CLK_SPI1_RST
	}
	else
	{
		SPI2_DISABLE_IRQ
		CLK_SPI2_RST
	}
}

void SPI_Send_data(SPI_config_t * SPI)
{
	if(SPI->polling == polling_ENABLED)
		while(! (SPI->SPIx->SR.TXE));
	SPI->SPIx->DR = *(SPI->Buffer) ;

}

void SPI_Receive_data(SPI_config_t * SPI)
{
	if(SPI->polling == polling_ENABLED)
		while(! (SPI->SPIx->SR.RXNE));
	*(SPI->Buffer)= SPI->SPIx->DR  ;

}

void SPI_TX_RX(SPI_config_t * SPI)
{
	SPI_Send_data(SPI);
	SPI_Receive_data(SPI);
}

void SPI_AFIO_Set_Pins(SPI_config_t * SPI)
{
	GPIO_PIN_config_t pinconfig ;
	//1 => A 4 5 6 7 //nss - sclk - miso -mosi
	if(SPI->SPIx == SPI1)
	{
		//NSS
		if(SPI->NSS_HW_SW == HW_output_disabled)
			SPI_Pin_config(GPIOA,PIN4,MODE_INPUT_FLO,OUTPUT_SPEED_10)

		if(SPI->Device_Mode == Master)
		{
			//SCLK
			SPI_Pin_config(GPIOA,PIN5,MODE_OUTPUT_AF_PP,OUTPUT_SPEED_10)
			//NSS
			if(SPI->NSS_HW_SW == HW_output_enabled)
			{
				SPI_Pin_config(GPIOA,PIN4,MODE_OUTPUT_AF_PP,OUTPUT_SPEED_10)
			}
			//MOSI
				SPI_Pin_config(GPIOA,PIN7,MODE_OUTPUT_AF_PP,OUTPUT_SPEED_10)
			//MISO
				if(SPI->Communication_Mode == FULL_Duplex)
					SPI_Pin_config(GPIOA,PIN6,MODE_INPUT_FLO,OUTPUT_SPEED_10)
		}
		else//slave
		{
			//SCLK
			SPI_Pin_config(GPIOA,PIN5,MODE_INPUT_FLO,OUTPUT_SPEED_10)
			//MOSI
			if(SPI->Communication_Mode == FULL_Duplex)
				SPI_Pin_config(GPIOA,PIN7,MODE_INPUT_FLO,OUTPUT_SPEED_10)
			//MISO
			if(SPI->Slave == multi_slave)
			{
				SPI_Pin_config(GPIOA,PIN6,MODE_OUTPUT_AF_OD,OUTPUT_SPEED_10)
			}
			else
			{
				SPI_Pin_config(GPIOA,PIN6,MODE_OUTPUT_AF_PP,OUTPUT_SPEED_10)
			}
		}
	}
	else//SPI2
	{
		//NSS
		if(SPI->NSS_HW_SW == HW_output_disabled)
			SPI_Pin_config(GPIOB,PIN12,MODE_INPUT_FLO,OUTPUT_SPEED_10)

		if(SPI->Device_Mode == Master)
		{
			//SCLK
			SPI_Pin_config(GPIOB,PIN13,MODE_OUTPUT_AF_PP,OUTPUT_SPEED_10)
			//NSS
			if(SPI->NSS_HW_SW == HW_output_enabled)
			{
				SPI_Pin_config(GPIOB,PIN12,MODE_OUTPUT_AF_PP,OUTPUT_SPEED_10)
			}
			//MOSI
				SPI_Pin_config(GPIOB,PIN15,MODE_OUTPUT_AF_PP,OUTPUT_SPEED_10)
			//MISO
				if(SPI->Communication_Mode == FULL_Duplex)
					SPI_Pin_config(GPIOB,PIN14,MODE_INPUT_FLO,OUTPUT_SPEED_10)
		}
		else//slave
		{
			//SCLK
			SPI_Pin_config(GPIOB,PIN13,MODE_INPUT_FLO,OUTPUT_SPEED_10)
			//MOSI
			if(SPI->Communication_Mode == FULL_Duplex)
				SPI_Pin_config(GPIOB,PIN15,MODE_INPUT_FLO,OUTPUT_SPEED_10)
			//MISO
			if(SPI->Slave == multi_slave)
			{
				SPI_Pin_config(GPIOB,PIN14,MODE_OUTPUT_AF_OD,OUTPUT_SPEED_10)
			}
			else
			{
				SPI_Pin_config(GPIOB,PIN14,MODE_OUTPUT_AF_PP,OUTPUT_SPEED_10)
			}
		}
	}



	//2 => B 12 13 14 15//nss - sclk - miso -mosi

}

void SPI2_IRQHandler (void)
{
	G_ISR_config[1]->Ptr_IRQ();
}

void SPI1_IRQHandler (void)
{
	G_ISR_config[0]->Ptr_IRQ();
}


