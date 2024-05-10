/*
 ******************************************************************************
 * @file           : CortexM3_Core_SCB.h
 * @author         : Ahmed Ashraf Mahgob Ahmed
 * @brief          : Contain the code to Control NVIC
 ******************************************************************************
**/
#ifndef INC_CORTEXM3_CORTEXM3_CORE_SCB_H_
#define INC_CORTEXM3_CORTEXM3_CORE_SCB_H_
/*--------------------------------------------Includes Start----------------------------------*/
#include <stdint.h>
/*--------------------------------------------Includes End----------------------------------*/

/*--------------------------------------------Macro Declaration----------------------------------*/
#define SCB_BASE  							0xE000ED00UL
#define SCB								((SCB_t *)(SCB_BASE))
/*
 * 		@ref group priority		<The PRIGROUP field indicates the position of the binary point that
 * 									splits the PRI_n fields in the Interrupt Priority Registers into separate
									group priority and sub priority fields. Table 45
									shows how the PRIGROUP value controls this split>
 * */
typedef enum
{
		 GroupPriority_16_SubPriority_0		=0x3,		/* <4> bits Group priority and <None> bits Subpriority*/
		 GroupPriority_8_SubPriority_2		=0x4,		/* <3> bits Group priority and <1> bits Subpriority*/
		 GroupPriority_4_SubPriority_4		=0x5,		/* <2> bits Group priority and <2> bits Subpriority*/
		 GroupPriority_2_SubPriority_8		=0x6,		/* <1> bits Group priority and <3> bits Subpriority*/
		 GroupPriority_0_SubPriority_16		=0x7		/* <None> bits Group priority and <4> bits Subpriority*/
}GroupPriority_t;


/*
 * 		@ref Registers		<Data about the SBC-Registers>
 * */
#define SBC_AIRCR_VECTKEYSTAT_Pos			16		/*SBC-AIRCR : VECTKEYSTAT bits Position	[16 bits]*/
#define SBC_AIRCR_PRIGROUP_Pos				8		/*SBC-AIRCR : PRIGROUP bits Position [3 bits]*/
#define SBC_AIRCR_VECTKEYSTAT_Mask			(0xFFFFUL << SBC_AIRCR_VECTKEYSTAT_Pos )
#define SBC_AIRCR_PRIGROUP_Mask				(0x7UL << SBC_AIRCR_PRIGROUP_Pos )
#define SBC_AIRCR_VECTKEYSTAT_Key			0x5FAUL
/*--------------------------------------------Macro Declaration----------------------------------*/

/*--------------------------------------------Macro Functions Declaration----------------------------------*/
/*--------------------------------------------Macro Functions Declaration----------------------------------*/

/*--------------------------------------------Data Type Declaration----------------------------------*/

	//read/clear (rc_w1) Software can read as well as clear this bit by writing 1. Writing ‘0’ has
	//	no effect on the bit value.
typedef struct
{
	volatile uint32_t CPUID;	/* Offset : 0x000 (R)  Privileged  CPUID base register*/
	volatile uint32_t ICSR;		/* Offset : 0x004 (R/W)->(not all) Privileged  Interrupt control and state register*/
	volatile uint32_t VTOR;		/* Offset : 0x008(R/W)  Privileged  Vector table offset register*/
	volatile uint32_t AIRCR;	/* Offset : 0x00C(R/W) Privileged  Application interrupt and reset control register*/
	/*Reads as 0xFA05--------------On writes, write 0x5FA to VECTKEY, otherwise the write is ignored.*/
	volatile uint32_t SCR;		/* Offset : 0x010 (R/W)  Privileged  System control register*/
	volatile uint32_t CCR;		/* Offset : 0x014 (R/W)  Privileged  Configuration and control register*/
	volatile uint32_t SHPR1;	/* Offset : 0x018 (R/W)->(not all)  Privileged  System handler priority registers*//*you can make it array*/
	volatile uint32_t SHPR2;	/* Offset : 0x01C (R/W)->(not all)  Privileged  System handler priority registers*/
	volatile uint32_t SHPR3;	/* Offset : 0x020 (R/W)->(not all)  Privileged  System handler priority registers*/
	volatile uint32_t SHCRS;	/* Offset : 0x024 (R/W)  Privileged  System handler control and state register*/
	volatile uint32_t CFSR;		/* Offset : 0x028 (R/W)  Privileged  Configurable fault status register*/
	volatile uint32_t HFSR;		/* Offset : 0x02C (rc_w1)  Hard fault status register*/
	uint32_t Reserved ;
	volatile uint32_t MMAR;		/* Offset : 0x034 (R/W)  Privileged  Memory management fault address register*/
	volatile uint32_t BFAR;		/* Offset : 0x038 (R/W)  Privileged  Bus fault address register*/


}SCB_t;

/**
 * 	@brief STM32F1XXX	Interrupt Number Definition
*/




/*--------------------------------------------Data Type Declaration----------------------------------*/

/*--------------------------------------------Software Interface Declaration-------------------------------*/
/**
 * 	@brief			Set Priority Group
 *  @details		The AIRCR provides priority grouping control for the exception model
 *  				using the sequence by writing 0x5FA to VECTKEY bits [16:31]
 *  				and set the PRIGROUP bits [8:10] which can take a value from 3 to 7
 *  @parameter[in]  priority Number of group priority and sub priority
 *  @note			priority must be a value from @ref group priority
 */
void SBC_SetPriority_Group(GroupPriority_t priority);
/**
 * 	@brief			Get Priority Group
 *  @details		Reads Priority Group bits(PRIGROUP) in AIRCR register in system control block
 *  @return			Priority Group field in AIRCR register
 *  @note			the processor write 0xFA05 which is the read value to VECTKEY bits [16:31] automatically
 */
uint32_t SBC_GetPriority_Group(void);
/**
 * 	@brief			Set Pending Interrupt
 *  @details		Set Pending Interrupt bit for specific device in NVIC Controller
 *  @parameter[in]  IRQn Interrupt Number for specific device
 *  @note			IRQn must be Positive Value OR Zero
 */

/**
 * 	@brief			Clear Pending Interrupt
 *  @details		Clear Pending Interrupt bit for specific device in NVIC Controller
 *  @parameter[in]  IRQn Interrupt Number for specific device
 *  @note			IRQn must be Positive Value OR Zero
 */

/**
 * 	@brief			Get Active Interrupt
 *  @details		Read active Interrupt bit in active register for specific device in NVIC Controller
 *  @parameter[in]  IRQn Interrupt Number for specific device
 *  @note			IRQn must be Positive Value OR Zero
 */



/*--------------------------------------------Software Interface Declaration-------------------------------*/



#endif /* INC_CORTEXM3_CORTEXM3_CORE_SCB_H_ */
