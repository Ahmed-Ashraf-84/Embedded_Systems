/*
 * stm32f103c6_ADC_driver.c
 *
 *  Created on: Nov 30, 2023
 *      Author: Ahmed Ashraf
 */


#include "stm32f103c6_ADC_driver.h"
#include "stm32f103c6_TIMER_driver.h"


#define   conv(y,z,v)				y ## z ## v

#define   temp(x)				conv(ADCx->Init->regular_config->conversions_ ,x,_th )

//#define	 reg(x)					ADCx->Instance->JSQR.JSQ ## x

#define   tempp(x)				ADCx->Init->sample_time_config->channel_##x

TIM_Handle_t tim2 ;


uint16_t calibration;

void(*ptr_ISR_AWD)(void);
void(*ptr_ISR_EOC)(void);

void ADC_Init(ADC_Handle_t *ADCx)
{
	//**********************		Timer		******************************

	TIM_Base_Init_t ink;

	//tim2.ISR_Handler = ISR ; explain ADC calibration in stm32f103c6
	tim2.TIM_mode = TIM_mode ;
	tim2.handler = interrupt ;
	tim2.Init  = &ink;
	tim2.Init->CounterMode = upcounter ;
	tim2.Init->Period = 3 ;
	tim2.Init->Prescaler = 20 ;		// .5 u	T	===>
	tim2.Instance  = TIM2 ;
	TIM_init(&tim2);
//*************************************************************************************************
	uint8_t temp_arr[16]={temp(1),temp(2),temp(3),temp(4),temp(5),temp(6),temp(7),temp(8),temp(9),temp(10),
						  temp(11),temp(12),temp(13),temp(14),temp(15),temp(16)};

	uint8_t counter=0;
	if(ADCx->Instance == ADC1)
	{
		//CLK_ADC1_RST
		ADC1_2_DISABLE_IRQ
		CLK_ADC1_EN
	}
	else if(ADCx->Instance == ADC2)
	{
		CLK_ADC2_RST
		ADC1_2_DISABLE_IRQ
		CLK_ADC2_EN
	}
	else{/*no thing */}

	RCC->CFGR = ((ADCx->Init->ClockPrescaler)<<14) ;
	/* wake up the ADC */
	ADCx->Instance->CR2.ADON = enabled ;
	//calibration
	while(!(tim2.Instance->SR.UIF)); //polling for 2 ADC cycle
	ADCx->Instance->CR2.CAL = enabled ;
	/*align*/
	ADCx->Instance->JOFR1.JOFFSET1 = ADCx->Init->injected_channel_offset ; //for
	ADCx->Instance->CR2.ALIGN = ADCx->Init->alignment ;

	/*channel selection */
	//regular**************************************************************
	ADCx->Instance->SQR1.SQR1 = (ADCx->Init->regular_config->NbrOfConversion)<<(20) ;

	for(counter=0;counter<=(ADCx->Init->regular_config->NbrOfConversion);counter++)
	{
		if(counter<6)
			ADCx->Instance->SQR3.SQR3 |= ((uint32_t)(temp_arr[counter]))<<(counter*5) ;
		if(counter>=6 && counter<12)
			ADCx->Instance->SQR2.SQR2 |= ((uint32_t)(temp_arr[counter]))<<(counter*5) ;
		if(counter>=12)
			ADCx->Instance->SQR1.SQR1 |= ((uint32_t)(temp_arr[counter]))<<(counter*5) ;
	/*	ADCx->Instance->SQR3.SQ1 = ADCx->Init->regular_config->conversions_1_th ;
		ADCx->Instance->SQR3.SQ2 = ADCx->Init->regular_config->conversions_2_th ;
		ADCx->Instance->SQR3.SQ3 = ADCx->Init->regular_config->conversions_3_th ;
		ADCx->Instance->SQR3.SQ4 = ADCx->Init->regular_config->conversions_4_th ;
		ADCx->Instance->SQR3.SQ5 = ADCx->Init->regular_config->conversions_5_th ;
		ADCx->Instance->SQR3.SQ6 = ADCx->Init->regular_config->conversions_6_th ;
		ADCx->Instance->SQR2.SQ7 = ADCx->Init->regular_config->conversions_7_th ;
		ADCx->Instance->SQR2.SQ8 = ADCx->Init->regular_config->conversions_8_th ;
		ADCx->Instance->SQR2.SQ9 = ADCx->Init->regular_config->conversions_9_th ;
		ADCx->Instance->SQR2.SQ10 = ADCx->Init->regular_config->conversions_10_th ;
		ADCx->Instance->SQR2.SQ11 = ADCx->Init->regular_config->conversions_11_th ;
		ADCx->Instance->SQR2.SQ12 = ADCx->Init->regular_config->conversions_12_th ;
		ADCx->Instance->SQR1.SQ13 = ADCx->Init->regular_config->conversions_13_th ;
		ADCx->Instance->SQR1.SQ14 = ADCx->Init->regular_config->conversions_14_th ;
		ADCx->Instance->SQR1.SQ15 = ADCx->Init->regular_config->conversions_15_th ;
		ADCx->Instance->SQR1.SQ16 = ADCx->Init->regular_config->conversions_16_th ;
	*/
	}
	// injection**********************************************************************
	ADCx->Instance->JSQR.JL = ADCx->Init->injected_config->NbrOfConversion ;

	/*for(counter=(ADCx->Init->injected_config->NbrOfConversion)-1;counter>=0;counter--)
	{
		//uint32_t *temm = reg(4-counter);

		//ADCx->Instance->JSQR.JSQ1 = ADCx->Init->injected_config->conversions_1_th ;
	}*/
	if(ADCx->Init->injected_config->NbrOfConversion == conversion_4)
	{
		ADCx->Instance->JSQR.JSQ1 = ADCx->Init->injected_config->conversions_1_th ;
		ADCx->Instance->JSQR.JSQ2 = ADCx->Init->injected_config->conversions_2_th ;
		ADCx->Instance->JSQR.JSQ3 = ADCx->Init->injected_config->conversions_3_th ;
		ADCx->Instance->JSQR.JSQ4 = ADCx->Init->injected_config->conversions_4_th ;
	}
	else if(ADCx->Init->injected_config->NbrOfConversion == conversion_3)
	{
		ADCx->Instance->JSQR.JSQ2 = ADCx->Init->injected_config->conversions_1_th ;
		ADCx->Instance->JSQR.JSQ3 = ADCx->Init->injected_config->conversions_2_th ;
		ADCx->Instance->JSQR.JSQ4 = ADCx->Init->injected_config->conversions_3_th ;
	}
	else if(ADCx->Init->injected_config->NbrOfConversion == conversion_2)
	{
		ADCx->Instance->JSQR.JSQ3 = ADCx->Init->injected_config->conversions_1_th ;
		ADCx->Instance->JSQR.JSQ4 = ADCx->Init->injected_config->conversions_2_th ;
	}
	else
	{
		ADCx->Instance->JSQR.JSQ4 = ADCx->Init->injected_config->conversions_1_th ;
	}

	/* calibration */
	//ADCx->Instance->CR2.CAL = enabled ;

	/*sampling time*/

	uint8_t tempp_arr[10] =	{tempp(0),tempp(1),tempp(2),tempp(3),tempp(4),tempp(5),tempp(6),
							tempp(7),tempp(8),tempp(9)};


	for(counter=0;counter<=(ADCx->Init->sample_time_config->NbrOfchannel_SAMP);counter++)
	{
			ADCx->Instance->SMPR2.Sample_time |= ((uint32_t)(tempp_arr[counter]))<<(counter*3) ;
	}

	//polling for cal until the bit become 0 the cal code is saved in DR register**********
	while(ADCx->Instance->CR2.CAL);
	calibration = ADCx->Instance->DR.Regular_DATA;

	/*Threshold levels*/
	ADCx->Instance->HTR.HT = ADCx->Init->AWD_config->high_threshold;
	ADCx->Instance->LTR.LT = ADCx->Init->AWD_config->low_threshold;
	ADCx->Instance->CR1.AWDIE = ADCx->Init->AWD_config->AWD_IRQ;
	ADCx->Instance->CR1.AWD_SGL = (ADCx->Init->AWD_config->AWD_channel)>>2;
	//ADCx->Instance->CR1.JAWDEN = (ADCx->Init->AWD_config->AWD_channel)|(1);//P
	//ADCx->Instance->CR1.AWDEN = ((ADCx->Init->AWD_config->AWD_channel)|(2))>>1;
	ADCx->Instance->CR1.AWDEN_JAWDEN = ((ADCx->Init->AWD_config->AWD_channel)|(3));

	ptr_ISR_AWD = ADCx->Init->AWD_config->AWD_ptr;

	/*external trigger*/
	ADCx->Instance->CR2.EXTTRIG = ADCx->Init->Ex_trigger_config->regular_trigger;
	ADCx->Instance->CR2.JEXTTRIG = ADCx->Init->Ex_trigger_config->injected_trigger;
	ADCx->Instance->CR2.EXTSEL = ADCx->Init->Ex_trigger_config->regular_event;
	ADCx->Instance->CR2.JEXTSEL = ADCx->Init->Ex_trigger_config->injected_event;

	/*select mode*/
	ADCx->Instance->CR2.CONT = ADCx->Init->Continuous_Mode;
	if(ADCx->Init->interrupt_enable)
	{
		ADCx->Instance->CR1.EOCIE = ADCx->Init->interrupt_enable ;
		ptr_ISR_EOC = ADCx->Init->EOC_IRQ;
	}

	/*start conversion */


}
void ADC_DEinit(ADC_Handle_t *ADCx);
void ADC_SelectChannel(ADC_Handle_t *ADCx);
void ADC_Start_Conv(ADC_Handle_t *ADCx)
{
	if((ADCx->Init->Ex_trigger_config->injected_event ==IN_software_trigger))
		ADCx->Instance->CR2.JSWSTART = enabled ;

	else if((ADCx->Init->Ex_trigger_config->regular_event ==RE_software_trigger))
		ADCx->Instance->CR2.SWSTART = enabled ;
	else
		ADCx->Instance->CR2.ADON = enabled ;
}
uint16_t ADC_Get_Conv_Result(ADC_Handle_t *ADCx)
{
	//polling
	uint16_t Data=0;
	while(!(ADC1->SR.EOC));
	Data = (ADCx->Instance->DR.Regular_DATA) - calibration ;
	return (Data);
}


void ADC1_2_IRQHandler (void)
{
	if(ADC1->SR.EOC)
	{
		if(ptr_ISR_EOC)
		{
			ptr_ISR_EOC();
		}
	}
	else if(ADC1->SR.AWD)
	{
		if(ptr_ISR_AWD)
		{
			ptr_ISR_AWD();
		}
	}


}

