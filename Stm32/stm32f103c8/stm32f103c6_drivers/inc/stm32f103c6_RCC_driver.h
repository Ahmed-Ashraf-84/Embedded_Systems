/**
 ******************************************************************************
 * @file           : stm32f103c6_RCC_driver.h
 * @author         : Ahmed Ashraf Mahgob Ahmed
 * @brief          : Contain the code to Control Reset and clock control
 ******************************************************************************
**/

#ifndef INC_STM32F103C6_RCC_DRIVER_H_
#define INC_STM32F103C6_RCC_DRIVER_H_
/*--------------------------------------------Includes Start----------------------------------*/
#include "stm32f103c6_LQFP48.h"
#include "stm32f103c6_RCC_driver_Cfg.h"
//#include "stm32f103c6_GPIO_driver.h"
/*--------------------------------------------Includes End----------------------------------*/

/*--------------------------------------------Macro Declaration----------------------------------*/

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define CLK_GPIOA_EN		(RCC->APB2ENR |= (1<<2));
#define CLK_GPIOB_EN		(RCC->APB2ENR |= (1<<3));
#define CLK_GPIOC_EN		(RCC->APB2ENR |= (1<<4));
#define CLK_GPIOD_EN		(RCC->APB2ENR |= (1<<5));

#define CLK_AFIO_EN			(RCC->APB2ENR |= (1<<0));

#define CLK_USART1_EN		(RCC->APB2ENR |= (1<<14));
#define CLK_USART2_EN		(RCC->APB1ENR |= (1<<17));
#define CLK_USART3_EN		(RCC->APB1ENR |= (1<<18));

#define CLK_SPI1_EN			(RCC->APB2ENR |= (1<<12));
#define CLK_SPI2_EN			(RCC->APB1ENR |= (1<<14));

#define CLK_I2C1_EN			(RCC->APB1ENR |= (1<<21));
#define CLK_I2C2_EN			(RCC->APB1ENR |= (1<<22));


#define CLK_TIM2_EN			(RCC->APB1ENR |= (1<<0));
#define CLK_TIM3_EN			(RCC->APB1ENR |= (1<<1));
#define CLK_TIM4_EN			(RCC->APB1ENR |= (1<<2));

#define CLK_TIM2_DEN		(RCC->APB1ENR &= ~(1<<0));///////////////////////
#define CLK_TIM3_DEN		(RCC->APB1ENR &= ~(1<<1));
#define CLK_TIM4_DEN		(RCC->APB1ENR &= ~(1<<2));


#define CLK_ADC1_EN			(RCC->APB2ENR |= (1<<9));
#define CLK_ADC2_EN			(RCC->APB2ENR |= (1<<10));

//-*-*-*-*-*-*-*-*-*-*-*-
//Rest Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define CLK_GPIOA_RST		(RCC->APB2RSTR |= (1<<2));\
							(RCC->APB2RSTR &= ~(1<<2));
#define CLK_GPIOB_RST		(RCC->APB2RSTR |= (1<<3));\
							(RCC->APB2RSTR &= ~(1<<3));
#define CLK_GPIOC_RST		(RCC->APB2RSTR |= (1<<4));\
							(RCC->APB2RSTR &= ~(1<<4));
#define CLK_GPIOD_RST		(RCC->APB2RSTR |= (1<<5));\
							(RCC->APB2RSTR &= ~(1<<5));

#define CLK_AFIO_RST		(RCC->APB2RSTR |= (1<<0));\
							(RCC->APB2RSTR &= ~(1<<0));

#define CLK_USART1_RST		(RCC->APB2RSTR |= (1<<14));\
							(RCC->APB2RSTR &= ~(1<<14));

#define CLK_USART2_RST		(RCC->APB1RSTR |= (1<<17));\
							(RCC->APB1RSTR &= ~(1<<17));

#define CLK_USART3_RST		(RCC->APB1RSTR |= (1<<18));\
							(RCC->APB1RSTR &= ~(1<<18));

#define CLK_SPI1_RST		(RCC->APB1RSTR |= (1<<12));\
							(RCC->APB1RSTR &= ~(1<<12));

