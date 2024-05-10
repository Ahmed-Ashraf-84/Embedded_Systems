/**
 ******************************************************************************
 * @file           : stm32f103c6_RCC_driver.c
 * @author         : Ahmed Ashraf Mahgob Ahmed
 * @brief          : Contain the code to Control Reset and clock control
 ******************************************************************************
**/

/*--------------------------------------------Includes Start----------------------------------*/
#include "stm32f103c6_RCC_driver.h"
#include "stm32f103c6_GPIO_driver.h"
/*--------------------------------------------Includes End----------------------------------*/

/*--------------------------------------------Macro Declaration----------------------------------*/


/*--------------------------------------------Macro Declaration----------------------------------*/

/*--------------------------------------------Macro Functions Declaration----------------------------------*/
/*--------------------------------------------Macro Functions Declaration----------------------------------*/

/*--------------------------------------------Data Type Declaration----------------------------------*/
static ptr_function ptr_handler;
static ptr_function ptr_failure_handler;



/*--------------------------------------------Data Type Declaration----------------------------------*/

/*--------------------------------------------Software Interface Declaration-------------------------------*/

/**
 * 	@brief			Initialize RCC
 *  @details		configure the system clock and select which oscillator to operate (HSI-HSE-LSI-LSE)
 *  				and specify the prescaler of AHB and APB1 and APB2 , USB . specify the frequency
 *  				of the PERIPHERALS and system tick and flash memory
 *  @parameter[in]  prescaler struct the include the numbers of prescaler of AHB ,APB ,APB2,USB
 *  @note			only one oscillator can be initialize and configure at a time
 *  @note
 */
