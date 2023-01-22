#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"

#include "LCD_config.h"
#include "LCD_interface.h"
#include "LCD_private.h"

void LCD_voidSendCommand(u8 Copy_u8Command)
{
    // Set RW pin to write
    DIO_u8SetPinValue(LCD_u8_CTRL_PORT, LCD_u8_RW_PIN, DIO_u8_PIN_LOW);

    // Set Rs pin to command
    DIO_u8SetPinValue(LCD_u8_CTRL_PORT, LCD_u8_RS_PIN, DIO_u8_PIN_LOW);

//    Send the command to the LCD
    DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Command);

//    Enable pulse
    DIO_u8SetPinValue(LCD_u8_CTRL_PORT, LCD_u8_E_PIN, DIO_u8_PIN_HIGH);

    _delay_ms(2);

//    Disable pulse
    DIO_u8SetPinValue(LCD_u8_CTRL_PORT, LCD_u8_E_PIN, DIO_u8_PIN_LOW);
}

void LCD_voidSendData(u8 Copy_u8Data)
{
	// Set RW pin to write
	    DIO_u8SetPinValue(LCD_u8_CTRL_PORT, LCD_u8_RW_PIN, DIO_u8_PIN_LOW);

	    // Set Rs pin to Data
	    DIO_u8SetPinValue(LCD_u8_CTRL_PORT, LCD_u8_RS_PIN, DIO_u8_PIN_HIGH);

	//    Send the Data to the LCD
	    DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Data);

	//    Enable pulse
	    DIO_u8SetPinValue(LCD_u8_CTRL_PORT, LCD_u8_E_PIN, DIO_u8_PIN_HIGH);

	    _delay_ms(2);

	//    Disable pulse
	    DIO_u8SetPinValue(LCD_u8_CTRL_PORT, LCD_u8_E_PIN, DIO_u8_PIN_LOW);
}

void LCD_voidInit(void)
{
//#if	LCD_MODE == FOUR_BIT
//	//	wait for more than 30ms after power up
//		_delay_ms(40);
//
//	//	function set command
//	//	* 1- 1 lines
//	//	* 2- font = 5*11
//		LCD_voidSendCommand(0b00100000);
//		LCD_voidSendCommand(0b00100000);
//		LCD_voidSendCommand(0b10000000);
//
//	//	wait for more than 39ms
//		_delay_ms(1);
//
//	//	Display on off control command
//	//	1- Display enable
//	//	2- cursor on
//	//	3- blink cursor off
//		LCD_voidSendCommand(0b00000000);
//		LCD_voidSendCommand(0b11000000);
//
//	//	wait for more than 39ms
//		_delay_ms(1);
//
//	//	LCD clear
//		LCD_voidSendCommand(0b00000000);
//		LCD_voidSendCommand(0b00010000);
//
//	//	Delay more than 1.53 ms
//		_delay_ms(2);
//
//#elif	LCD_MODE == EIGHT_BIT
	//	wait for more than 30ms after power up
		_delay_ms(40);

	//	function set command
	//	* 1- 2 lines
	//	* 2- font = 5*7
		LCD_voidSendCommand(0b00111000);

	//	wait for more than 39ms
		_delay_ms(1);

	//	Display on off control command
	//	1- Display enable
	//	2- cursor off
	//	3- blink cursor off
		LCD_voidSendCommand(0b00001100);

	//	wait for more than 39ms
		_delay_ms(1);

	//	LCD clear
		LCD_voidSendCommand(0b00000001);

	//	Delay more than 1.53 ms
		_delay_ms(2);
//#endif

}

void LCD_voidWriteString(char const* Copy_pchString)
{
	while(*Copy_pchString != '\0')
	{
		LCD_voidSendData(*Copy_pchString);
		Copy_pchString++;
	}
}

void LCD_voidWriteNumber(u32 Copy_u32Number)
{
	u8 num_to_char_array[100], iterator = 0;
	if(Copy_u32Number == 0)	{LCD_voidSendData('0');}
	while(Copy_u32Number != 0)
	{
		num_to_char_array[iterator] = (u8)(Copy_u32Number % 10);
		Copy_u32Number /= 10;
		iterator++;
	}
	for(;iterator > 0; iterator--)
	{
		LCD_voidSendData('0' + (num_to_char_array[iterator-1]));
	}
}

//void LCD_voidWriteNumber(u32 Copy_u32Number)
//{
//	u32 Local_u32Reserved = 1;
//	while(Copy_u32Number)
//	{
//		Local_u32Reserved = Local_u32Reserved * 10 + Copy_u32Number % 10;
//		Copy_u32Number /= 10;
//	}
//
//	do
//	{
//		LCD_voidSendData((Local_u32Reserved % 10) + '0');
//		Local_u32Reserved /= 10;
//	}
//	while(Local_u32Reserved != 1);
//}

void LCD_voidGotoXY(u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	u8 Local_u8Address;

//	Adresses start with address 0
	if(Copy_u8XPos == LCD_u8_FIRST_LINE)
	{
		Local_u8Address = Copy_u8YPos;
	}

//	Adresses start with address 0x40
	else if(Copy_u8XPos == LCD_u8_SECOND_LINE)
	{
		Local_u8Address = 0x40 + Copy_u8YPos;
	}

//	Setting the 8th bit 1 for the command (Datasheet)
	SET_BIT(Local_u8Address, 7);
//	Sending the SET DDRAM address command
	LCD_voidSendCommand(Local_u8Address);
}

void LCD_voidWriteSpecialCharacter(u8* Copy_u8Pattern, u8 Copy_u8PatternNumber, u8 Copy_XPos, u8 Copy_YPos)
{
	u8 Local_u8Address, Local_u8PatternCounter;

//	1- Calculate the required address of CGRAM
	Local_u8Address = Copy_u8PatternNumber * 8;

//	2- Set CGRAM Address the 7th bit 1 for the command (Datasheet)
	SET_BIT(Local_u8Address, 6);
	LCD_voidSendCommand(Local_u8Address);

//	3- Write the required pattern inside the CGRAM
	for(Local_u8PatternCounter = 0; Local_u8PatternCounter < 8; Local_u8PatternCounter++)
	{
		LCD_voidSendData(Copy_u8Pattern[Local_u8PatternCounter]);
	}

//	4- Shift the address counter to the DDRAM
	LCD_voidGotoXY(Copy_XPos, Copy_YPos);

//	5- Display the CGRAM pattern on the LCD
	LCD_voidSendData(Copy_u8PatternNumber);
}

