/*
 * Keypad.c
 *
 *  Created on: Sep 15, 2023
 *      Author: Ahmed Ashraf
 */


//-----------------------------
//Includes
//-----------------------------

#include "Keypad.h"

uint8_t keypad_buttons [Keypad_ROWS][Keypad_COLUMNS] =
{
		{'7','8','9','/'},
		{'4','5','6','*'},
		{'1','2','3','-'},
		{'#','0','=','+'}
};






void keypad_init(keypad_t *keypad)
{
	uint8_t row_counter =0 ,column_counter=0;

	for(row_counter=0;row_counter<Keypad_ROWS;row_counter++)
	{
		GPIO_init(keypad->ports.row_pin_Port[row_counter], &(keypad->Keypad_row_pins[row_counter]));
		GPIO_Write_Pin(keypad->ports.row_pin_Port[row_counter], keypad->Keypad_row_pins[row_counter].GPIO_PIN_Number,
						GPIO_status_SET);
	}


	for(column_counter=0;column_counter<Keypad_COLUMNS;column_counter++)
	{
		GPIO_init(keypad->ports.column_pin_Port[column_counter], &(keypad->Keypad_column_pins[column_counter]));
	}


}

uint8_t keypad_get_button(keypad_t *keypad)
{
	uint8_t row_counter =0 ,column_counter=0,counter=0;
	uint8_t ret_value =0;
	for(row_counter=0;row_counter<Keypad_ROWS;row_counter++)
	{
		for(counter=0;counter<Keypad_ROWS;counter++)
		{
			GPIO_Write_Pin(keypad->ports.row_pin_Port[counter], keypad->Keypad_row_pins[counter].GPIO_PIN_Number,
							GPIO_status_RESET);
		}

		GPIO_Write_Pin(keypad->ports.row_pin_Port[row_counter], keypad->Keypad_row_pins[row_counter].GPIO_PIN_Number,
						GPIO_status_SET);

		for(column_counter=0;column_counter<Keypad_COLUMNS;column_counter++)
		{
			ret_value = GPIO_Read_Pin(keypad->ports.column_pin_Port[column_counter],
						  keypad->Keypad_column_pins[column_counter].GPIO_PIN_Number );

			if(ret_value == GPIO_status_SET)
			{
				ret_value = keypad_buttons[row_counter][column_counter];
				return (ret_value);
			}

		}

	}

	return (ret_value);					//0
}


