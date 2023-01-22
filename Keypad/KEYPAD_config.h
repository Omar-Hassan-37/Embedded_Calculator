/************************************************************************/
/************************************************************************/
/*******************        Author: Omar Hassan         *****************/
/*******************        Component: KEYPAD             ***************/
/*******************        Component: HAL             ******************/
/*******************        Version: 1.00               *****************/
/************************************************************************/
/************************************************************************/

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#define NO_KEY_PRESSED_VALUE	0xFF

#define KEYPAD_u8_PORT			DIO_u8_PORTC

#define KEYPAD_u8_ROW0			DIO_u8_PIN0
#define KEYPAD_u8_ROW1			DIO_u8_PIN1
#define KEYPAD_u8_ROW2			DIO_u8_PIN2
#define KEYPAD_u8_ROW3			DIO_u8_PIN3

#define KEYPAD_u8_COLUMN0		DIO_u8_PIN4
#define KEYPAD_u8_COLUMN1		DIO_u8_PIN5
#define KEYPAD_u8_COLUMN2		DIO_u8_PIN6
#define KEYPAD_u8_COLUMN3		DIO_u8_PIN7

#define KEYPAD_KEYS_ARR4x4		{ {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} }


#endif