RetStatus_t RCC_SYS_CLK_Config(RCC_CONFIG_t* CLK_SRC,ptr_function IRQ_handler)
{
	RetStatus_t ret_value =MCAL_OK;
	//uint32_t register_temp = 0UL;
	if(CLK_SRC == NULL )
	{
		ret_value =MCAL_NOK;
	}
	else
	{
		if (CLK_SRC->CLK_Source_Selection == RCC_HSE_CLK_Source)
		{
			//AFIO Port D0/Port D1 mapping on OSC_IN/OSC_OUT
			SET_BIT(AFIO->MAPR,AFIO_MAPR_PD01_REMAP_Mask );
			//config bypass bit
			SET_BIT(RCC->CR,CLK_SRC->External_oscillator << RCC_CR_HSEBYP_Pos );
			//HSE ON
			SET_BIT(RCC->CR,RCC_CR_HSEON_Mask );
			//set RCC control register to register_temp
			/*RCC->CR = MODIFY_REG(RCC->CR,(RCC_CR_HSEBYP_Mask |RCC_CR_HSEON_Mask ),register_temp);*/

			if(CLK_SRC->mechanism == Interrupt)
			{
				SET_BIT(RCC->CIR,RCC_CIR_HSERDYIE_Mask );
				ptr_handler = IRQ_handler ;
			}
			else if (CLK_SRC->mechanism == Polling)
			{
				while(!READ_BIT(RCC->CR,RCC_CR_HSERDY_Mask));
			}
			else{}
		}
		else if (CLK_SRC->CLK_Source_Selection  == RCC_HSI_CLK_Source)
		{
			SET_BIT(RCC->CR,RCC_CR_HSION_Mask );
#if (HSI_Calibration == HSI_Calibration_ON)
			uint16_t temp_1 = 0 ,temp_2 = 0;
			temp_1 = READ_BIT(RCC->CR,RCC_CR_HSITRIM_Mask);
			temp_2 = READ_BIT(RCC->CR,RCC_CR_HSICAL_Mask);
			//SET_BIT(RCC->CR,(temp_1 + temp_2)<<RCC_CR_HSICAL_Pos);

#elif (HSI_Calibration == HSI_Calibration_OFF)

#else
			ret_value =MCAL_NOK;
#endif
			if(CLK_SRC->mechanism == Interrupt)
			{
				SET_BIT(RCC->CIR,RCC_CIR_HSIRDYIE_Mask );
				ptr_handler = IRQ_handler ;
			}
			else if (CLK_SRC->mechanism == Polling)
			{
				while(!READ_BIT(RCC->CR,RCC_CR_HSIRDY_Mask));
			}
			else{}
		}
		else if (CLK_SRC->CLK_Source_Selection  == RCC_PLL_CLK_Source)
		{
			//ret_value = RCC_CLK_prescaler(prescaler);
			SET_BIT(RCC->CFGR,CLK_SRC->PLL_HSE_prescaler << RCC_CFGR_PLLXTPRE_Pos );
			SET_BIT(RCC->CFGR,CLK_SRC->PLL_Multiplier << RCC_CFGR_PLLMUL_Pos );
#if(PLL_Multiplier_Entry == HSE_divided_1_PLL_MUL)

			SET_BIT(RCC->CFGR,RCC_CFGR_PLLSRC_Mask );

#elif(PLL_Multiplier_Entry == HSI_divided_2_PLL_MUL)

			CLEAR_BIT(RCC->CFGR,RCC_CFGR_PLLSRC_Mask );

#else
			ret_value =MCAL_NOK;
#endif
			SET_BIT(RCC->CR,RCC_CR_PLLON_Mask );

			if(CLK_SRC->mechanism == Interrupt)
			{
				SET_BIT(RCC->CIR,RCC_CIR_PLLRDYIE_Mask );
				ptr_handler = IRQ_handler ;
			}
			else if (CLK_SRC->mechanism == Polling)
			{
				while(!READ_BIT(RCC->CR,RCC_CR_PLLRDY_Mask));
			}
			else{}
		}
		else if (CLK_SRC->CLK_Source_Selection  == RCC_LSI_CLK_Source)
		{
			SET_BIT(RCC->CR,RCC_CSR_LSION_Mask );

			if(CLK_SRC->mechanism == Interrupt)
			{
				SET_BIT(RCC->CIR,RCC_CIR_LSIRDYIE_Mask );
				ptr_handler = IRQ_handler ;
			}
			else if (CLK_SRC->mechanism == Polling)
			{
				while(!READ_BIT(RCC->CR,RCC_CSR_LSIRDY_Mask));
			}
			else{}
		}
		else if (CLK_SRC->CLK_Source_Selection  == RCC_LSE_CLK_Source)
		{
			//config bypass bit
			SET_BIT(RCC->BDCR,CLK_SRC->External_oscillator << RCC_BDCR_LSEBYP_Pos );
			//HSE ON
			SET_BIT(RCC->BDCR,RCC_BDCR_LSEON_Mask );
			//set RCC control register to register_temp
			/*RCC->CR = MODIFY_REG(RCC->CR,(RCC_CR_HSEBYP_Mask |RCC_CR_HSEON_Mask ),register_temp);*/

			if(CLK_SRC->mechanism == Interrupt)
			{
				SET_BIT(RCC->CIR,RCC_CIR_LSERDYIE_Mask );
				ptr_handler = IRQ_handler ;
			}
			else if (CLK_SRC->mechanism == Polling)
			{
				while(!READ_BIT(RCC->BDCR,RCC_BDCR_LSERDY_Mask));
			}
			else{}
		}
		else{/*nothing*/}
	}
	return (ret_value) ;
}


