/*
 * ECU_Layer.h
 *
 *  Created on: Sep 15, 2023
 *      Author: Ahmed Ashraf
 */

#ifndef INC_ECU_LAYER_H_
#define INC_ECU_LAYER_H_
//-----------------------------
//Includes
//-----------------------------

#include "Chr_Lcd.h"
#include "stm32f103c6_LQFP48.h"
#include "Keypad.h"
//-----------------------------
//initialization
//-----------------------------

Lcd_4bit_t Lcd_1 = {//port A
		.Lcd_RS.GPIO_PIN_Number = PIN0 ,
		.Lcd_RS.GPIO_MODE = MODE_OUTPUT_OD,
		.Lcd_RS.GPIO_OUTPUT_SPEED=OUTPUT_SPEED_10,
		.Lcd_EN.GPIO_PIN_Number = PIN1 ,
		.Lcd_EN.GPIO_MODE = MODE_OUTPUT_OD,
		.Lcd_EN.GPIO_OUTPUT_SPEED=OUTPUT_SPEED_10,
		.Lcd_DATA[0].GPIO_PIN_Number =PIN2,
		.Lcd_DATA[0].GPIO_MODE =MODE_OUTPUT_OD,
		.Lcd_DATA[0].GPIO_OUTPUT_SPEED=OUTPUT_SPEED_10,
		.Lcd_DATA[1].GPIO_PIN_Number =PIN3,
		.Lcd_DATA[1].GPIO_MODE =MODE_OUTPUT_OD,
		.Lcd_DATA[1].GPIO_OUTPUT_SPEED=OUTPUT_SPEED_10,
		.Lcd_DATA[2].GPIO_PIN_Number =PIN4,
		.Lcd_DATA[2].GPIO_MODE =MODE_OUTPUT_OD,
		.Lcd_DATA[2].GPIO_OUTPUT_SPEED=OUTPUT_SPEED_10,
		.Lcd_DATA[3].GPIO_PIN_Number =PIN5,
		.Lcd_DATA[3].GPIO_MODE =MODE_OUTPUT_OD,
		.Lcd_DATA[3].GPIO_OUTPUT_SPEED=OUTPUT_SPEED_10,
		.ports.Port[0]=GPIOA,
		.ports.Port[1]=GPIOA,
		.ports.Port[2]=GPIOA,
		.ports.Port[3]=GPIOA,
		.ports.Port[4]=GPIOA,
		.ports.Port[5]=GPIOA

};


Lcd_8bit_t Lcd_2 = {//port B
		.Lcd_RS.GPIO_PIN_Number = PIN0 ,
		.Lcd_RS.GPIO_MODE = MODE_OUTPUT_OD,
		.Lcd_RS.GPIO_OUTPUT_SPEED=OUTPUT_SPEED_10,
		.Lcd_EN.GPIO_PIN_Number = PIN1 ,
		.Lcd_EN.GPIO_MODE = MODE_OUTPUT_OD,
		.Lcd_EN.GPIO_OUTPUT_SPEED=OUTPUT_SPEED_10,
		.Lcd_DATA[0].GPIO_PIN_Number =PIN2,
		.Lcd_DATA[0].GPIO_MODE =MODE_OUTPUT_OD,
		.Lcd_DATA[0].GPIO_OUTPUT_SPEED=OUTPUT_SPEED_10,
		.Lcd_DATA[1].GPIO_PIN_Number =PIN3,
		.Lcd_DATA[1].GPIO_MODE =MODE_OUTPUT_OD,
		.Lcd_DATA[1].GPIO_OUTPUT_SPEED=OUTPUT_SPEED_10,
		.Lcd_DATA[2].GPIO_PIN_Number =PIN4,
		.Lcd_DATA[2].GPIO_MODE =MODE_OUTPUT_OD,
		.Lcd_DATA[2].GPIO_OUTPUT_SPEED=OUTPUT_SPEED_10,
		.Lcd_DATA[3].GPIO_PIN_Number =PIN5,
		.Lcd_DATA[3].GPIO_MODE =MODE_OUTPUT_OD,
		.Lcd_DATA[3].GPIO_OUTPUT_SPEED=OUTPUT_SPEED_10,
		.Lcd_DATA[4].GPIO_PIN_Number =PIN6,
		.Lcd_DATA[4].GPIO_MODE =MODE_OUTPUT_OD,
		.Lcd_DATA[4].GPIO_OUTPUT_SPEED=OUTPUT_SPEED_10,
		.Lcd_DATA[5].GPIO_PIN_Number =PIN7,
		.Lcd_DATA[5].GPIO_MODE =MODE_OUTPUT_OD,
		.Lcd_DATA[5].GPIO_OUTPUT_SPEED=OUTPUT_SPEED_10,
		.Lcd_DATA[6].GPIO_PIN_Number =PIN8,
		.Lcd_DATA[6].GPIO_MODE =MODE_OUTPUT_OD,
		.Lcd_DATA[6].GPIO_OUTPUT_SPEED=OUTPUT_SPEED_10,
		.Lcd_DATA[7].GPIO_PIN_Number =PIN9,
		.Lcd_DATA[7].GPIO_MODE =MODE_OUTPUT_OD,
		.Lcd_DATA[7].GPIO_OUTPUT_SPEED=OUTPUT_SPEED_10,
		.ports.Port[0]=GPIOB,
		.ports.Port[1]=GPIOB,
		.ports.Port[2]=GPIOB,
		.ports.Port[3]=GPIOB,
		.ports.Port[4]=GPIOB,
		.ports.Port[5]=GPIOB,
		.ports.Port[6]=GPIOB,
		.ports.Port[7]=GPIOB,
		.ports.Port[8]=GPIOB,
		.ports.Port[9]=GPIOB
};


