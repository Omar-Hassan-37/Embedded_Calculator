/*
 * main.c
 *
 *  Created on: Dec 29, 2022
 *      Author: oh377
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PORT_interface.h"
#include "LCD_interface.h"
#include "KEYPAD_interface.h"

#include "util/delay.h"

void GLOBAL_voidSemiCalculator(void);
u8 GLOBAL_u8Calculate(u8 Copy_u8FirstOperand, u8 Copy_u8SecondOperand, u8 Copy_u8Operation, u8* Copy_u8Remainder);

void main(void)
{
	PORT_voidInit();
	LCD_voidInit();

	u8 Local_u8KeynumberNumber;
	u8 arr[2] = {0,2};
	while(1)
	{
//		Busy waiting until a key is pressed
		GLOBAL_voidSemiCalculator();
		_delay_ms(1000);
		LCD_voidSendCommand(LCD_CLEAR);
	}
}

void GLOBAL_voidSemiCalculator(void)
{
	u8 Local_u8CursorArrow [8] = {
						0b00000100,
						0b00001110,
						0b00010101,
						0b00000100,
						0b00000000,
						0b00000000,
						0b00000000
	};
	u8 Local_u8FirstOperand [10] = {0,1,2,3,4,5,6,7,8,9};
	u8 Local_u8Operation [5] = {'+','-','*','/'};
	u8 Local_u8SecondOperand [10] = {0,1,2,3,4,5,6,7,8,9};
	u8 Local_u8PressedKey, Local_u8FirstIterator = 0, Local_u8SecIterator = 0, Local_u8ThirdIterator = 0;
	u8 Local_u8CalcMode = KEYPAD_CALC_FIRST_OPERAND, Local_u8Result;

	u8 Local_u8Remainder = 0;

	LCD_voidSendData('0' + Local_u8FirstOperand[Local_u8FirstIterator]);
	LCD_voidSendData(Local_u8Operation[Local_u8SecIterator]);
	LCD_voidSendData('0' + Local_u8SecondOperand[Local_u8ThirdIterator]);
	LCD_voidWriteSpecialCharacter(Local_u8CursorArrow,1, LCD_u8_SECOND_LINE, LCD_u8_FIRST_COLUMN);

	while(1)
	{

		do
		{
			Local_u8PressedKey = KEYPAD_u8GetPressedKey();
		}while(0xFF == Local_u8PressedKey);

		if(0xFF != Local_u8PressedKey)
		{
			switch(Local_u8CalcMode)
			{
				case KEYPAD_CALC_FIRST_OPERAND:
				{
					switch(Local_u8PressedKey)
					{
						case KEYPAD_CALC_UP_BUTTON:
						{
							if(KEYPAD_CALC_LAST_DIGIT != Local_u8FirstIterator)	{Local_u8FirstIterator++;}
							LCD_voidGotoXY(LCD_u8_FIRST_LINE, LCD_u8_FIRST_COLUMN);
							LCD_voidSendData('0' + Local_u8FirstOperand[Local_u8FirstIterator]);
							break;
						}
						case KEYPAD_CALC_DOWN_BUTTON:
						{
							if(KEYPAD_CALC_FIRST_DIGIT != Local_u8FirstIterator)	{Local_u8FirstIterator--;}
							LCD_voidGotoXY(LCD_u8_FIRST_LINE, LCD_u8_FIRST_COLUMN);
							LCD_voidSendData(' 0' + Local_u8FirstOperand[Local_u8FirstIterator]);
							break;
						}
						case KEYPAD_CALC_ENTER_BUTTON:
						{
							Local_u8CalcMode++;
							LCD_voidGotoXY(LCD_u8_SECOND_LINE, LCD_u8_FIRST_COLUMN);
							LCD_voidSendData(' ');
							LCD_voidWriteSpecialCharacter(Local_u8CursorArrow,1, LCD_u8_SECOND_LINE, LCD_u8_SECOND_COLUMN);
							break;
						}
					}
					break;
				}
				case KEYPAD_CALC_OPERATION:
				{
					switch(Local_u8PressedKey)
					{
						case KEYPAD_CALC_UP_BUTTON:
						{
							if(KEYPAD_CALC_LAST_SIGN != Local_u8SecIterator)	{Local_u8SecIterator++;}
							LCD_voidGotoXY(LCD_u8_FIRST_LINE, LCD_u8_SECOND_COLUMN);
							LCD_voidSendData(Local_u8Operation[Local_u8SecIterator]);
							break;
						}
						case KEYPAD_CALC_DOWN_BUTTON:
						{
							if(KEYPAD_CALC_FIRST_SIGN != Local_u8SecIterator)	{Local_u8SecIterator--;}
							LCD_voidGotoXY(LCD_u8_FIRST_LINE, LCD_u8_SECOND_COLUMN);
							LCD_voidSendData(Local_u8Operation[Local_u8SecIterator]);
							break;
						}
						case KEYPAD_CALC_ENTER_BUTTON:
						{
							Local_u8CalcMode++;
							LCD_voidGotoXY(LCD_u8_SECOND_LINE, LCD_u8_SECOND_COLUMN);
							LCD_voidSendData(' ');
							LCD_voidWriteSpecialCharacter(Local_u8CursorArrow,1, LCD_u8_SECOND_LINE, LCD_u8_THIRD_COLUMN);
							break;
						}
					}
					break;
				}
				case KEYPAD_CALC_SECOND_OPERAND:
				{
					switch(Local_u8PressedKey)
					{
						case KEYPAD_CALC_UP_BUTTON:
						{
							if((KEYPAD_CALC_LAST_DIGIT != Local_u8ThirdIterator) && (Local_u8SecondOperand[Local_u8ThirdIterator] < Local_u8FirstOperand[Local_u8FirstIterator]))
							{
								Local_u8ThirdIterator++;
							}
							LCD_voidGotoXY(LCD_u8_FIRST_LINE, LCD_u8_THIRD_COLUMN);
							LCD_voidSendData('0' + Local_u8SecondOperand[Local_u8ThirdIterator]);
							break;
						}
						case KEYPAD_CALC_DOWN_BUTTON:
						{
							if(KEYPAD_CALC_FIRST_DIGIT != Local_u8ThirdIterator)	{Local_u8ThirdIterator--;}
							LCD_voidGotoXY(LCD_u8_FIRST_LINE, LCD_u8_THIRD_COLUMN);
							LCD_voidSendData('0' + Local_u8SecondOperand[Local_u8ThirdIterator]);
							break;
						}
						case KEYPAD_CALC_ENTER_BUTTON:
						{
							Local_u8CalcMode++;
							LCD_voidGotoXY(LCD_u8_SECOND_LINE, LCD_u8_THIRD_COLUMN);
							LCD_voidSendData(' ');
							LCD_voidGotoXY(LCD_u8_FIRST_LINE, LCD_u8_FOURTH_COLUMN);
							LCD_voidSendData('=');
							Local_u8Result = GLOBAL_u8Calculate(Local_u8FirstOperand[Local_u8FirstIterator],Local_u8SecondOperand[Local_u8ThirdIterator], Local_u8Operation[Local_u8SecIterator], &Local_u8Remainder);
							LCD_voidWriteNumber(Local_u8Result);
//							if(Local_u8Remainder != 0)
//							{
//								LCD_voidSendData('.');
//								LCD_voidWriteNumber(Local_u8Remainder);
//							}
							LCD_voidWriteSpecialCharacter(Local_u8CursorArrow,1, LCD_u8_SECOND_LINE, LCD_u8_FIFTH_COLUMN);
							break;
						}
					}
					break;
				}
				case KEYPAD_CALC_NEW_OPERATION:
				{
					switch(Local_u8PressedKey)
					{
						case KEYPAD_CALC_ENTER_BUTTON:
						{
							Local_u8CalcMode = 0;
							Local_u8FirstIterator = 0;
							Local_u8SecIterator = 0;
							Local_u8ThirdIterator = 0;

							LCD_voidSendCommand(LCD_CLEAR);

							LCD_voidSendData('0' + Local_u8FirstOperand[Local_u8FirstIterator]);
							LCD_voidSendData(Local_u8Operation[Local_u8SecIterator]);
							LCD_voidSendData('0' + Local_u8SecondOperand[Local_u8ThirdIterator]);
							LCD_voidWriteSpecialCharacter(Local_u8CursorArrow,1, LCD_u8_SECOND_LINE, LCD_u8_FIRST_COLUMN);
							break;
						}
					}
					break;
				}
			}
		}
	}
}


u8 GLOBAL_u8Calculate(u8 Copy_u8FirstOperand, u8 Copy_u8SecondOperand, u8 Copy_u8Operation, u8* Copy_u8Remainder)
{
	switch(Copy_u8Operation)
	{
		case MATH_PLUS:	return (Copy_u8FirstOperand + Copy_u8SecondOperand);
		case MATH_MINUS: return (Copy_u8FirstOperand - Copy_u8SecondOperand);
		case MATH_MULTIPLY: return (Copy_u8FirstOperand * Copy_u8SecondOperand);
		case MATH_DIVIDE:
		{
//			if(Copy_u8FirstOperand % Copy_u8SecondOperand != 0)
//			{
//				*Copy_u8Remainder = Copy_u8FirstOperand % Copy_u8SecondOperand;
//			}
			return (Copy_u8FirstOperand / Copy_u8SecondOperand);
		}
		default: return 0;
	}
}
