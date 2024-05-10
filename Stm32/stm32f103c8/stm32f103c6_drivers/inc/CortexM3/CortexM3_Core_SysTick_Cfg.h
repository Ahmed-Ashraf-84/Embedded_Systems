/**
 ******************************************************************************
 * @file           : CortexM3_Core_SysTick_Cfg.h
 * @author         : Ahmed Ashraf Mahgob Ahmed
 * @brief          : Contain the code to Control system timer
 ******************************************************************************
**/
#ifndef INC_CORTEXM3_CORTEXM3_CORE_SYSTICK_CFG_H_
#define INC_CORTEXM3_CORTEXM3_CORE_SYSTICK_CFG_H_
/*--------------------------------------------Includes Start----------------------------------*/

/*--------------------------------------------Includes End----------------------------------*/

/*--------------------------------------------Macro Declaration----------------------------------*/






#define SET_BIT(REG,BIT)	(REG |= BIT )
#define CLEAR_BIT(REG,BIT)	(REG &= ~(BIT))
#define TOGGLE_BIT(REG,BIT)	(REG ^= BIT )
#define READ_BIT(REG,BIT)	(REG & BIT )

#define STK_AHB_CLK_DIV_1		1UL
#define STK_AHB_CLK_DIV_8		0UL
#define STK_AHB_CLK_SOURCE		(STK_AHB_CLK_DIV_8)

/*--------------------------------------------Macro Declaration----------------------------------*/

/*--------------------------------------------Macro Functions Declaration----------------------------------*/
/*--------------------------------------------Macro Functions Declaration----------------------------------*/

/*--------------------------------------------Data Type Declaration----------------------------------*/
/*--------------------------------------------Data Type Declaration----------------------------------*/


#endif /* INC_CORTEXM3_CORTEXM3_CORE_SYSTICK_CFG_H_ */
