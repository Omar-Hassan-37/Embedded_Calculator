/************************************************************************/
/************************************************************************/
/*******************        Author: Omar Hassan         *****************/
/*******************        Component: KEYPAD             ***************/
/*******************        Component: HAL             ******************/
/*******************        Version: 1.00               *****************/
/************************************************************************/
/************************************************************************/

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#define KEYPAD_CALC_FIRST_OPERAND		0
#define KEYPAD_CALC_OPERATION			1
#define KEYPAD_CALC_SECOND_OPERAND		2
#define KEYPAD_CALC_NEW_OPERATION		3

#define KEYPAD_CALC_UP_BUTTON			2
#define KEYPAD_CALC_DOWN_BUTTON			3
#define KEYPAD_CALC_ENTER_BUTTON		4

#define KEYPAD_CALC_FIRST_DIGIT			0
#define KEYPAD_CALC_LAST_DIGIT			9
#define KEYPAD_CALC_FIRST_SIGN			0
#define KEYPAD_CALC_LAST_SIGN			3


u8  KEYPAD_u8GetPressedKey(void);


#endif
