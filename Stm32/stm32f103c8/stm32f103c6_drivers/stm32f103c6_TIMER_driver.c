/*
 * stm32f103c6_TIMER_driver.C
 *
 *  Created on: Nov 21, 2023
 *      Author: Ahmed Ashraf
 */

#include "stm32f103c6_TIMER_driver.h"

#define UEV_enabled			0
#define UEV_disabled		1
#define enabled				1
#define disabled			0

#define set_IRQ_flag_OC			TIM3->SR.UIF = enabled ; \
								TIM3->SR.CC1IF = enabled ;

#define clear_IRQ_flag_OC		TIM3->SR.UIF = disabled ; \
								TIM3->SR.CC1IF = disabled ;

#define clear_IRQ_flag_PWM		TIM4->SR.UIF = disabled ; \
								TIM4->SR.CC1IF = disabled ;

//#define set_IRQ_OC
//#define clear_IRQ_OC

uint16_t *IC_value = NULL;

static void(*TIM_IRQ_Handler)(void);


static uint16_t IC_Handler (void);

void TIM_init(TIM_Handle_t *TIMx){

	uint8_t TIM_x_ = 0 ;
	if(TIMx->Instance == TIM2 )
	{
		CLK_TIM2_RST
		TIM2_DISABLE_IRQ
		CLK_TIM2_EN
		TIM_x_ = TIM2_ISR ;
	}
	else if(TIMx->Instance == TIM3)
	{
		CLK_TIM3_RST
		TIM2_DISABLE_IRQ
		CLK_TIM3_EN
		TIM_x_ = TIM3_ISR ;
	}
	else
	{
		CLK_TIM4_RST
		TIM2_DISABLE_IRQ
		CLK_TIM4_EN
		TIM_x_ = TIM4_ISR ;
	}

	//TIM_IRQ_Handler=TIMx->ISR_Handler;

	TIMx->Instance->ARR.ARR     = TIMx->Init->Period ;
	TIMx->Instance->CR1.DIR 	= TIMx->Init->CounterMode ;
	TIMx->Instance->PSC.PSC     = TIMx->Init->Prescaler ;
	TIMx->Instance->CR1.UDIS    = UEV_enabled ;
	TIMx->Instance->CR1.URS     = enabled ;
	TIMx->Instance->CR1.ARPE    = enabled ;

	if(TIMx->handler == interrupt)
	{
		TIM_IRQ_Handler = TIMx->ISR_Handler;
		TIMx->Instance->DIER.UIE   = interrupt_enabled ;
		TIM_ENABLE_ISR(TIM_x_)
	}
	else if(TIMx->handler == NONE)
	{
		TIM_IRQ_Handler=NULL;
		TIMx->Instance->DIER.UIE   = interrupt_enabled ;
		TIM_ENABLE_ISR(TIM_x_)
	}
	else
	{ /* no thing */ }

	if(TIMx->TIM_mode == TIM_mode )
	{
		TIMx->Instance->CR1.CEN     = enabled ;
	}
	else if(TIMx->TIM_mode == Capture_mode )
	{
		TIMx->Instance->CR1.CEN     = enabled ;
	}
	else if(TIMx->TIM_mode == Compare_mode )
	{

	}
	else if(TIMx->TIM_mode == PWM_mode )
	{

	}
	else
	{ /* no thing */ }

}

void TIM_deinit(TIM_Handle_t *TIMx){

	TIMx->Instance->DIER.UIE   = interrupt_disabled ;

	if(TIMx->Instance == TIM2 )
	{
		CLK_TIM2_DEN
		TIM2_DISABLE_IRQ
	}
	else if(TIMx->Instance == TIM3)
	{
		CLK_TIM3_DEN
		TIM2_DISABLE_IRQ
	}
	else
	{
		CLK_TIM4_DEN
		TIM2_DISABLE_IRQ
	}



}

void TIM_IC_init(TIM_Handle_t *TIMx ,TIM_IC_Init_t *TIM_IC ) /* TIM 2 */
{
	TIM_init(TIMx);
	/*
	uint8_t TIM_x_ = 0 ;
	if(TIMx->Instance == TIM2 )
	{
		CLK_TIM2_EN
		TIM_x_ = TIM2_IRQ ;
	}
	else if(TIMx->Instance == TIM3)
	{
		CLK_TIM3_EN
		TIM_x_ = TIM3_IRQ ;
	}
	else
	{
		CLK_TIM4_EN
		TIM_x_ = TIM4_IRQ ;
	}

	TIMx->Instance->ARR     	= TIMx->Init->Period ;
	TIMx->Instance->CR1.DIR 	= TIMx->Init->CounterMode ;
	TIMx->Instance->PSC     	= TIMx->Init->Prescaler ;
	TIMx->Instance->CR1.UDIS    = UEV_enabled ;
	TIMx->Instance->CR1.CEN     = enabled ;
	*/

	TIMx->Instance->CCMR1.InputCapturemode.CC1S     = TIM_IC->ICMAPPing ;//1
	TIMx->Instance->CCMR1.InputCapturemode.IC1F     = TIM_IC->ICFilter ;//2
	TIMx->Instance->CCER.CC1P     						   = TIM_IC->ICPolarity ;
	TIMx->Instance->CCMR1.InputCapturemode.IC1PSC   = TIM_IC->ICPrescaler ;//3
	if( TIMx->handler == DMA )
	{
		TIMx->Instance->DIER.UDE   = DMA_enabled ;
		TIMx->Instance->DIER.CC1DE = DMA_enabled ;
	}
	else
	{
		//TIMx->Instance->DIER.UIE   = interrupt_enabled ;
		TIMx->Instance->DIER.CC1IE = interrupt_enabled ;
		//TIM_ENABLE_IRQ(TIM_x_)
	}

	IC_value = TIM_IC->IC_value_ ;
	TIMx->Instance->CCER.CC1E  = Capture_enabled ;

}

