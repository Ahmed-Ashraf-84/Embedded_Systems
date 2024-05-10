/**
 ******************************************************************************
 * @file           : CortexM3_Core_SysTick.h
 * @author         : Ahmed Ashraf Mahgob Ahmed
 * @brief          : Contain the code to Control system timer
 ******************************************************************************
**/
#ifndef INC_CORTEXM3_CORTEXM3_CORE_SYSTICK_H_
#define INC_CORTEXM3_CORTEXM3_CORE_SYSTICK_H_
/*--------------------------------------------Includes Start----------------------------------*/
#include <stdint.h>
#include "stdlib.h"
#include "CortexM3_Core_SysTick_Cfg.h"
/*--------------------------------------------Includes End----------------------------------*/

/*--------------------------------------------Macro Declaration----------------------------------*/
#define STK_BASE  							0xE000E010UL
#define STK									((STK_t *)(STK_BASE))


#define STK_CTRL_ENABLE_Pos					0UL					/*STK-CTRL : ENABLE bit Position [1 bit]*/
#define STK_CTRL_ENABLE_Mask				(1UL << STK_CTRL_ENABLE_Pos)

#define STK_CTRL_TICKINT_Pos				1UL					/*STK-CTRL : TICKINT bit Position [1 bit]*/
#define STK_CTRL_TICKINT_Mask				(1UL << STK_CTRL_TICKINT_Pos)

#define STK_CTRL_CLKSOURCE_Pos				2UL					/*STK-CTRL : CLKSOURCE bit Position [1 bit]*/
#define STK_CTRL_CLKSOURCE_Mask				(1UL << STK_CTRL_CLKSOURCE_Pos)

#define STK_CTRL_COUNTFLAG_Pos				16UL				/*STK-CTRL : COUNTFLAG bit Position [1 bit]*/
#define STK_CTRL_COUNTFLAG_Mask				(1UL << STK_CTRL_COUNTFLAG_Pos)

#define STK_CTRL_RELOAD_Pos					0UL					/*STK-CTRL : RELOAD bit Position [24 bit]*/
#define STK_CTRL_RELOAD_Mask				(0xFFFFFFUL << STK_CTRL_RELOAD_Pos)

#define STK_Single_Interval_mode			0UL
#define STK_Periodic_Interval_mode			1UL

/*--------------------------------------------Macro Declaration----------------------------------*/

/*--------------------------------------------Macro Functions Declaration----------------------------------*/
/*--------------------------------------------Macro Functions Declaration----------------------------------*/

/*--------------------------------------------Data Type Declaration----------------------------------*/

typedef void(*Ptr_function)(void);

	//read/clear (rc_w1) Software can read as well as clear this bit by writing 1. Writing ‘0’ has
	//	no effect on the bit value.
typedef struct
{
	volatile uint32_t CTRL;		/* Offset : 0x000(R/W) Privileged  control and status register*/
	volatile uint32_t LOAD;		/* Offset : 0x004(R/W) Privileged  reload value register*/
	volatile uint32_t VAL;		/* Offset : 0x008(R/W) Privileged  current value register*/
	volatile uint32_t CALIB;	/* Offset : 0x00C(R/)  Privileged   calibration value register*/
}STK_t;
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
uint8_t STK_Init(uint32_t STK_Ticks);

/**
 * 	@brief			DeInitialize SysTick timer
 *  @details		Using the control register to disable the counter and the interrupt request
 *  				and reset to the Load register and reset the counter register
 */
void STK_Deinit(void);

/**
 * 	@brief			SysTick timer counts to reach the required Ticks by polling
 *  @details		After Initialize SysTick timer the timer counts down till Zero in this interval
 *  				the processor polling to the counter flag
 *  @parameter[in]  STK_Ticks Number of the Ticks which the counter start to counts down from till Zero
 *  @note			STK_Ticks must be a value can be represented in 24 bit (24bit-Timer)
 */
void STK_Polling(uint32_t STK_Ticks);

/**
 * 	@brief			SysTick timer counts to reach the required Ticks by interrupt for a single time
 *  @details		After Initialize SysTick timer the timer counts down till Zero in after this interval
 *  			    the counter flag is set and the processor will handle this interrupt request and jump
 *  			    to the user function this mechanism will be done for a single time
 *  @parameter[in]  STK_Ticks Number of the Ticks which the counter start to counts down from till Zero
 *  @parameter[in]  callback pointer to function which the user want to be processed
 *  @note			STK_Ticks must be a value can be represented in 24 bit (24bit-Timer)
 *  				callback must be point to a function take void and return void and not equal to NULL
 *
 */
void STK_Single_Interval(uint32_t STK_Ticks ,Ptr_function callback);

/**
 * 	@brief			SysTick timer counts to reach the required Ticks by interrupt Periodically
 *  @details		After Initialize SysTick timer the timer counts down till Zero in after this interval
 *  			    the counter flag is set and the processor will handle this interrupt request and jump
 *  			    to the user function this mechanism will be done Periodically
 *  @parameter[in]  STK_Ticks Number of the Ticks which the counter start to counts down from till Zero
 *  @parameter[in]  callback pointer to function which the user want to be processed
 *  @note			STK_Ticks must be a value can be represented in 24 bit (24bit-Timer)
 *  				callback must be point to a function take void and return void and not equal to NULL
 *
 */
void STK_Periodic_Interval(uint32_t STK_Ticks ,Ptr_function callback);


/**
 * 	@brief			Get Remaining Ticks
 *  @details		Get Remaining Ticks by read the value of the current value register
 *  @return			Remaining Ticks
 *
 */
uint32_t STK_Get_RemainingTicks(void);

/**
 * 	@brief			Get Elapsed Ticks
 *  @details		Get Elapsed Ticks by read the value of the reload value register and subtract
 *  				it from current value register
 *  @return			Elapsed Ticks
 */
uint32_t STK_Get_ElapsedTicks(void);

/*--------------------------------------------Software Interface Declaration-------------------------------*/


#endif /* INC_CORTEXM3_CORTEXM3_CORE_SYSTICK_H_ */
