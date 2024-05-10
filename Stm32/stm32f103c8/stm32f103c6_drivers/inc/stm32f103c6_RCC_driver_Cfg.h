/**
 ******************************************************************************
 * @file           : stm32f103c6_RCC_driver_Cfg.h
 * @author         : Ahmed Ashraf Mahgob Ahmed
 * @brief          : Contain the code to configure Reset and clock control
 ******************************************************************************
**/
#ifndef INC_STM32F103C6_RCC_DRIVER_CFG_H_
#define INC_STM32F103C6_RCC_DRIVER_CFG_H_
/*--------------------------------------------Includes Start----------------------------------*/

/*--------------------------------------------Includes End----------------------------------*/

/*--------------------------------------------Macro Declaration----------------------------------*/
//the available oscillator to use is HSI-HSE-LSI-LSE

// the system main clock select
#define RCC_HSI_CLK_Source			0x0U	//8 MHZ >> faster startup time and
											//less accurate than an external crystal oscillator
#define RCC_HSE_CLK_Source			0x1U	//Port D pin 0 - 1 [in - out]
#define RCC_PLL_CLK_Source			0x2U
#define RCC_CLK_Source_Selection	(RCC_HSE_CLK_Source)				//macro configuration

#define RCC_LSI_CLK_Source			0x3U
#define RCC_LSE_CLK_Source			0x4U	//Port C pin 14 - 15 [in - out]
		/*used as general-purpose I/O
		PC14 and PC15, respectively, when the LSE oscillator is off. The LSE has priority over the
		GP IOs function*/

//@ref external clock
#define crystal_ceramic_resonator	0x0
#define user_external_clock			0x1			//The external clock signal (square, sinus or triangle) with ~50%
												//duty cycle
//@ref USB prescaler
#define  PLL_clock_divided_1_5		0x0
#define  PLL_clock_divided_1		0x1
//@ref ADC prescaler
#define PCLK2_divided_2				0x0
#define PCLK2_divided_4				0x1
#define PCLK2_divided_6				0x2
#define PCLK2_divided_8				0x3
//@ref [APB high-speed prescaler (APB2) PCLK2] and [ APB low-speed prescaler (APB1) PCLK1]
#define HCLK_divided_1				0x0
#define HCLK_divided_2				0x4
#define HCLK_divided_4				0x5
#define HCLK_divided_8				0x6
#define HCLK_divided_16				0x7
//@ref  AHB prescaler
#define SYSCLK_divided_1			0x0
#define SYSCLK_divided_2			0x8
#define SYSCLK_divided_4			0x9
#define SYSCLK_divided_8			0xA
#define SYSCLK_divided_16			0xB
#define SYSCLK_divided_64			0xC
#define SYSCLK_divided_128			0xD
#define SYSCLK_divided_256			0xE
#define SYSCLK_divided_512			0xF

//HSI calibration *****HSI to 8 MHz ± 1%
#define HSI_Calibration_ON			0x0		//you need to have a LSE oscillator to do calibration
#define HSI_Calibration_OFF			0x1
#define HSI_Calibration				(HSI_Calibration_OFF)				//macro configuration

//@ref HSE divider for PLL entry
#define HSE_divided_1				0x0
#define HSE_divided_2				0x1
//@ref HSE or HSI/2 to PLL multiplier PLL entry
#define HSI_divided_2_PLL_MUL		0x0
#define HSE_divided_1_PLL_MUL		0x1
#define PLL_Multiplier_Entry		(HSE_divided_1_PLL_MUL)				//macro configuration
//@ref PLL multiplication factor	[Caution: The PLL output frequency must not exceed 72 MHz.]
#define PLL_Multiplier_2			0x0
#define PLL_Multiplier_3			0x1
#define PLL_Multiplier_4			0x2
#define PLL_Multiplier_5			0x3
#define PLL_Multiplier_6			0x4
#define PLL_Multiplier_7			0x5
#define PLL_Multiplier_8			0x6
#define PLL_Multiplier_9			0x7
#define PLL_Multiplier_10			0x8
#define PLL_Multiplier_11			0x9
#define PLL_Multiplier_12			0xA
#define PLL_Multiplier_13			0xB
#define PLL_Multiplier_14			0xC
#define PLL_Multiplier_15			0xD
#define PLL_Multiplier_16			0xF

//RTC clock source selection
#define HSE_divided_128				3UL
#define LSE							1UL
#define LSI							2UL
#define RTC_clock_source_selection  (HSE_divided_128)				//macro configuration

//allows the clock to be output onto the external MCO pin
//[PLL clock divided by 2 ------HSE-----HSI-----SYSCLK] does not exceed 50 MHz (the maximum IO speed)
#define No_clock					0UL
#define System_clock				4UL
#define HSI_clock					5UL
#define HSE_clock					6UL
#define PLL_divided_2_clock			7UL
#define MCU_CLK_output_selection	(HSE_clock)						//macro configuration

//AFIO remapping
#define No_remapping				0UL
#define PD0_remapped				1UL

/*--------------------------------------------Macro Declaration----------------------------------*/

/*--------------------------------------------Macro Functions Declaration----------------------------------*/
#define SET_BIT(REG,BIT)						(REG |= BIT )
#define CLEAR_BIT(REG,BIT)						(REG &= ~(BIT))
#define TOGGLE_BIT(REG,BIT)						(REG ^= BIT )
#define READ_BIT(REG,BIT)						(REG & BIT )
#define MODIFY_REG(REG,CLEAR_MSK,SET_VALUE)		(((REG) & (~(CLEAR_MSK))) | (SET_VALUE))
/*--------------------------------------------Macro Functions Declaration----------------------------------*/

/*--------------------------------------------Data Type Declaration----------------------------------*/
typedef enum
{
	Polling		,
	Interrupt
}enable_mechanism;
/*--------------------------------------------Data Type Declaration----------------------------------*/



#endif /* INC_STM32F103C6_RCC_DRIVER_CFG_H_ */