#define CLK_SPI2_RST		(RCC->APB1RSTR |= (1<<14));\
							(RCC->APB1RSTR &= ~(1<<14));

#define CLK_I2C1_RST		(RCC->APB1RSTR |= (1<<21));\
							(RCC->APB1RSTR &= ~(1<<21));

#define CLK_I2C2_RST		(RCC->APB1RSTR |= (1<<22));\
							(RCC->APB1RSTR &= ~(1<<22));

#define CLK_TIM2_RST		(RCC->APB1RSTR |= (1<<0));\
							(RCC->APB1RSTR &= ~(1<<0));

#define CLK_TIM3_RST		(RCC->APB1RSTR |= (1<<1));\
							(RCC->APB1RSTR &= ~(1<<1));

#define CLK_TIM4_RST		(RCC->APB1RSTR |= (1<<2));\
							(RCC->APB1RSTR &= ~(1<<2));


#define CLK_ADC1_RST		(RCC->APB2RSTR |= (1<<9));
							/* \
							//(RCC->APB2RSTR &= ~(1<<9));*/

#define CLK_ADC2_RST		(RCC->APB2RSTR |= (1<<10));\
							(RCC->APB2RSTR &= ~(1<<10));


//@ref SYS_CLK

#define HSI_SYS_CLK					(uint32_t)8000000
#define HSE_SYS_CLK					(uint32_t)16000000
#define PLL_SYS_CLK					(uint32_t)16000000

#define RCC_CR_HSEON_Pos				16UL					/*RCC-CR : HSE ENABLE bit Position [16 bit]*/
#define RCC_CR_HSEON_Mask				(1UL << RCC_CR_HSEON_Pos)

#define RCC_CR_HSERDY_Pos				17UL					/*RCC-CR : HSE RDY bit Position [17 bit]*/
#define RCC_CR_HSERDY_Mask				(1UL << RCC_CR_HSERDY_Pos)

#define RCC_CR_HSEBYP_Pos				18UL					/*RCC-CR : HSE BYP bit Position [18 bit]*/
#define RCC_CR_HSEBYP_Mask				(1UL << RCC_CR_HSEBYP_Pos)

#define RCC_CR_HSION_Pos				0UL						/*RCC-CR : HSI ON bit Position [0 bit]*/
#define RCC_CR_HSION_Mask				(1UL << RCC_CR_HSION_Pos)

#define RCC_CR_HSICAL_Pos				8UL						/*RCC-CR : HSI CAL bit Position [8:15 bit]*/
#define RCC_CR_HSICAL_Mask				(0xFFUL << RCC_CR_HSICAL_Pos)

#define RCC_CR_HSITRIM_Pos				3UL						/*RCC-CR : HSI TRIM bit Position [3:7 bit]*/
#define RCC_CR_HSITRIM_Mask				(0x1FUL << RCC_CR_HSITRIM_Pos)

#define RCC_CR_HSIRDY_Pos				1UL						/*RCC-CR : HSI RDY bit Position [1 bit]*/
#define RCC_CR_HSIRDY_Mask				(1UL << RCC_CR_HSIRDY_Pos)

#define RCC_CR_PLLRDY_Pos				25UL					/*RCC-CR : PLL RDY bit Position [25 bit]*/
#define RCC_CR_PLLRDY_Mask				(1UL << RCC_CR_PLLRDY_Pos)

#define RCC_CR_PLLON_Pos				24UL					/*RCC-CR : PLL ON bit Position [24 bit]*/
#define RCC_CR_PLLON_Mask				(1UL << RCC_CR_PLLON_Pos)

#define RCC_CR_CSSON_Pos				19UL					/*RCC-CR : CSS ON bit Position [19 bit]*/
#define RCC_CR_CSSON_Mask				(1UL << RCC_CR_CSSON_Pos)

#define RCC_CIR_HSERDYF_Pos				3UL						/*RCC-CIR : HSE RDYF bit Position [3 bit]*/
#define RCC_CIR_HSERDYF_Mask			(1UL << RCC_CIR_HSERDYF_Pos)

