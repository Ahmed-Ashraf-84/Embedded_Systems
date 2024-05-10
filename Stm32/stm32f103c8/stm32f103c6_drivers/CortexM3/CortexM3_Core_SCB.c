/**
 ******************************************************************************
 * @file           : CortexM3_Core_SCB.c
 * @author         : Ahmed Ashraf Mahgob Ahmed
 * @brief          : Contain the code to Control NVIC
 ******************************************************************************
**/
/*--------------------------------------------Includes Start----------------------------------*/
#include "CortexM3/CortexM3_Core_SCB.h"

/*--------------------------------------------Includes End----------------------------------*/

/*--------------------------------------------Macro Declaration----------------------------------*/
/*--------------------------------------------Macro Declaration----------------------------------*/

/*--------------------------------------------Macro Functions Declaration----------------------------------*/
/*--------------------------------------------Macro Functions Declaration----------------------------------*/

/*--------------------------------------------Data Type Declaration----------------------------------*/
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
void SBC_SetPriority_Group(GroupPriority_t priority)
{
	uint32_t register_value = 0;
	uint32_t priority_temp = (uint32_t)priority ;

	register_value = SCB->AIRCR ;
	register_value &= ~(SBC_AIRCR_PRIGROUP_Mask | SBC_AIRCR_VECTKEYSTAT_Mask);
	register_value |=   (priority_temp << SBC_AIRCR_PRIGROUP_Pos)	|
						(SBC_AIRCR_VECTKEYSTAT_Key << SBC_AIRCR_VECTKEYSTAT_Pos);
	SCB->AIRCR = register_value ;
}

/**
 * 	@brief			Get Priority Group
 *  @details		Reads Priority Group bits(PRIGROUP) in AIRCR register in system control block
 *  @return			Priority Group field in AIRCR register
 */
uint32_t SBC_GetPriority_Group(void)
{
	uint32_t ret_value = 0 ;
	ret_value = (uint32_t)SCB->AIRCR ;
	ret_value &= (SBC_AIRCR_PRIGROUP_Mask) ;
	ret_value >>= SBC_AIRCR_PRIGROUP_Pos ;

	return (ret_value) ;
}

/*--------------------------------------------Software Interface Declaration-------------------------------*/
