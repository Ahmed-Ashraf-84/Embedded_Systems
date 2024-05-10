/*
 * stm32f103c6_TIMER_driver.h
 *
 *  Created on: Nov 21, 2023
 *      Author: Ahmed Ashraf
 */

#ifndef INC_STM32F103C6_TIMER_DRIVER_H_
#define INC_STM32F103C6_TIMER_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------

#include "stm32f103c6_LQFP48.h"
//#include "stm32f103c6_GPIO_driver.h"
#include "stm32f103c6_RCC_driver.h"


//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref counter_DIR_Definition
enum counter_DIR_Definition
{
	upcounter 		= 0b0 ,
	downcounter 	= 0b1

};

//@ref IC_map_selection_Definition     /**CC1 channel is configured as input**/
enum IC_map_selection_Definition
{
	ICx_TO_TIx 		= 0b01 ,
	ICx_TO_TI_xPP 	= 0b10 ,		// 1 <-> 2  and 3 <-> 4
	ICx_TO_TRC		= 0b11

};
/*
 * ****************** (CCxS) -> CCMR1 ***********************
 *  01: CC1 channel is configured as input, IC1 is mapped on TI1
    10: CC1 channel is configured as input, IC1 is mapped on TI2
	11: CC1 channel is configured as input, IC1 is mapped on TRC. This mode is working only if
	an internal trigger input is selected through TS bit (TIMx_SMCR register)

	Note: CC1S bits are writable only when the channel is OFF (CC1E = 0 in TIMx_CCER).*/

/**********
 * ************  ICFilter  ************** ICxF -> CCMR
 *
 *  0000: No filter, sampling is done at fDTS
	0001: fSAMPLING=fCK_INT, N=2
	0010: fSAMPLING=fCK_INT, N=4
	0011: fSAMPLING=fCK_INT, N=8 // push button (debounce)
	0100: fSAMPLING=fDTS/2, N=6
	0101: fSAMPLING=fDTS/2, N=8
	0110: fSAMPLING=fDTS/4, N=6
	0111: fSAMPLING=fDTS/4, N=8
	1000: fSAMPLING=fDTS/8, N=6
	1001: fSAMPLING=fDTS/8, N=8
	1010: fSAMPLING=fDTS/16, N=5
	1011: fSAMPLING=fDTS/16, N=6
	1100: fSAMPLING=fDTS/16, N=8
	1101: fSAMPLING=fDTS/32, N=5
	1110: fSAMPLING=fDTS/32, N=6
	1111: fSAMPLING=fDTS/32, N=8
 *
 *
 */

//@ref Polarity_Definition
enum Polarity_Definition
{
	rising_edge 		= 0b0 ,
	falling_edge 		= 0b1

};

/*
 *  Bits 3:2 IC1PSC: Input capture 1 prescaler
	This bit-field defines the ratio of the prescaler acting on CC1 input (IC1).
	The prescaler is reset as soon as CC1E=0 (TIMx_CCER register).
	00: no prescaler, capture is done each time an edge is detected on the capture input
	01: capture is done once every 2 events
	10: capture is done once every 4 events
	11: capture is done once every 8 events*/

//@ref IC_Prescaler_Definition
enum IC_Prescaler_Definition
{
	no_prescaler 			= 0b00  ,
	capture_2_events 		= 0b01  ,
	capture_4_events		= 0b10 ,
	capture_8_events		= 0b11

};


//@ref IC_Enable_Definition  ******** CCxE -> CCER
enum IC_Enable_Definition
{
	Capture_enabled 		= 0b1 ,
	Capture_disabled 		= 0b0

};

//@ref interrupt_Enable_Definition  ******** CCxIE -> DIER
enum interrupt_Enable_Definition
{
	interrupt_enabled 		= 0b1 ,
	interrupt_disabled 		= 0b0

};

//@ref  DMA_Enable_Definition  ******** CCxDE -> DIER
enum  DMA_Enable_Definition
{
	 DMA_enabled 		= 0b1 ,
	 DMA_disabled 		= 0b0

};

//@ref  IC_handle_Definition  ******** CCxDE -> DIER
enum  handle_Definition
{
	 DMA 		    = 0b01 ,
	 interrupt 		= 0b00 ,
	 NONE			= 0b11

};

