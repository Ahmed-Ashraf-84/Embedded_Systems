/**
 ******************************************************************************
 * @file           : CortexM3_Core_SysTick.c
 * @author         : Ahmed Ashraf Mahgob Ahmed
 * @brief          : Contain the code to Control system timer
 ******************************************************************************
**/
/*--------------------------------------------Includes Start----------------------------------*/
#include "CortexM3/CortexM3_Core_SysTick.h"

/*--------------------------------------------Includes End----------------------------------*/

/*--------------------------------------------Macro Declaration----------------------------------*/

/*--------------------------------------------Macro Declaration----------------------------------*/

/*--------------------------------------------Macro Functions Declaration----------------------------------*/
/*--------------------------------------------Macro Functions Declaration----------------------------------*/

/*--------------------------------------------Data Type Declaration----------------------------------*/

static Ptr_function Sys_tick_ptr = NULL ;
static volatile uint32_t Sys_tick_callback_mode ;

/*--------------------------------------------Data Type Declaration----------------------------------*/

/*--------------------------------------------Software Interface Declaration-------------------------------*/


/**
 * 	@brief			Initialize SysTick timer
 *  @details		Using the control register to disable the counter and the interrupt request
 *  				and write to the Load register a specific value which has been taken from the user
 *  				and reset the counter register and specify the input clock
 *  @parameter[in]  STK_Ticks Number of the Ticks which the counter start to counts down from till Zero
 *  @note			STK_Ticks must be a value can be represented in 24 bit (24bit-Timer)
 *  @note			return value will be equal to Zero if the Initialization failed and will be equal
 *  				to 1 if the Initialization succeed
 */
uint8_t STK_Init(uint32_t STK_Ticks)
{
	uint8_t ret_value = 0 ;

	if(STK_Ticks <= STK_CTRL_RELOAD_Mask )
	{
		//disable the counter
		CLEAR_BIT(STK->CTRL ,STK_CTRL_ENABLE_Mask);
		//disable the interrupt
		CLEAR_BIT(STK->CTRL ,STK_CTRL_TICKINT_Mask);
		//reset the counter
		STK->VAL = 0 ;
		//reload the load register
		STK->LOAD = STK_Ticks ;
		//config the input clock
#if (STK_AHB_CLK_SOURCE == STK_AHB_CLK_DIV_1)
	SET_bit(STK->CTRL ,STK_CTRL_CLKSOURCE_Mask);
#elif (STK_AHB_CLK_SOURCE == STK_AHB_CLK_DIV_8)
	CLEAR_BIT(STK->CTRL ,STK_CTRL_CLKSOURCE_Mask);
#endif
		ret_value = 1 ;
	}
	else{/*nothing*/}

	return (ret_value);

}

/**
 * 	@brief			DeInitialize SysTick timer
 *  @details		Using the control register to disable the counter and the interrupt request
 *  				and reset to the Load register and reset the counter register
 */
void STK_Deinit(void)
{
	//disable the counter
	CLEAR_BIT(STK->CTRL ,STK_CTRL_ENABLE_Mask);
	//disable the interrupt
	CLEAR_BIT(STK->CTRL ,STK_CTRL_TICKINT_Mask);
	//reset the counter
	STK->VAL = 0 ;
	//reset the load register
	STK->LOAD = 0 ;
}

/**
 * 	@brief			SysTick timer counts to reach the required Ticks by polling
 *  @details		After Initialize SysTick timer the timer counts down till Zero in this interval
 *  				the processor polling to the counter flag
 *  @parameter[in]  STK_Ticks Number of the Ticks which the counter start to counts down from till Zero
 *  @note			STK_Ticks must be a value can be represented in 24 bit (24bit-Timer)
 */
void STK_Polling(uint32_t STK_Ticks)
{
	//reload the load register
	STK->LOAD = STK_Ticks ;
	//enable the counter
	SET_BIT(STK->CTRL ,STK_CTRL_ENABLE_Mask);
	//polling
	while(READ_BIT(STK->CTRL ,STK_CTRL_COUNTFLAG_Mask) == 0 );
	//deinit the SysTick
	STK_Deinit();
}