RetStatus_t RCC_CLK_prescaler(RCC_PRESCALER_t * prescaler)
{
	RetStatus_t ret_value = MCAL_OK ;
	if(prescaler == NULL)
	{
		ret_value = MCAL_NOK ;
	}
	else
	{
		SET_BIT(RCC->CFGR ,prescaler->USB_prescaler <<RCC_CFGR_USBPRE_Pos);
		SET_BIT(RCC->CFGR ,prescaler->ADC_prescaler <<RCC_CFGR_ADCPRE_Pos);
		SET_BIT(RCC->CFGR ,prescaler->APB2_prescaler <<RCC_CFGR_PPRE2_Pos);
		SET_BIT(RCC->CFGR ,prescaler->APB1_prescaler <<RCC_CFGR_PPRE1_Pos);
		SET_BIT(RCC->CFGR ,prescaler->AHB_prescaler <<RCC_CFGR_HPRE_Pos);
	}
	return (ret_value) ;
}

RetStatus_t RCC_SYS_CLK_Selection(void)
{
	RetStatus_t ret_value = MCAL_OK ;
#if   (RCC_CLK_Source_Selection == RCC_HSE_CLK_Source)

	SET_BIT(RCC->CFGR ,RCC_HSE_CLK_Source <<RCC_CFGR_SW_Pos);

#elif (RCC_CLK_Source_Selection == RCC_PLL_CLK_Source)

	SET_BIT(RCC->CFGR ,RCC_PLL_CLK_Source <<RCC_CFGR_SW_Pos);

#elif (RCC_CLK_Source_Selection== RCC_HSI_CLK_Source)

	SET_BIT(RCC->CFGR ,RCC_HSI_CLK_Source <<RCC_CFGR_SW_Pos);

#else
	ret_value = MCAL_NOK ;
#endif

	return (ret_value) ;
}

Sys_CLK_status_t RCC_Get_SYS_CLK_Source(void)
{
	Sys_CLK_status_t ret_value = Error;
	ret_value = READ_BIT(RCC->CFGR ,RCC_CFGR_SWS_Mask);

	return (ret_value) ;
}


/*RetStatus_t RCC_Clock_security_Init(ptr_function IRQ_failure_handler)
{
	RetStatus_t ret_value = MCAL_OK ;
	if(IRQ_failure_handler == NULL)
	{
		ret_value = MCAL_NOK ;
	}
	else
	{
		SET_BIT(RCC->CR , RCC_CR_CSSON_Mask);
		ptr_failure_handler = IRQ_failure_handler ;
	}
	return (ret_value) ;
}*/
void RCC_Clock_security_Init(ptr_function IRQ_failure_handler)
{
	SET_BIT(RCC->CR , RCC_CR_CSSON_Mask);
	ptr_failure_handler = IRQ_failure_handler ;
}

void RCC_RTC_CLK_Init(void)
{
	uint8_t temp_register = 0 ;
	temp_register = READ_BIT(RCC->BDCR ,(RCC_BDCR_LSEON_Mask | RCC_BDCR_LSEBYP_Mask));
	SET_BIT(RCC->BDCR ,RCC_BDCR_BDRST_Mask);
	RCC->BDCR = MODIFY_REG(RCC->BDCR ,(RCC_BDCR_LSEON_Mask | RCC_BDCR_LSEBYP_Mask) ,(uint32_t)temp_register);

#if(RTC_clock_source_selection == HSE_divided_128)

	SET_BIT(RCC->BDCR ,HSE_divided_128<<RCC_BDCR_RTCSEL_Pos);

#elif(RTC_clock_source_selection == LSI)

	SET_BIT(RCC->BDCR ,LSI<<RCC_BDCR_RTCSEL_Pos);

#elif(RTC_clock_source_selection == LSE)

	SET_BIT(RCC->BDCR ,LSE<<RCC_BDCR_RTCSEL_Pos);

#endif
	SET_BIT(RCC->BDCR ,RCC_BDCR_RTCEN_Mask);
}

