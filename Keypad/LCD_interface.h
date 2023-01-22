#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define LCD_CLEAR				1

#define LCD_u8_FIRST_LINE			0
#define LCD_u8_SECOND_LINE			1
#define LCD_u8_FIRST_COLUMN			0
#define LCD_u8_SECOND_COLUMN		1
#define LCD_u8_THIRD_COLUMN			2
#define LCD_u8_FOURTH_COLUMN		3
#define LCD_u8_FIFTH_COLUMN			4
#define LCD_u8_SIXTH_COLUMN			5
#define LCD_u8_SEVENTH_COLUMN		6
#define LCD_u8_EIGHTH_COLUMN		7
#define LCD_u8_NINTH_COLUMN			8
#define LCD_u8_TENTH_COLUMN			9
#define LCD_u8_ELEVENTH_COLUMN		10
#define LCD_u8_TWELFTH_COLUMN		11
#define LCD_u8_THIRTEENTH_COLUMN	12
#define LCD_u8_FOURTEENTH_COLUMN	13
#define LCD_u8_FIFTEENTH_COLUMN		14
#define LCD_u8_SIXTEENTH_COLUMN		15

void LCD_voidSendCommand(u8 Copy_u8Command);

void LCD_voidSendData(u8 Copy_u8Data);

void LCD_voidInit(void);

void LCD_voidWriteString(char const* Copy_pchString);

void LCD_voidWriteNumber(u32 Copy_u16Number);

void LCD_voidGotoXY(u8 Copy_u8XPos, u8 Copy_u8YPos);

void LCD_voidWriteSpecialCharacter(u8* Copy_u8Pattern, u8 Copy_u8PatternNumber, u8 Copy_XPos, u8 Copy_YPos);


#endif