void TIM_OC_init(TIM_Handle_t *TIMx ,TIM_OC_Init_t *TIM_OC ) /* TIM 3 */
{
	TIM_init(TIMx);

	TIMx->Instance->CCMR1.OutputComparemode.OC1M		=	TIM_OC->Mode;//4
	TIMx->Instance->CCER.CC1P								=	TIM_OC->polarity;
	TIMx->Instance->CCMR1.OutputComparemode.OC1PE	=	TIM_OC->preload;//5
	TIMx->Instance->CCR1.CCR1								=	TIM_OC->OC_value;

	if( TIMx->handler == DMA )
	{
		TIMx->Instance->DIER.UDE   = DMA_enabled ;
		TIMx->Instance->DIER.CC1DE = DMA_enabled ;
	}
	else
	{
		//TIMx->Instance->DIER.UIE   = interrupt_enabled ;
		TIMx->Instance->DIER.CC1IE = interrupt_enabled ;
		//TIM_ENABLE_IRQ(TIM_x_)
	}

	TIMx->Instance->CCER.CC1E  = Compare_enabled ;

}

void TIM_PWM_init(TIM_Handle_t *TIMx ,TIM_PWM_Init_t *TIM_PWM ) /* TIM 4 */
{
	TIM_init(TIMx);

	TIMx->Instance->CCMR1.OutputComparemode.OC1M		=	TIM_PWM->Mode;//6
	TIMx->Instance->CCER.CC1P								=	TIM_PWM->polarity;
	TIMx->Instance->CCMR1.OutputComparemode.OC1PE	=	TIM_PWM->preload;//7
	TIMx->Instance->CCR1.CCR1								=	TIM_PWM->PWM_value;
	TIMx->Instance->CR1.CMS									=	TIM_PWM->selection;

	if( TIMx->handler == DMA )
	{
		TIMx->Instance->DIER.UDE   = DMA_enabled ;
		TIMx->Instance->DIER.CC1DE = DMA_enabled ;
	}
	else
	{
		//TIMx->Instance->DIER.UIE   = interrupt_enabled ;
		TIMx->Instance->DIER.CC1IE = interrupt_enabled ;
		//TIM_ENABLE_IRQ(TIM_x_)
	}
	TIMx->Instance->CCER.CC1E 	= PWM_enabled ;
	TIMx->Instance->EGR.UG 		= enabled ;
	TIMx->Instance->CR1.CEN     = enabled ;
}

static uint16_t IC_Handler (void)
{
	/*TIM2->Instance->CCR1.CCR1 ;
	if(TIMx->Instance->SR.CC1IF)
	{
		IC[array_counter] = TIMx->Instance->CCR1.CCR1 ;
		array_counter++;
	}

	if(array_counter == 2)
	{

	}*/

	return(TIM2->CCR1.CCR1 );
}

void TIM2_IRQHandler(void)
{

	//TIM2->SR.UIF = disabled ;		//TIMx->Instance->SR.UIF = disabled ; // clear flag  //TIM2->SR.UIF = disabled ;
	//TIM2->SR.CC1IF = disabled ;
	//if(TIM_IRQ_Handler)
	//{
	//	TIM_IRQ_Handler();
	//}
	//else
	//{

	//	*IC_value = IC_Handler();
	//}

	if(TIM2->SR.UIF)
	{
		TIM2->SR.UIF = disabled ;
		if(TIM_IRQ_Handler)
			{
				TIM_IRQ_Handler();
			}
	}
	else if(TIM2->SR.UIF)
	{
		TIM2->SR.CC1IF = disabled ;
		*IC_value = IC_Handler();
	}
	else{/*no thing*/}


}

void TIM3_IRQHandler(void)
{
	clear_IRQ_flag_OC

	if(TIM_IRQ_Handler)
	{
		TIM_IRQ_Handler();
	}
}

void TIM4_IRQHandler(void)
{
	clear_IRQ_flag_PWM

	if(TIM_IRQ_Handler)
	{
		TIM_IRQ_Handler();
	}
}