#define RCC_CIR_HSERDYC_Pos				19UL					/*RCC-CIR : HSE RDYC bit Position [19 bit]*/
#define RCC_CIR_HSERDYC_Mask			(1UL << RCC_CIR_HSERDYC_Pos)

#define RCC_CIR_HSERDYIE_Pos			11UL					/*RCC-CIR : HSE RDYIE bit Position [11 bit]*/
#define RCC_CIR_HSERDYIE_Mask			(1UL << RCC_CIR_HSERDYIE_Pos)

#define RCC_CIR_LSERDYF_Pos				1UL						/*RCC-CIR : LSE RDYF bit Position [1 bit]*/
#define RCC_CIR_LSERDYF_Mask			(1UL << RCC_CIR_LSERDYF_Pos)

#define RCC_CIR_LSERDYC_Pos				17UL					/*RCC-CIR : LSE RDYC bit Position [17 bit]*/
#define RCC_CIR_LSERDYC_Mask			(1UL << RCC_CIR_LSERDYC_Pos)

#define RCC_CIR_LSERDYIE_Pos			9UL						/*RCC-CIR : LSE RDYIE bit Position [9 bit]*/
#define RCC_CIR_LSERDYIE_Mask			(1UL << RCC_CIR_LSERDYIE_Pos)

#define RCC_CIR_LSIRDYF_Pos				0UL						/*RCC-CIR : LSI RDYF bit Position [0 bit]*/
#define RCC_CIR_LSIRDYF_Mask			(1UL << RCC_CIR_LSIRDYF_Pos)

#define RCC_CIR_LSIRDYC_Pos				16UL					/*RCC-CIR : LSI RDYC bit Position [16 bit]*/
#define RCC_CIR_LSIRDYC_Mask			(1UL << RCC_CIR_LSIRDYC_Pos)

#define RCC_CIR_LSIRDYIE_Pos			8UL						/*RCC-CIR : LSI RDYIE bit Position [8 bit]*/
#define RCC_CIR_LSIRDYIE_Mask			(1UL << RCC_CIR_LSIRDYIE_Pos)
//************************************************************************************
#define RCC_CIR_HSIRDYF_Pos				2UL						/*RCC-CIR : HSI RDYF bit Position [2 bit]*/
#define RCC_CIR_HSIRDYF_Mask			(1UL << RCC_CIR_HSIRDYF_Pos)

#define RCC_CIR_HSIRDYC_Pos				18UL					/*RCC-CIR : HSI RDYC bit Position [18 bit]*/
#define RCC_CIR_HSIRDYC_Mask			(1UL << RCC_CIR_HSIRDYC_Pos)

#define RCC_CIR_HSIRDYIE_Pos			10UL					/*RCC-CIR : HSI RDYIE bit Position [10 bit]*/
#define RCC_CIR_HSIRDYIE_Mask			(1UL << RCC_CIR_HSIRDYIE_Pos)

#define RCC_CIR_PLLRDYF_Pos				4UL						/*RCC-CIR : PLL RDYF bit Position [4 bit]*/
#define RCC_CIR_PLLRDYF_Mask			(1UL << RCC_CIR_PLLRDYF_Pos)

#define RCC_CIR_PLLRDYC_Pos				20UL					/*RCC-CIR : PLL RDYC bit Position [20 bit]*/
#define RCC_CIR_PLLRDYC_Mask			(1UL << RCC_CIR_PLLRDYC_Pos)

#define RCC_CIR_PLLRDYIE_Pos			12UL					/*RCC-CIR : PLL RDYIE bit Position [12 bit]*/
#define RCC_CIR_PLLRDYIE_Mask			(1UL << RCC_CIR_PLLRDYIE_Pos)

#define RCC_CIR_CSSF_Pos				7UL						/*RCC-CIR : CSSF bit Position [7 bit]*/
#define RCC_CIR_CSSF_Mask				(1UL << RCC_CIR_CSSF_Pos)

#define RCC_CIR_CSSC_Pos				23UL					/*RCC-CIR : CSSC bit Position [23 bit]*/
#define RCC_CIR_CSSC_Mask				(1UL << RCC_CIR_CSSC_Pos)