/**
 * 	@brief			SysTick timer counts to reach the required Ticks by interrupt for a single time
 *  @details		After Initialize SysTick timer the timer counts down till Zero in after this interval
 *  			    the counter flag is set and the processor will handle this interrupt request and jump
 *  			    to the user function this mechanism will be done for a single time
 *  @parameter[in]  STK_Ticks Number of the Ticks which the counter start to counts down from till Zero
 *  @parameter[in]  callback pointer to function which the user want to be processed
 *  @note			STK_Ticks must be a value can be represented in 24 bit (24bit-Timer)
 *  @note			callback must be point to a function take void and return void and not equal to NULL
 *  @note			the NVIC must be configured to enable the interrupt and to set the priority
 *
 */
void STK_Single_Interval(uint32_t STK_Ticks ,Ptr_function callback)
{
	if(callback != NULL)
	{
	//enable the interrupt
	SET_BIT(STK->CTRL ,STK_CTRL_TICKINT_Mask);
	//reload the load register
	STK->LOAD = STK_Ticks ;
	//set Sys_tick_ptr to callback
	Sys_tick_ptr = callback ;
	//set Sys_tick_callback_mode to STK_Single_Interval_mode
	Sys_tick_callback_mode = STK_Single_Interval_mode;
	//enable the counter
	SET_BIT(STK->CTRL ,STK_CTRL_ENABLE_Mask);

	}
	else{/*nothing*/}
}

/**
 * 	@brief			SysTick timer counts to reach the required Ticks by interrupt Periodically
 *  @details		After Initialize SysTick timer the timer counts down till Zero in after this interval
 *  			    the counter flag is set and the processor will handle this interrupt request and jump
 *  			    to the user function this mechanism will be done Periodically
 *  @parameter[in]  STK_Ticks Number of the Ticks which the counter start to counts down from till Zero
 *  @parameter[in]  callback pointer to function which the user want to be processed
 *  @note			STK_Ticks must be a value can be represented in 24 bit (24bit-Timer)
 *  @note			callback must be point to a function take void and return void and not equal to NULL
 *  @note			the NVIC must be configured to enable the interrupt and to set the priority
 *
 */
void STK_Periodic_Interval(uint32_t STK_Ticks ,Ptr_function callback)
{
	if(callback != NULL)
	{
	//enable the interrupt
	SET_BIT(STK->CTRL ,STK_CTRL_TICKINT_Mask);
	//reload the load register
	STK->LOAD = STK_Ticks ;
	//set Sys_tick_ptr to callback
	Sys_tick_ptr = callback ;
	//set Sys_tick_callback_mode to STK_Periodic_Interval_mode
	Sys_tick_callback_mode = STK_Periodic_Interval_mode;
	//enable the counter
	SET_BIT(STK->CTRL ,STK_CTRL_ENABLE_Mask);

	}
	else{/*nothing*/}
}

/**
 * 	@brief			Get Remaining Ticks
 *  @details		Get Remaining Ticks by read the value of the current value register
 *  @return			Remaining Ticks
 *
 */
uint32_t STK_Get_RemainingTicks(void)
{
	uint32_t ret_value = 0 ;
	//read current value register
	ret_value = STK->VAL ;

	return (ret_value);
}

/**
 * 	@brief			Get Elapsed Ticks
 *  @details		Get Elapsed Ticks by read the value of the current value register
 *  @return			Elapsed Ticks
 */
uint32_t STK_Get_ElapsedTicks(void)
{
	uint32_t ret_value = 0 ;
	//read current value register
	ret_value = (STK->LOAD) - (STK->VAL)  ;

	return (ret_value);
}

void SysTick_Handler(void)
{
	if(Sys_tick_callback_mode == STK_Single_Interval_mode )
	{
		STK_Deinit();
	}

	if(Sys_tick_ptr != NULL)
	{
		Sys_tick_ptr();
	}

}


/*--------------------------------------------Software Interface Declaration-------------------------------*/