/*
 * Bits 2:0 SMS: Slave mode selection
		When external signals are selected the active edge of the trigger signal (TRGI) is linked to
		the polarity selected on the external input (see Input Control register and Control Register
		description.
			000: Slave mode disabled - if CEN = ‘1 then the prescaler is clocked directly by the internal
			clock.
			001: Encoder mode 1 - Counter counts up/down on TI2FP1 edge depending on TI1FP2
			level.
			010: Encoder mode 2 - Counter counts up/down on TI1FP2 edge depending on TI2FP1
			level.
			011: Encoder mode 3 - Counter counts up/down on both TI1FP1 and TI2FP2 edges
			depending on the level of the other input.
			100: Reset Mode - Rising edge of the selected trigger input (TRGI) reinitializes the counter
			and generates an update of the registers.
			101: Gated Mode - The counter clock is enabled when the trigger input (TRGI) is high. The
			counter stops (but is not reset) as soon as the trigger becomes low. Both start and stop of
			the counter are controlled.
			110: Trigger Mode - The counter starts at a rising edge of the trigger TRGI (but it is not
			reset). Only the start of the counter is controlled.
    (IC)    111: External Clock Mode 1 - Rising edges of the selected trigger (TRGI) clock the counter.
					Note: The gated mode must not be used if TI1F_ED is selected as the trigger input (TS=100).
					Indeed, TI1F_ED outputs 1 pulse for each transition on TI1F, whereas the gated mode
					checks the level of the trigger signal.
					The clock of the slave timer must be enabled prior to receiving events from the master
					timer, and must not be changed on-the-fly while triggers are received from the master
					timer.
 *
 */
//@ref  OC_MODES_Definition  ******** OCxM -> CCMR1
enum  OC_MODES_Definition
{
	Frozen 		= 0 ,
	HIGH 		    ,
	LOW				,
	Toggle			,
	forced_LOW		,
	forced_HIGH
};

/*
 * 	OC1M: Output compare 1 mode
	These bits define the behavior of the output reference signal OC1REF from which OC1 and
	OC1N are derived. OC1REF is active high whereas OC1 and OC1N active level depends
	on CC1P and CC1NP bits.
		000: Frozen - The comparison between the output compare register TIMx_CCR1 and the
		counter TIMx_CNT has no effect on the outputs.(this mode is used to generate a timing
		base).
		001: Set channel 1 to active level on match. OC1REF signal is forced high when the counter
		TIMx_CNT matches the capture/compare register 1 (TIMx_CCR1).
		010: Set channel 1 to inactive level on match. OC1REF signal is forced low when the
		counter TIMx_CNT matches the capture/compare register 1 (TIMx_CCR1).
		011: Toggle - OC1REF toggles when TIMx_CNT=TIMx_CCR1.
		100: Force inactive level - OC1REF is forced low.
		101: Force active level - OC1REF is forced high.
		*/
//@ref  PWM_MODES_Definition  ******** OCxM -> CCMR1
enum  PWM_MODES_Definition
{
	PWM_1	= 6	 ,
	PWM_2
};


/*
		110: PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1
		else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0) as long as
		TIMx_CNT>TIMx_CCR1 else active (OC1REF=1).
		111: PWM mode 2 - In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1
		else active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else
		inactive
 */

//@ref   output polarity_Definition  ********  CCxP -> CCER
enum   OC_Polarity_Definition			/* this bit specifies the polarity.
 	 	 	 	 	 	 	 	 	 	 * active_high the signal (OCXref) remains cons (buffer)
 	 	 	 	 	 	 	 	 	 	 * active_low  the signal (OCXref) inverted
 	 	 	 	 	 	 	 	 	 	 */
{
	 Active_HIGH 		= 0b0 ,
	 Active_LOW 		= 0b1

};

//@ref   output polarity_Definition  ********  OC1PE -> CCMR1
enum  OC_preload_Definition			/* this bit specifies the polarity.
 	 	 	 	 	 	 	 	 	 	 * Preload_register_disabled TIMx_CCR1 can be written at anytime, the
											new value is taken in account immediately.
 	 	 	 	 	 	 	 	 	 	 * Preload_register_disabled  Read/Write operations access the preload
											register. TIMx_CCR1 preload value is loaded in the active register at each update event
 	 	 	 	 	 	 	 	 	 	 */
{
	Preload_register_disabled 		= 0b0 ,
	Preload_register_enabled 		= 0b1	//must be enabled in in pwm mode

};


//@ref OC_Enable_Definition  ******** CCxE -> CCER
enum OC_Enable_Definition
{
	Compare_enabled 		= 0b1 ,
	Compare_disabled 		= 0b0

};

//@ref PWM_Enable_Definition  ******** CCxE -> CCER
enum PWM_Enable_Definition
{
	PWM_enabled 		= 0b1 ,
	PWM_disabled 		= 0b0

};