#define RCC_CFGR_USBPRE_Pos				22UL					/*RCC-CFGR : USB PRE bit Position [22 bit]*/
#define RCC_CFGR_USBPRE_Mask			(1UL << RCC_CFGR_USBPRE_Pos)
				/*48 MHZ. This bit must be valid before enabling the USB clock in the RCC_APB1ENR register.
				This bit can’t be reset if the USB clock is enabled*/
#define RCC_CFGR_ADCPRE_Pos				14UL					/*RCC-CFGR : ADC PRE bit Position [14:15 bit]*/
#define RCC_CFGR_ADCPRE_Mask			(3UL << RCC_CFGR_ADCPRE_Pos)

#define RCC_CFGR_PPRE2_Pos				11UL					/*RCC-CFGR : PCLK2 bit Position [11:13 bit]*/
#define RCC_CFGR_PPRE2_Mask			    (7UL << RCC_CFGR_PPRE2_Pos)

#define RCC_CFGR_PPRE1_Pos				8UL						/*RCC-CFGR : PCLK1 bit Position [8:10 bit]*/
#define RCC_CFGR_PPRE1_Mask			    (7UL << RCC_CFGR_PPRE1_Pos)

#define RCC_CFGR_HPRE_Pos				4UL						/*RCC-CFGR : AHB bit Position [4:7 bit]*/
#define RCC_CFGR_HPRE_Mask			    (0xFUL << RCC_CFGR_HPRE_Pos)

#define RCC_CFGR_SW_Pos					0UL						/*RCC-CFGR : SW bit Position [0:1 bit]*/
#define RCC_CFGR_SW_Mask			    (3UL << RCC_CFGR_SW_Pos)

#define RCC_CFGR_SWS_Pos				2UL						/*RCC-CFGR : SWS bit Position [2:3 bit]*/
#define RCC_CFGR_SWS_Mask			    (3UL << RCC_CFGR_SWS_Pos)

#define RCC_CFGR_PLLMUL_Pos				18UL					/*RCC-CFGR : PLL MUL bit Position [18:21 bit]*/
#define RCC_CFGR_PLLMUL_Mask			(0xFUL << RCC_CFGR_PLLMUL_Pos)

#define RCC_CFGR_PLLXTPRE_Pos			17UL					/*RCC-CFGR : PLL XTPRE bit Position [17 bit]*/
#define RCC_CFGR_PLLXTPRE_Mask			(1UL << RCC_CFGR_PLLXTPRE_Pos)

#define RCC_CFGR_PLLSRC_Pos				16UL					/*RCC-CFGR : PLL SRC bit Position [16 bit]*/
#define RCC_CFGR_PLLSRC_Mask			(3UL << RCC_CFGR_PLLSRC_Pos)

#define RCC_CFGR_MCO_Pos				24UL					/*RCC-CFGR : MCO bit Position [24:26 bit]*/
#define RCC_CFGR_MCO_Mask				(7UL << RCC_CFGR_MCO_Pos)

#define RCC_BDCR_LSEON_Pos				0UL						/*RCC-BDCR : LSE ENABLE bit Position [0 bit]*/
#define RCC_BDCR_LSEON_Mask				(1UL << RCC_BDCR_LSEON_Pos)

#define RCC_BDCR_LSERDY_Pos				1UL						/*RCC-BDCR : LSE RDY bit Position [1 bit]*/
#define RCC_BDCR_LSERDY_Mask			(1UL << RCC_BDCR_LSERDY_Pos)

#define RCC_BDCR_LSEBYP_Pos				2UL						/*RCC-BDCR : LSE BYP bit Position [2 bit]*/
#define RCC_BDCR_LSEBYP_Mask			(1UL << RCC_BDCR_LSEBYP_Pos)

#define RCC_BDCR_BDRST_Pos				16UL					/*RCC-BDCR : BD RST bit Position [16 bit]*/
#define RCC_BDCR_BDRST_Mask				(1UL << RCC_BDCR_BDRST_Pos)

