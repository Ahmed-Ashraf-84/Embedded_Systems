/*
 * Chr_Lcd.c
 *
 *  Created on: Sep 15, 2023
 *      Author: Ahmed Ashraf
 */

//-----------------------------
//Includes
//-----------------------------

#include "Chr_Lcd.h"


uint8_t customChar1[] = {
  0B00011,
  0B00111,
  0B01111,
  0B01111,
  0B01111,
  0B00111,
  0B00011,
  0B00001
};

uint8_t customChar2[] = {
  0B11000,
  0B11100,
  0B11110,
  0B11110,
  0B11110,
  0B11100,
  0B11000,
  0B10000
};

















static void Lcd_4bit_set_cursor(Lcd_4bit_t * LCD , uint8_t row , uint8_t column );
static void Lcd_8bit_set_cursor(Lcd_8bit_t * LCD , uint8_t row , uint8_t column );
static void Lcd_send_4bit_Enable(Lcd_4bit_t * LCD );
static void Lcd_send_8bit_Enable(Lcd_8bit_t * LCD );
static void Lcd_send_4bit(Lcd_4bit_t * LCD ,uint8_t command);
static void delay(unsigned int time);



void Lcd_4bit_init(Lcd_4bit_t * LCD )
{
	uint8_t pin_counter=0;
	GPIO_init(LCD->ports.Port[0], &(LCD->Lcd_RS));
	GPIO_init(LCD->ports.Port[1], &(LCD->Lcd_EN));
	for(pin_counter=0;pin_counter<4;pin_counter++)
	{
		GPIO_init(LCD->ports.Port[pin_counter+2], &(LCD->Lcd_DATA[pin_counter]));
	}
	delay(5);
	//Lcd_4bit_command(LCD , Lcd_8bit_mode_2Lines_8row);
	delay(5);
	Lcd_4bit_command(LCD , Lcd_8bit_mode_2Lines_8row);
	delay(3);
	Lcd_4bit_command(LCD , Lcd_8bit_mode_2Lines_8row);
	delay(2);
	Lcd_4bit_command(LCD , Lcd_8bit_mode_2Lines_8row);


	Lcd_4bit_command(LCD , Lcd_Clear_display);
	Lcd_4bit_command(LCD , Lcd_Cursor_Home);
	Lcd_4bit_command(LCD , Lcd_Entry_mode_increment);
	Lcd_4bit_command(LCD , Lcd_display_ON_under_line_Cursor_ON);
	Lcd_4bit_command(LCD , Lcd_4bit_mode_2Lines_8row);

}
void Lcd_4bit_command(Lcd_4bit_t * LCD ,uint8_t command)
{
	GPIO_Write_Pin(LCD->ports.Port[0], LCD->Lcd_RS.GPIO_PIN_Number, GPIO_status_RESET);
	Lcd_send_4bit(LCD,(command >> 4));
	Lcd_send_4bit_Enable(LCD);
	Lcd_send_4bit(LCD,(command));
	Lcd_send_4bit_Enable(LCD);
}
void Lcd_4bit_send_chr(Lcd_4bit_t * LCD ,uint8_t data)
{
	GPIO_Write_Pin(LCD->ports.Port[0], LCD->Lcd_RS.GPIO_PIN_Number, GPIO_status_SET);
	Lcd_send_4bit(LCD,(data >> 4));
	Lcd_send_4bit_Enable(LCD);
	Lcd_send_4bit(LCD,(data));
	Lcd_send_4bit_Enable(LCD);
}
void Lcd_4bit_send_chr_pos(Lcd_4bit_t * LCD ,uint8_t row,uint8_t column,uint8_t data)
{
	Lcd_4bit_set_cursor(LCD , row , column );
	Lcd_4bit_send_chr(LCD,data);
}
void Lcd_4bit_send_str(Lcd_4bit_t * LCD ,uint8_t *str)
{
	while(*str)
	{
		Lcd_4bit_send_chr(LCD,*str++);
	}
}
void Lcd_4bit_send_str_pos(Lcd_4bit_t * LCD ,uint8_t row,uint8_t column,uint8_t *str)
{
	Lcd_4bit_set_cursor(LCD , row , column );

	while(*str)
	{
		Lcd_4bit_send_chr(LCD,*str++);
	}
}
void Lcd_4bit_send_custom_chr(Lcd_4bit_t * LCD ,uint8_t row,uint8_t column,uint8_t chr[],uint8_t memory_pos)
{
	uint8_t counter=0;

	Lcd_4bit_command(LCD,(Lcd_CGRAM+memory_pos*8));

	for(counter=0;counter<8;counter++)
	{
		Lcd_4bit_send_chr(LCD,chr[counter]);

	}

	Lcd_4bit_send_chr_pos(LCD,row,column,memory_pos);
}


