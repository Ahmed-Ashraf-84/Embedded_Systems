/**
 ******************************************************************************
 * @file           : CortexM3_Core_NVIC.h
 * @author         : Ahmed Ashraf Mahgob Ahmed
 * @brief          : Contain the code to Control NVIC
 ******************************************************************************
**/

#ifndef INC_CORTEXM3_CORTEXM3_CORE_NVIC_H_
#define INC_CORTEXM3_CORTEXM3_CORE_NVIC_H_
/*--------------------------------------------Includes Start----------------------------------*/
#include <stdint.h>
/*--------------------------------------------Includes End----------------------------------*/

/*--------------------------------------------Macro Declaration----------------------------------*/
#define NVCI_BASEE  							0xE000E100UL
#define NVIC								((NVIC_t *)(NVCI_BASEE))

/*
 * 		@ref Registers		<Data about the SBC-Registers>
 * */

#define	NVIC_IPR_Pos						0x4
#define	NVIC_IPR_Mask						(0xF<<NVIC_IPR_Pos)
/*--------------------------------------------Macro Declaration----------------------------------*/

/*--------------------------------------------Macro Functions Declaration----------------------------------*/
/*--------------------------------------------Macro Functions Declaration----------------------------------*/

/*--------------------------------------------Data Type Declaration----------------------------------*/

	//read/clear (rc_w1) Software can read as well as clear this bit by writing 1. Writing ‘0’ has
	//	no effect on the bit value.
typedef struct
{
	volatile uint32_t ISER[3];		 /* Offset : 0x000 (R/W)  Privileged  Interrupt set-enable registers*/
	uint32_t Reserved0[29];
	volatile uint32_t ICER[3];		/* Offset : 0x080 (R/W) (rc_w1) Privileged  Interrupt clear-enable registers*/
	uint32_t Reserved1[29];
	volatile uint32_t ISPR[3];		/* Offset : 0x100(R/W)  Privileged  Interrupt set-pending registers*/
	uint32_t Reserved2[29];
	volatile uint32_t ICPR[3];		/* Offset : 0x180 (R/W) (rc_w1) Privileged  Interrupt clear-pending registers*/
	uint32_t Reserved3[29];
	volatile uint32_t IABR[3];		/* Offset : 0x200 (R)  Privileged  Interrupt active bit registers*/
	uint32_t Reserved4[61];
	volatile uint32_t IPR[81];		/* Offset : 0x300 (R/W)  Privileged  Interrupt priority registers*/
	uint8_t Reserved5[3];			/* the last register has the last 3 bytes reserved */
	uint32_t Reserved6[695];
	volatile uint32_t STIR;			/* Offset : 0xE00 (W)  Privileged  Software trigger interrupt register	INTID[8:0]*/

}NVIC_t;

/**
 * 	@brief STM32F1XXX	Interrupt Number Definition
*/
typedef enum
{
	//****************************Cortex-M3 Processor Exceptions Numbers *****************************
	NMI_IRQ						=-14,		/* Non maskable interrupt*/
	MemManage_IRQ				=-12,		/* Cortex-M3 Memory management interrupt*/
	BusFault_IRQ				=-11,		/* Cortex-M3 BusFault interrupt*/
	UsageFault_IRQ				=-10,		/* Cortex-M3 UsageFault interrupt*/
	SVCall_IRQ					=-5,		/* Cortex-M3 SVCall interrupt*/
	DebugMonitor_IRQ			=-4,		/* Cortex-M3 Debug Monitor interrupt*/
	PendSV_IRQ					=-2,		/* Cortex-M3 PendSV interrupt*/
	SysTick_IRQ					=-1,		/* Cortex-M3 System tick timer interrupt*/
	//****************************STM32 Interrupt Numbers *****************************
	WWDG_IRQ					=0,
	PVD_IRQ						=1,
	TAMPER_IRQ					=2,
	RTC_IRQ						=3,
	FLASH_IRQ					=4,
	RCC_IRQ						=5,
	EXTI0_IRQ					=6,
	EXTI1_IRQ					=7,
	EXTI2_IRQ					=8,
	EXTI3_IRQ					=9,
	EXTI4_IRQ					=10,
	DMA1_Channel1_IRQ			=11,
	DMA1_Channel2_IRQ			=12,
	DMA1_Channel3_IRQ			=13,
	DMA1_Channel4_IRQ			=14,
	DMA1_Channel5_IRQ			=15,
	DMA1_Channel6_IRQ			=16,
	DMA1_Channel7_IRQ			=17,
	ADC1_2_IRQ					=18,
    USB_HP_CAN_TX_IRQ			=19,
	USB_LP_CAN_RX0_IRQ			=20,
	CAN_RX1_IRQ					=21,
	CAN_SCE_IRQ					=22,
	EXTI9_5_IRQ					=23,
	TIM1_BRK_IRQ				=24,
	TIM1_UP_IRQ					=25,
	TIM1_TRG_COM_IRQ			=26,
	TIM1_CC_IRQ					=27,
	TIM2_IRQ					=28,
	TIM3_IRQ					=29,
	TIM4_IRQ					=30,
	I2C1_EV_IRQ					=31,
	I2C1_ER_IRQ					=32,
	I2C2_EV_IRQ					=33,
	I2C2_ER_IRQ					=34,
	SPI1_IRQ					=35,
	SPI2_IRQ					=36,
	USART1_IRQ					=37,
	USART2_IRQ					=38,
	USART3_IRQ					=39,
	EXTI15_10_IRQ				=40,
	RTCAlarm_IRQ				=41,
	USBWakeup_IRQ				=42,
	TIM8_BRK_IRQ				=43,
	TIM8_UP_IRQ					=44,
	TIM8_TRG_COM_IRQ			=45,
	TIM8_CC_IRQ					=46,
	ADC3_IRQ					=47,
	FSMC_IRQ					=48,
	SDIO_IRQ					=49,
	TIM5_IRQ					=50,
	SPI3_IRQ					=51,
	UART4_IRQ					=52,
	UART5_IRQ					=53,
	TIM6_IRQ					=54,
	TIM7_IRQ					=55,
	DMA2_Channel1_IRQ			=56,
	DMA2_Channel2_IRQ			=57,
	DMA2_Channel3_IRQ			=58,
	DMA2_Channel4_5_IRQ			=59
}IRQN_t;