#define RCC_BDCR_RTCEN_Pos				15UL					/*RCC-BDCR : RTC EN bit Position [15 bit]*/
#define RCC_BDCR_RTCEN_Mask				(1UL << RCC_BDCR_RTCEN_Pos)

#define RCC_BDCR_RTCSEL_Pos				8UL						/*RCC-BDCR : RTC SEL bit Position [8:9 bit]*/
#define RCC_BDCR_RTCSEL_Mask			(3UL << RCC_BDCR_RTCSEL_Pos)

#define RCC_CSR_LSION_Pos				0UL						/*RCC-CSR : LSI ENABLE bit Position [0 bit]*/
#define RCC_CSR_LSION_Mask				(1UL << RCC_CSR_LSION_Pos)

#define RCC_CSR_LSIRDY_Pos				1UL						/*RCC-CSR : LSI RDY bit Position [1 bit]*/
#define RCC_CSR_LSIRDY_Mask				(1UL << RCC_CSR_LSIRDY_Pos)

#define RCC_CSR_IWDGRSTF_Pos			29UL					/*RCC-CSR : IWDG RST F bit Position [29 bit]*/
#define RCC_CSR_IWDGRSTF_Mask			(1UL << RCC_CSR_IWDGRSTF_Pos)

/************************** AFIO remap **************************************/

#define AFIO_MAPR_PD01_REMAP_Pos		15UL				/*AFIO-MAPR : PD01_REMAP bit Position [15 bit]*/
#define AFIO_MAPR_PD01_REMAP_Mask		(1UL << AFIO_MAPR_PD01_REMAP_Pos)
/* Port D0/Port D1 mapping on OSC_IN/OSC_OUT		[HSE]*/



/*--------------------------------------------Macro Declaration----------------------------------*/

/*--------------------------------------------Macro Functions Declaration----------------------------------*/
/*--------------------------------------------Macro Functions Declaration----------------------------------*/

/*--------------------------------------------Data Type Declaration----------------------------------*/
typedef void(*ptr_function)(void);

typedef enum
{
	MCAL_NOK	,
	MCAL_OK
}RetStatus_t;

typedef enum
{
	HSI		,
	HSE 	,
	PLL 	,
	Error
}Sys_CLK_status_t;

typedef struct
{
	uint8_t CLK_Source_Selection ;
	enable_mechanism mechanism ;
	uint8_t External_oscillator ;			//@ref external clock
	uint8_t PLL_HSE_prescaler:1 ;			//@ref HSE divider for PLL entry
	uint8_t PLL_Multiplier:4 ;				//@ref PLL multiplication factor
}RCC_CONFIG_t;

typedef struct
{
	uint8_t AHB_prescaler:4 ;				//@ref  AHB prescaler
	uint8_t APB1_prescaler:3 ;				//@ref  [ APB low-speed prescaler (APB1) PCLK1]
	uint8_t APB2_prescaler:3 ;				//@ref  [APB high-speed prescaler (APB2) PCLK2]
	uint8_t ADC_prescaler:2 ;				//@ref ADC prescaler
	uint8_t USB_prescaler:1 ;				//@ref USB prescaler
	uint8_t reversed:3 ;

}RCC_PRESCALER_t;





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
RetStatus_t RCC_SYS_CLK_Config(RCC_CONFIG_t* CLK_SRC,ptr_function IRQ_handler);
RetStatus_t RCC_CLK_prescaler(RCC_PRESCALER_t * prescaler);
RetStatus_t RCC_SYS_CLK_Selection(void);
Sys_CLK_status_t RCC_Get_SYS_CLK_Source(void);
void RCC_Clock_security_Init(ptr_function IRQ_failure_handler);
void RCC_RTC_CLK_Init(void);

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
uint32_t RCC_GET_SYS_CLK(void);
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
uint32_t RCC_GET_PCLK1_CLK(void);
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
uint32_t RCC_GET_PCLK2_CLK(void);
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
uint32_t RCC_GET_HCLK_CLK(void);

/*--------------------------------------------Software Interface Declaration-------------------------------*/

#endif /* INC_STM32F103C6_RCC_DRIVER_H_ */
