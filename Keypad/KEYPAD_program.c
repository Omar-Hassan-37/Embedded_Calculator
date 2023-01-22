/************************************************************************/
/************************************************************************/
/*******************        Author: Omar Hassan         *****************/
/*******************        Component: KEYPAD             ***************/
/*******************        Component: HAL             ******************/
/*******************        Version: 1.00               *****************/
/************************************************************************/
/************************************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "KEYPAD_config.h"
#include "KEYPAD_interface.h"
#include "KEYPAD_private.h"

u8 KEYPAD_u8GetPressedKey(void)
{
	u8 Local_u8PressedKey= NO_KEY_PRESSED_VALUE;
	u8 Local_u8ColumnIndex, Local_u8RowIndex, Local_u8PinState;

	u8 Local_u8KepadArr[ROWS_NUMBER][COLUMNS_NUMBER]= KEYPAD_KEYS_ARR4x4;

	u8 Local_u8RowsPinsArr[4]= {KEYPAD_u8_ROW0, KEYPAD_u8_ROW1,KEYPAD_u8_ROW2,KEYPAD_u8_ROW3};
	u8 Local_u8ColumnsPinsArr[4]= {KEYPAD_u8_COLUMN0,KEYPAD_u8_COLUMN1,KEYPAD_u8_COLUMN2,KEYPAD_u8_COLUMN3};

	for(Local_u8ColumnIndex=0; Local_u8ColumnIndex<COLUMNS_NUMBER; Local_u8ColumnIndex++)
	{
		/*Activate the current column*/
		DIO_u8SetPinValue(KEYPAD_u8_PORT, Local_u8ColumnsPinsArr[Local_u8ColumnIndex], DIO_u8_PIN_LOW);

		for(Local_u8RowIndex=0; Local_u8RowIndex<ROWS_NUMBER; Local_u8RowIndex++)
		{
			/*Read the current row*/
			DIO_u8GetPinValue(KEYPAD_u8_PORT,Local_u8RowsPinsArr[Local_u8RowIndex], &Local_u8PinState);

			/*Check if the key is pressed*/
			if(DIO_u8_PIN_LOW == Local_u8PinState )
			{
				Local_u8PressedKey= Local_u8KepadArr[Local_u8RowIndex][Local_u8ColumnIndex];

				/*Busy waiting (polling) until the key is released*/
				while(DIO_u8_PIN_LOW == Local_u8PinState)
				{
					DIO_u8GetPinValue(KEYPAD_u8_PORT,Local_u8RowsPinsArr[Local_u8RowIndex], &Local_u8PinState);
				}
				return Local_u8PressedKey;
			}
		}
			/*Deactivate the current column*/
			DIO_u8SetPinValue(KEYPAD_u8_PORT, Local_u8ColumnsPinsArr[Local_u8ColumnIndex], DIO_u8_PIN_HIGH);
	}
	return Local_u8PressedKey;
}

