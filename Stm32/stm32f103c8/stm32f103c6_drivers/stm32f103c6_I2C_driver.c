/*
 * stm32f103c6_I2C_driver.c
 *
 *  Created on: Oct 10, 2023
 *      Author: Ahmed Ashraf
 */


//-----------------------------
//Includes
//-----------------------------
#include "stm32f103c6_I2C_driver.h"


// program I2C_CR2_FREQ according to sm mode - fm mode   ----  TRISE[5:0]
//(I2C_OAR1) =>>Bit 14 Should always be kept at 1 by software

//#define Set_bit()

#define read		 1
#define write		 0

#define ADD_read		I2C->I2Cx->DR = (uint8_t) ((Des_Add<<1) | read ) ;
#define ADD_write		I2C->I2Cx->DR = (uint8_t) ((Des_Add<<1) | write ) ;



#define I2C_Pin_config(port , pin , mode , speed)				pinconfig.GPIO_PIN_Number = pin;\
																pinconfig.GPIO_MODE = mode ;\
																pinconfig.GPIO_OUTPUT_SPEED = speed ;\
																GPIO_init(port, &pinconfig);


void I2C_init(I2C_config_t * I2C)
{
	uint8_t I2Cx_temp[3]={0} ;//EV-ref-ER
	if(I2C->I2Cx == I2C1)
	{
		I2Cx_temp[0] = I2C1_ISR_EV;
		I2Cx_temp[1] = 0;//31 ->> 31
		I2Cx_temp[2] = I2C1_ISR_ER;
		CLK_I2C1_EN
	}
	else
	{
		I2Cx_temp[0] = I2C2_ISR_EV;
		I2Cx_temp[1] = 32;//33 ->> 1
		I2Cx_temp[2] = I2C2_ISR_ER;
		CLK_I2C2_EN
	}

	I2C->I2Cx->CR1.SMBUS = I2C->Peripheral_mode ;
	if(I2C->Peripheral_mode == I2C_mode)
	{

		I2C->I2Cx->CR1.ACK = I2C->ACK_enable ;
		I2C->I2Cx->CR1.ENGC = I2C->General_call_ADD ;
		if(I2C->I2C_mode == Master)
		{
			uint8_t temp =0;
			//Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
			temp = (RCC_GET_PCLK1_CLK() / 1000000 );
			I2C->I2Cx->CR2.FREQ = temp ; // 2 MHZ to 36 MHZ

			I2C->I2Cx->CCR.F_S = I2C->I2C_SM_FM ;
			if(I2C->I2C_SM_FM == SM)
			{
				//Configure the clock control registers
				I2C->I2Cx->CCR.CCR  = CCR_calc(I2C->SCLK_FREQ);
			}
			else
			{
				// not  supported
			}

			//Configure the rise time register
			I2C->I2Cx->TRISE.TRISE = temp+1 ;



		}
		else
		{
			I2C->I2Cx->CR1.NO_STRETCH = I2C->stretch_mode ;
			I2C->I2Cx->OAR1.ADD_MODE = I2C->Slave_config.add_mode ;
			I2C->I2Cx->OAR2.ENDUAL = I2C->Slave_config.dual_mode;
			I2C->I2Cx->OAR1.ADD_1_7 = I2C->Slave_config.Primary_Slave_ADD ;
			I2C->I2Cx->OAR2.ADD2 = I2C->Slave_config.Secondary_Slave_ADD ;

			I2C->I2Cx->CR2.ITBUFEN = IRQ_ENABLED ;
			I2C->I2Cx->CR2.ITERREN = IRQ_ENABLED ;
			I2C->I2Cx->CR2.ITEVTEN = IRQ_ENABLED ;
			I2C_ENABLE_ISR_ER(I2Cx_temp[2])
			I2C_ENABLE_ISR_EV(I2Cx_temp[0],I2Cx_temp[1])

		}
		I2C->I2Cx->CR1.PE = ENABLED;
	}
	else
	{
		// not  supported
	}




}
void I2C_RST(I2C_config_t * I2C)
{
	if(I2C->I2Cx == I2C1)
	{
		I2C1_DISABLE_IRQ_ER
		I2C1_DISABLE_IRQ_EV
		CLK_I2C1_RST
	}
	else
	{
		I2C2_DISABLE_IRQ_ER
		I2C2_DISABLE_IRQ_EV
		CLK_I2C2_RST
	}
}
void I2C_AFIO_Set_Pins(I2C_config_t * I2C)
{
	GPIO_PIN_config_t pinconfig ;

	if(I2C->I2Cx == I2C1)
	{
		I2C_Pin_config(GPIOB,PIN6,MODE_OUTPUT_AF_OD,OUTPUT_SPEED_10)
		I2C_Pin_config(GPIOB,PIN7,MODE_OUTPUT_AF_OD,OUTPUT_SPEED_10)
	}
	else
	{
		I2C_Pin_config(GPIOB,PIN10,MODE_OUTPUT_AF_OD,OUTPUT_SPEED_10)
		I2C_Pin_config(GPIOB,PIN11,MODE_OUTPUT_AF_OD,OUTPUT_SPEED_10)
	}
}
void I2C_Master_TX(I2C_config_t * I2C,uint16_t Des_Add ,uint8_t * Data ,uint8_t Data_length )
{
	uint8_t counter =0;
	while( I2C->I2Cx->SR2.BUSY );
	I2C->I2Cx->CR1.START = SET_bit ;//generate start
	while( !(I2C->I2Cx->SR1.SB) );  // EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	ADD_write //macro
	while( !(I2C->I2Cx->SR1.ADDR) );//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while( !((I2C->I2Cx->SR2.MSL)&(I2C->I2Cx->SR2.TRA)&(I2C->I2Cx->SR2.BUSY)) ); //EV6 con.
	while( !(I2C->I2Cx->SR1.TxE) );//EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR
	for(counter=0;counter < Data_length;counter++ )
	{
		I2C->I2Cx->DR = Data[counter] ;
		while( !(I2C->I2Cx->SR1.TxE) );//EV8: TxE=1, shift register not empty, d. ata register empty, cleared by writing DR register
	}
	while( !(I2C->I2Cx->SR1.BTF) );
	I2C->I2Cx->CR1.STOP = SET_bit ;

}
void I2C_Master_RX(I2C_config_t * I2C,uint16_t Des_Add ,uint8_t * Data ,uint8_t Data_length )
{
	uint8_t counter =0;
	while( I2C->I2Cx->SR2.BUSY );
	I2C->I2Cx->CR1.START = SET_bit ;//generate start
	while( !(I2C->I2Cx->SR1.SB) );  // EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	ADD_read //macro
	while( !(I2C->I2Cx->SR1.ADDR) );//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while( (I2C->I2Cx->SR2.TRA) );
	if(Data_length==1)
	{
		I2C->I2Cx->CR1.ACK = RESET_bit ;
		I2C->I2Cx->CR1.STOP = RESET_bit ;
		Data[counter] = I2C->I2Cx->DR;
	}
	else
	{
		for(counter=0;counter < Data_length;counter++)
		{
			while( !(I2C->I2Cx->SR1.RxNE) );
			Data[counter] = I2C->I2Cx->DR;
			if(counter == Data_length-2 )
			{
				I2C->I2Cx->CR1.ACK = RESET_bit ;
				I2C->I2Cx->CR1.STOP = RESET_bit ;
			}
		}
	}

	I2C->I2Cx->CR1.ACK = I2C->ACK_enable ;

}