keypad_t keypad_1 =
{
		.Keypad_row_pins[0].GPIO_PIN_Number =PIN6,
		.Keypad_row_pins[0].GPIO_MODE =MODE_OUTPUT_OD,
		.Keypad_row_pins[0].GPIO_OUTPUT_SPEED =OUTPUT_SPEED_10,
		.Keypad_row_pins[1].GPIO_PIN_Number =PIN7,
		.Keypad_row_pins[1].GPIO_MODE =MODE_OUTPUT_OD,
		.Keypad_row_pins[1].GPIO_OUTPUT_SPEED =OUTPUT_SPEED_10,
		.Keypad_row_pins[2].GPIO_PIN_Number =PIN8,
		.Keypad_row_pins[2].GPIO_MODE =MODE_OUTPUT_OD,
		.Keypad_row_pins[2].GPIO_OUTPUT_SPEED =OUTPUT_SPEED_10,
		.Keypad_row_pins[3].GPIO_PIN_Number =PIN9,
		.Keypad_row_pins[3].GPIO_MODE =MODE_OUTPUT_OD,
		.Keypad_row_pins[3].GPIO_OUTPUT_SPEED =OUTPUT_SPEED_10,
		.ports.row_pin_Port[0]=GPIOA ,
		.ports.row_pin_Port[1]=GPIOA ,
		.ports.row_pin_Port[2]=GPIOA ,
		.ports.row_pin_Port[3]=GPIOA ,


		.Keypad_column_pins[0].GPIO_PIN_Number =PIN10,
		.Keypad_column_pins[0].GPIO_MODE =MODE_INPUT_FLO,
		.Keypad_column_pins[1].GPIO_PIN_Number =PIN11,
		.Keypad_column_pins[1].GPIO_MODE =MODE_INPUT_FLO,
		.Keypad_column_pins[2].GPIO_PIN_Number =PIN12,
		.Keypad_column_pins[2].GPIO_MODE =MODE_INPUT_FLO,
		.Keypad_column_pins[3].GPIO_PIN_Number =PIN13,
		.Keypad_column_pins[3].GPIO_MODE =MODE_INPUT_FLO,
		.ports.column_pin_Port[0]=GPIOB ,
		.ports.column_pin_Port[1]=GPIOB ,
		.ports.column_pin_Port[2]=GPIOB ,
		.ports.column_pin_Port[3]=GPIOB



};









//-----------------------------
//Macros Configuration References
//-----------------------------

/*
* ===============================================
* APIs Supported by "ECU Layer"
* ===============================================
*/

void ECU_Layer_init(void);


#endif /* INC_ECU_LAYER_H_ */