void RCC_MCU_CLK_OutPut(void)
{
	GPIO_PIN_config_t PinConfig = {PIN8,MODE_OUTPUT_AF_PP,OUTPUT_SPEED_50};

	GPIO_init(GPIOA,&PinConfig);

#if(MCU_CLK_output_selection == System_clock)

	SET_BIT(RCC->CFGR ,System_clock<<RCC_CFGR_MCO_Pos);

#elif(MCU_CLK_output_selection == HSI_clock)

	SET_BIT(RCC->CFGR ,HSI_clock<<RCC_CFGR_MCO_Pos);

#elif(MCU_CLK_output_selection == HSE_clock)

	SET_BIT(RCC->CFGR ,HSE_clock<<RCC_CFGR_MCO_Pos);

#elif(MCU_CLK_output_selection == PLL_divided_2_clock)

	SET_BIT(RCC->CFGR ,PLL_divided_2_clock<<RCC_CFGR_MCO_Pos);

#elif(MCU_CLK_output_selection == No_clock)

#endif
}


uint32_t RCC_GET_SYS_CLK(void)
{
	//Bits 3:2 SWS[1:0]: System clock switch status
	//Set and cleared by hardware to indicate which clock source is used as system clock.
	//00: HSI oscillator used as system clock
	//01: HSE oscillator used as system clock
	//10: PLL used as system clock
	//11: Not applicable
	uint32_t SYS_CLK = 0;
	switch((RCC->CFGR >> 2) & 0x3 )
	{
	case 0 :
		SYS_CLK = HSI_SYS_CLK ;
		break;
	case 1 :
		SYS_CLK = HSE_SYS_CLK ;
		break;
	case 2 :
		SYS_CLK = PLL_SYS_CLK ;
		break;
	}

	return(SYS_CLK);

}
uint32_t RCC_GET_PCLK1_CLK(void)
{
	uint32_t PCLK1_CLK =0;

		if((RCC->CFGR)>>10 & 0x1)
		{
			PCLK1_CLK = (RCC_GET_SYS_CLK()) >> ((((RCC->CFGR)>>8) & 0x3 )+1);
		}
		else
		{
			PCLK1_CLK = RCC_GET_SYS_CLK() ;
		}


		return (PCLK1_CLK);

}
uint32_t RCC_GET_PCLK2_CLK(void)
{
	uint32_t PCLK2_CLK =0;

		if((RCC->CFGR)>>13 & 0x1)
		{
			PCLK2_CLK = (RCC_GET_SYS_CLK()) >> ((((RCC->CFGR)>>11) & 0x3 )+1);
		}
		else
		{
			PCLK2_CLK = RCC_GET_SYS_CLK() ;
		}


		return (PCLK2_CLK);
}
uint32_t RCC_GET_HCLK_CLK(void)
{
	uint32_t HCLK_CLK =0;

	if((RCC->CFGR)>>7 & 0x1)
	{
		HCLK_CLK = (RCC_GET_SYS_CLK()) >> ((((RCC->CFGR)>>4) & 0x7 )+1);
	}
	else
	{
		HCLK_CLK = RCC_GET_SYS_CLK() ;
	}


	return (HCLK_CLK);

}

void RCC_IRQHandler(void)
{
	SET_BIT(RCC->CIR,RCC_CIR_HSERDYC_Mask);//clear flag This bit is cleared by setting
	SET_BIT(RCC->CIR,RCC_CIR_HSIRDYC_Mask);//clear flag This bit is cleared by setting
	SET_BIT(RCC->CIR,RCC_CIR_PLLRDYC_Mask);//clear flag This bit is cleared by setting
	SET_BIT(RCC->CIR,RCC_CIR_LSERDYC_Mask);//clear flag This bit is cleared by setting
	SET_BIT(RCC->CIR,RCC_CIR_LSIRDYC_Mask);//clear flag This bit is cleared by setting

	if(ptr_handler!=NULL)
	{
		ptr_handler();
	}


}

void NMI_Handler(void)
{
	SET_BIT(RCC->CIR,RCC_CIR_CSSC_Mask);//clear flag This bit is cleared by setting

	if(ptr_failure_handler!=NULL)
	{
		ptr_failure_handler();
	}
}


/*--------------------------------------------Software Interface Declaration-------------------------------*/