/*--------------------------------------------Data Type Declaration----------------------------------*/

/*--------------------------------------------Software Interface Declaration-------------------------------*/
/**
 * 	@brief			Enable Interrupt
 *  @details		Enable Interrupt for specific device in NVIC Controller
 *  @parameter[in]  IRQn Interrupt Number for specific device
 *  @note			IRQn must be Positive Value OR Zero
 */
void NVIC_Enable_IRQ(IRQN_t IRQn);
/**
 * 	@brief			Disable Interrupt
 *  @details		Disable Interrupt for specific device in NVIC Controller
 *  @parameter[in]  IRQn Interrupt Number for specific device
 *  @note			IRQn must be Positive Value OR Zero
 */
void NVIC_Disable_IRQ(IRQN_t IRQn);
/**
 * 	@brief			Set Pending Interrupt
 *  @details		Set Pending Interrupt bit for specific device in NVIC Controller
 *  @parameter[in]  IRQn Interrupt Number for specific device
 *  @note			IRQn must be Positive Value OR Zero
 */
void NVIC_SetPending_IRQ(IRQN_t IRQn);
/**
 * 	@brief			Clear Pending Interrupt
 *  @details		Clear Pending Interrupt bit for specific device in NVIC Controller
 *  @parameter[in]  IRQn Interrupt Number for specific device
 *  @note			IRQn must be Positive Value OR Zero
 */
void NVIC_ClearPending_IRQ(IRQN_t IRQn);
/**
 * 	@brief			Get Active Interrupt
 *  @details		Read active Interrupt bit in active register for specific device in NVIC Controller
 *  @parameter[in]  IRQn Interrupt Number for specific device
 *  @note			IRQn must be Positive Value OR Zero
 */
uint32_t NVIC_GetActive_IRQ(IRQN_t IRQn);
/**
 * 	@brief			Set Interrupt Priority
 *  @details		set the priority value in priority bits [4:7] in IPRn register
 *  					for specific device in NVIC Controller
 *  @parameter[in]  IRQn Interrupt Number for specific device
 *  @parameter[in]  priority specify the group priority number and sub priority number for IRQn device
 *  					according to SCB(system control block)-AIRCR register in bit field [8:10]
 *  @note			IRQn must be Positive Value OR Zero
 *  @note			you must config the AIRCR register in system control block use
 *  					the function void SBC_SetPriority_Group(GroupPriority_t priority); in SBC-lib
 */
void NVIC_SetPriority_IRQ(IRQN_t IRQn ,uint8_t priority);

/**
 * 	@brief			Get Interrupt Priority
 *  @details		Reads priority bits [4:7] in IPRn register
 *  @parameter[in]  IRQn Interrupt Number for specific device
 *  @note			IRQn must be Positive Value OR Zero
 */
uint32_t NVIC_GetPriority_IRQ(IRQN_t IRQn);
/*--------------------------------------------Software Interface Declaration-------------------------------*/


#endif /* INC_CORTEXM3_CORTEXM3_CORE_NVIC_H_ */