/*
 *
 	 Bits 6:5 CMS: Center-aligned mode selection
			00: Edge-aligned mode. The counter counts up or down depending on the direction bit
				(DIR).
			01: Center-aligned mode 1. The counter counts up and down alternatively. Output compare
				interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set
				only when the counter is counting down.
			10: Center-aligned mode 2. The counter counts up and down alternatively. Output compare
				interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set
				only when the counter is counting up.
			11: Center-aligned mode 3. The counter counts up and down alternatively. Output compare
				interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set
				both when the counter is counting up or down.

			Note: It is not allowed to switch from edge-aligned mode to center-aligned mode as long as
			the counter is enabled (CEN=1)
*/

//@ref Center-aligned mode_Definition  ******** CMS -> CR1
enum Center_aligned_mode_Definition
{
	Edge_aligned_mode 		= 0 ,
	Center_aligned_mode_1 		,
	Center_aligned_mode_2 		,
	Center_aligned_mode_3
};

//@ref TIM_mode_Definition
enum TIM_mode_Definition
{
	TIM_mode 		= 0 ,
	Capture_mode 		,
	Compare_mode 		,
	PWM_mode
};


//-----------------------------
//User type definitions (structures)
//-----------------------------



typedef struct {
	enum counter_DIR_Definition CounterMode :1 ; /* Specifies the counter mode. */
	uint16_t Prescaler; /* Specifies the prescaler value used to divide the TIMclock. */
	uint16_t Period; /* Specifies the period value to be loaded into the active
	Auto-Reload Register at the next update event. */ // specifies the frequency in PWM


//uint32_t ClockDivision; /* Specifies the clock division. */
//uint32_t RepetitionCounter; /* Specifies the repetition counter value. */
} TIM_Base_Init_t;


typedef struct {
	enum Polarity_Definition ICPolarity 	 	:1 ;  /* Specifies the active edge of the input signal. */
	//enum  IC_handle_Definition IC_handler       :1 ;
	enum IC_map_selection_Definition ICMAPPing  :2 ;  /* Specifies the input. */
	enum IC_Prescaler_Definition ICPrescaler 	:2 ;  /* Specifies the Input Capture Prescaler. */
	uint8_t ICFilter						    :4 ;  /* Specifies the input capture filter. */
	uint16_t *IC_value_;
} TIM_IC_Init_t;


typedef struct{
	enum  OC_Polarity_Definition polarity  :1 ;		/* Specifies the output polarity. */
	enum  OC_MODES_Definition Mode : 3 ;			/* Specifies the Mode of output pin. */
	enum  OC_preload_Definition preload  :1 ;		/* Specifies the ccrx behavior. */
	uint16_t OC_value ;								/* specifies the compare value */

}TIM_OC_Init_t;

//  eventually must be enabled (ARPE) in PWM
//  the user has to initialize all the registers by setting the UG bit in the TIMx_EGR register ,
//    before starting the counter

typedef struct
{
	enum  OC_Polarity_Definition polarity  		  :1 ;		/* Specifies the output polarity. */
	enum  OC_preload_Definition preload  		  :1 ;		/* Specifies the CCRx behavior. */
	enum Center_aligned_mode_Definition selection :2 ;      /* Specifies the Mode of counting. */
	enum  PWM_MODES_Definition	Mode 			  :3 ;		/* Specifies the Mode of output pin. */
	uint16_t PWM_value ;								    /* specifies the duty cycle in CCRx  */
}TIM_PWM_Init_t;


typedef struct {
	enum  handle_Definition handler       :2 ;
	enum TIM_mode_Definition TIM_mode	  :2 ;
	void(*ISR_Handler)(void);
	TIM_t *Instance; /* Pointer to timer descriptor */
	TIM_Base_Init_t *Init; /* TIM Time Base required parameters */
//HAL_TIM_ActiveChannel Channel; /* Active channel */
///DMA_HandleTypeDef *hdma[7]; /* DMA Handlers array */
//HAL_LockTypeDef Lock; /* Locking object */
//__IO HAL_TIM_StateTypeDef State; /* TIM operation state */
} TIM_Handle_t;


/*
* ===============================================
* APIs Supported by "MCAL TIMER DRIVER"
* ===============================================
*/

void TIM_init(TIM_Handle_t *TIMx);
void TIM_deinit(TIM_Handle_t *TIMx);

void TIM_IC_init(TIM_Handle_t *TIMx ,TIM_IC_Init_t *TIM_IC );

void TIM_OC_init(TIM_Handle_t *TIMx ,TIM_OC_Init_t *TIM_OC );

void TIM_PWM_init(TIM_Handle_t *TIMx ,TIM_PWM_Init_t *TIM_PWM );


#endif /* INC_STM32F103C6_TIMER_DRIVER_H_ */
