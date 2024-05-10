/*
 * Chr_Lcd.h
 *
 *  Created on: Sep 15, 2023
 *      Author: Ahmed Ashraf
 */

#ifndef INC_CHR_LCD_H_
#define INC_CHR_LCD_H_

//-----------------------------
//Includes
//-----------------------------
#include "stm32f103c6_GPIO_driver.h"
//#include <stdint.h>
//#include "stdlib.h"
//-----------------------------
//User type definitions (structures)
//-----------------------------
typedef struct
{
	GPIO_t *Port[16];

}PORTS_t;

typedef struct
{
	GPIO_PIN_config_t Lcd_RS;
	GPIO_PIN_config_t Lcd_EN;
	GPIO_PIN_config_t Lcd_RW;
	GPIO_PIN_config_t Lcd_DATA [4];
	PORTS_t           ports;
}Lcd_4bit_t;

typedef struct
{
	GPIO_PIN_config_t Lcd_RS;
	GPIO_PIN_config_t Lcd_EN;
	GPIO_PIN_config_t Lcd_RW;
	GPIO_PIN_config_t Lcd_DATA [8];
	PORTS_t           ports;
}Lcd_8bit_t;




//-----------------------------
//Macros Configuration References
//-----------------------------

#define Lcd_8bit_mode_2Lines_8row  					0x38
#define Lcd_4bit_mode_2Lines_8row  					0x28
#define Lcd_8bit_mode_2Lines_11row  				0x3C
#define Lcd_4bit_mode_2Lines_11row  				0x2C
#define Lcd_Clear_display  							0x01
#define Lcd_Cursor_Home  							0x02
#define Lcd_Entry_mode_increment  					0x06
#define Lcd_display_ON_under_line_Cursor_ON 		0x0E
#define Lcd_display_shift_Right  					0x1C
#define Lcd_display_shift_Left  					0x18
#define Lcd_DDRAM  									0x80
#define Lcd_CGRAM  									0x40
#define Lcd_8bit_mode_2Lines  						0x38
#define Lcd_8bit_mode_2Lines  						0x38

#define Row1  										1
#define Row2  										2
#define Row3  										3
#define Row4  										4

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic variable:
//-*-*-*-*-*-*-*-*-*-*-*



/*
* ===============================================
* APIs Supported by "ECU Chr_LCD DRIVERS"
* ===============================================
*/
void Lcd_4bit_init(Lcd_4bit_t * LCD );
void Lcd_4bit_command(Lcd_4bit_t * LCD ,uint8_t command);
void Lcd_4bit_send_chr(Lcd_4bit_t * LCD ,uint8_t data);
void Lcd_4bit_send_chr_pos(Lcd_4bit_t * LCD ,uint8_t row,uint8_t column,uint8_t data);
void Lcd_4bit_send_str(Lcd_4bit_t * LCD ,uint8_t *str);
void Lcd_4bit_send_str_pos(Lcd_4bit_t * LCD ,uint8_t row,uint8_t column,uint8_t *str);
void Lcd_4bit_send_custom_chr(Lcd_4bit_t * LCD ,uint8_t row,uint8_t column,uint8_t chr[],uint8_t memory_pos);


void Lcd_8bit_init(Lcd_8bit_t * LCD );
void Lcd_8bit_command(Lcd_8bit_t * LCD ,uint8_t command);
void Lcd_8bit_send_chr(Lcd_8bit_t * LCD ,uint8_t data);
void Lcd_8bit_send_chr_pos(Lcd_8bit_t * LCD ,uint8_t row,uint8_t column,uint8_t data);
void Lcd_8bit_send_str(Lcd_8bit_t * LCD ,uint8_t *str);
void Lcd_8bit_send_str_pos(Lcd_8bit_t * LCD ,uint8_t row,uint8_t column,uint8_t *str);
void Lcd_8bit_send_custom_chr(Lcd_8bit_t * LCD ,uint8_t row,uint8_t column,uint8_t chr[],uint8_t memory_pos);

#endif /* INC_CHR_LCD_H_ */
