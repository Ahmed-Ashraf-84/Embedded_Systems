/**
 ******************************************************************************
 * @file           : CortexM3_Core_NVIC.c
 * @author         : Ahmed Ashraf Mahgob Ahmed
 * @brief          : Contain the code to Control NVIC
 ******************************************************************************
**/


/*--------------------------------------------Includes Start----------------------------------*/
#include "CortexM3/CortexM3_Core_NVIC.h"

/*--------------------------------------------Includes End----------------------------------*/

/*--------------------------------------------Macro Declaration----------------------------------*/
/*--------------------------------------------Macro Declaration----------------------------------*/

/*--------------------------------------------Macro Functions Declaration----------------------------------*/
/*--------------------------------------------Macro Functions Declaration----------------------------------*/

/*--------------------------------------------Data Type Declaration----------------------------------*/
/*--------------------------------------------Data Type Declaration----------------------------------*/

/*--------------------------------------------Software Interface Declaration-------------------------------*/

/**
 * 	@brief			Enable Interrupt
 *  @details		Enable Interrupt for specific device in NVIC Controller
 *  @parameter[in]  IRQn Interrupt Number for specific device
 *  @note			IRQn must be Positive Value OR Zero
 */
void NVIC_Enable_IRQ(IRQN_t IRQn)
{
	if((uint32_t)IRQn >= 0)
	{
		NVIC->ISER[(((uint32_t)IRQn)>>5)] |= (1UL<<((uint32_t)IRQn & 0x1F));
	}
	else {/*nothing*/}

}
/**
 * 	@brief			Disable Interrupt
 *  @details		Disable Interrupt for specific device in NVIC Controller
 *  @parameter[in]  IRQn Interrupt Number for specific device
 *  @note			IRQn must be Positive Value OR Zero
 */
void NVIC_Disable_IRQ(IRQN_t IRQn)
{
	if((uint32_t)IRQn >= 0)
	{
		NVIC->ICER[(((uint32_t)IRQn)>>5)] |= (1UL<<((uint32_t)IRQn & 0x1F));
	}
	else {/*nothing*/}
}
/**
 * 	@brief			Set Pending Interrupt
 *  @details		Set Pending Interrupt bit for specific device in NVIC Controller
 *  @parameter[in]  IRQn Interrupt Number for specific device
 *  @note			IRQn must be Positive Value OR Zero
 */
void NVIC_SetPending_IRQ(IRQN_t IRQn)
{
	if((uint32_t)IRQn >= 0)
	{
		NVIC->ISPR[(((uint32_t)IRQn)>>5)] |= (1UL<<((uint32_t)IRQn & 0x1F));
	}
	else {/*nothing*/}
}
/**
 * 	@brief			Clear Pending Interrupt
 *  @details		Clear Pending Interrupt bit for specific device in NVIC Controller
 *  @parameter[in]  IRQn Interrupt Number for specific device
 *  @note			IRQn must be Positive Value OR Zero
 */
void NVIC_ClearPending_IRQ(IRQN_t IRQn)
{
	if((uint32_t)IRQn >= 0)
	{
		NVIC->ICPR[(((uint32_t)IRQn)>>5)] |= (1UL<<((uint32_t)IRQn & 0x1F));
	}
	else {/*nothing*/}
}
/**
 * 	@brief			Get Active Interrupt
 *  @details		Read active Interrupt bit in active register for specific device in NVIC Controller
 *  @parameter[in]  IRQn Interrupt Number for specific device
 *  @note			IRQn must be Positive Value OR Zero
 */
uint32_t NVIC_GetActive_IRQ(IRQN_t IRQn)
{
	if((uint32_t)IRQn >= 0)
	{
		return ((NVIC->IABR[(((uint32_t)IRQn)>>5)] & (1UL<<((uint32_t)IRQn & 0x1F))) == 0UL ? 0UL : 1UL );
		//return ((NVIC->IABR[(((uint32_t)IRQn)>>5)] & (1UL<<((uint32_t)IRQn & 0x1F)))>>(1UL<<((uint32_t)IRQn & 0x1F)));
	}
	else {
		return 0Ul;
		}
}

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
void NVIC_SetPriority_IRQ(IRQN_t IRQn ,uint8_t priority)
{
	if((uint32_t)IRQn >= 0)
	{
		NVIC->IPR[(uint32_t)IRQn] = (uint8_t)(priority << NVIC_IPR_Pos) ;
	}
	else {/*nothing*/}

}

/**
 * 	@brief			Get Interrupt Priority
 *  @details		Reads priority bits [4:7] in IPRn register
 *  @parameter[in]  IRQn Interrupt Number for specific device
 *  @note			IRQn must be Positive Value OR Zero
 */
uint32_t NVIC_GetPriority_IRQ(IRQN_t IRQn)
{
	if((uint32_t)IRQn >= 0)
	{
		uint32_t ret_value = 0 ;
		ret_value = NVIC->IPR[(uint32_t)IRQn] ;
		ret_value &= (NVIC_IPR_Mask);
		ret_value >>= NVIC_IPR_Pos ;
		return (ret_value);
	}
	else {/*nothing*/}
}
/*--------------------------------------------Software Interface Declaration-------------------------------*/