void Lcd_8bit_init(Lcd_8bit_t * LCD )
{
	uint8_t pin_counter=0;
	GPIO_init(LCD->ports.Port[0], &(LCD->Lcd_RS));
	GPIO_init(LCD->ports.Port[1], &(LCD->Lcd_EN));
	for(pin_counter=0;pin_counter<8;pin_counter++)
	{
		GPIO_init(LCD->ports.Port[pin_counter+2], &(LCD->Lcd_DATA[pin_counter]));//2-->5
	}

	delay(5);
	Lcd_8bit_command(LCD , Lcd_8bit_mode_2Lines_8row);
	delay(3);
	Lcd_8bit_command(LCD , Lcd_8bit_mode_2Lines_8row);
	delay(2);
	Lcd_8bit_command(LCD , Lcd_8bit_mode_2Lines_8row);

	Lcd_8bit_command(LCD , Lcd_8bit_mode_2Lines_8row);
	Lcd_8bit_command(LCD , Lcd_Clear_display);
	Lcd_8bit_command(LCD , Lcd_Cursor_Home);
	Lcd_8bit_command(LCD , Lcd_Entry_mode_increment);
	Lcd_8bit_command(LCD , Lcd_display_ON_under_line_Cursor_ON);

}
void Lcd_8bit_command(Lcd_8bit_t * LCD ,uint8_t command)
{
	uint8_t pin_counter=0;
	GPIO_Write_Pin(LCD->ports.Port[0], LCD->Lcd_RS.GPIO_PIN_Number, GPIO_status_RESET);

	for(pin_counter=0;pin_counter<8;pin_counter++)
	{
		GPIO_Write_Pin(LCD->ports.Port[pin_counter+2], LCD->Lcd_DATA[pin_counter].GPIO_PIN_Number, (command >> pin_counter)&(0x01));
	}

	Lcd_send_8bit_Enable(LCD);
}
void Lcd_8bit_send_chr(Lcd_8bit_t * LCD ,uint8_t data)
{
	uint8_t pin_counter=0;
	GPIO_Write_Pin(LCD->ports.Port[0], LCD->Lcd_RS.GPIO_PIN_Number, GPIO_status_SET);

	for(pin_counter=0;pin_counter<8;pin_counter++)
	{
		GPIO_Write_Pin(LCD->ports.Port[pin_counter+2], LCD->Lcd_DATA[pin_counter].GPIO_PIN_Number, (data >> pin_counter)&(0x01));
	}

	Lcd_send_8bit_Enable(LCD);
}
void Lcd_8bit_send_chr_pos(Lcd_8bit_t * LCD ,uint8_t row,uint8_t column,uint8_t data)
{

	Lcd_8bit_set_cursor(LCD , row , column );
	Lcd_8bit_send_chr(LCD,data);

}
void Lcd_8bit_send_str(Lcd_8bit_t * LCD ,uint8_t *str)
{
	while(*str)
	{
		Lcd_8bit_send_chr(LCD,*str++);
	}

}
void Lcd_8bit_send_str_pos(Lcd_8bit_t * LCD ,uint8_t row,uint8_t column,uint8_t *str)
{

	Lcd_8bit_set_cursor(LCD , row , column );

	while(*str)
	{
		Lcd_8bit_send_chr(LCD,*str++);
	}
}
void Lcd_8bit_send_custom_chr(Lcd_8bit_t * LCD ,uint8_t row,uint8_t column,uint8_t chr[],uint8_t memory_pos)
{
	uint8_t counter=0;

	Lcd_8bit_command(LCD,(Lcd_CGRAM+memory_pos*8));

	for(counter=0;counter<8;counter++)
	{
		Lcd_8bit_send_chr(LCD,chr[counter]);

	}

	Lcd_8bit_send_chr_pos(LCD,row,column,memory_pos);
}


static void Lcd_send_4bit(Lcd_4bit_t * LCD ,uint8_t command_data)
{
	uint8_t pin_counter=0;
	for(pin_counter=0;pin_counter<4;pin_counter++)
	{
	GPIO_Write_Pin(LCD->ports.Port[pin_counter+2], LCD->Lcd_DATA[pin_counter].GPIO_PIN_Number, (command_data >> pin_counter)&(0x01));
	}
}


static void Lcd_send_4bit_Enable(Lcd_4bit_t * LCD )
{
	GPIO_Write_Pin(LCD->ports.Port[1], LCD->Lcd_EN.GPIO_PIN_Number, GPIO_status_SET);
	delay(1);
	GPIO_Write_Pin(LCD->ports.Port[1], LCD->Lcd_EN.GPIO_PIN_Number, GPIO_status_RESET);
}

static void Lcd_send_8bit_Enable(Lcd_8bit_t * LCD )
{
	GPIO_Write_Pin(LCD->ports.Port[1], LCD->Lcd_EN.GPIO_PIN_Number, GPIO_status_SET);
	delay(1);
	GPIO_Write_Pin(LCD->ports.Port[1], LCD->Lcd_EN.GPIO_PIN_Number, GPIO_status_RESET);
}

static void delay(unsigned int time)
{
	unsigned int i=0, j=0;

	for(i=0;i<time;i++)
		for(j=0;j<255;j++);

}


static void Lcd_8bit_set_cursor(Lcd_8bit_t * LCD , uint8_t row , uint8_t column )
{
	column--;
	switch(row)
	{
	case Row1:
		Lcd_8bit_command(LCD,(0x80+column));
		break;
	case Row2:
		Lcd_8bit_command(LCD,(0xC0+column));
		break;
	case Row3:
		Lcd_8bit_command(LCD,(0x94+column));
		break;
	case Row4:
		Lcd_8bit_command(LCD,(0xD4+column));
		break;


	}

}

static void Lcd_4bit_set_cursor(Lcd_4bit_t * LCD , uint8_t row , uint8_t column )
{
	column--;
	switch(row)
	{
	case Row1:
		Lcd_4bit_command(LCD,(0x80+column));
		break;
	case Row2:
		Lcd_4bit_command(LCD,(0xC0+column));
		break;
	case Row3:
		Lcd_4bit_command(LCD,(0x94+column));
		break;
	case Row4:
		Lcd_4bit_command(LCD,(0xD4+column));
		break;


	}

}

