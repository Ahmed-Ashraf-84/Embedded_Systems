/*
 * Keypad.h
 *
 *  Created on: Sep 15, 2023
 *      Author: Ahmed Ashraf
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_
//-----------------------------
//Includes
//-----------------------------
#include "stm32f103c6_GPIO_driver.h"

//-----------------------------
//Macros Configuration References
//-----------------------------

#define Keypad_ROWS      	 4
#define Keypad_COLUMNS       4


//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	GPIO_t *row_pin_Port[Keypad_ROWS];
	GPIO_t *column_pin_Port[Keypad_COLUMNS];

}keypad_PORTS_t;


typedef struct
{
	GPIO_PIN_config_t Keypad_row_pins[Keypad_ROWS];
	GPIO_PIN_config_t Keypad_column_pins[Keypad_COLUMNS];
	keypad_PORTS_t ports;

}keypad_t;

/*
* ===============================================
* APIs Supported by "ECU Keypad DRIVERS"
* ===============================================
*/

void keypad_init(keypad_t *keypad);

uint8_t keypad_get_button(keypad_t *keypad);



#endif /* INC_KEYPAD_H_ */
